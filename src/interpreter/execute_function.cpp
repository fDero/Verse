#include "../../include/verse.hpp"
#include "../../prototypes/procedures.hpp"

ExecutionContext craft_execution_context(const FunctionDefinition& function, const ArgumentValues& arguments){
    ExecutionContext context { std::make_shared<FunctionDefinition>(function) };
    for (int i = 0; i < function.args.size(); i++){
        context.variable_values[function.args[i].name] = arguments[i];
        context.variable_types[function.args[i].name] = function.args[i].typesignature;
    }
    return context;
}

std::pair<ArgumentTypes, ArgumentValues> evaluate_function_arguments(const FunctionCall& function_call, ExecutionContext& context){
    ArgumentTypes argument_types;
    ArgumentValues argument_values;
    for (const Instruction& argument : function_call.args){
        auto [type, value] = execute_expression(argument, context);
        argument_types.push_back(type);
        argument_values.push_back(value);
    }
    return { argument_types, argument_values };
}

ExpressionResult execute_function_call(const FunctionCall& function_call, ExecutionContext& context){
    auto [argument_types, argument_values] = evaluate_function_arguments(function_call, context);
    if (verselang_macros.find(function_call.func_name) != verselang_macros.end()) {
        return (verselang_macros[function_call.func_name])(argument_types, argument_values, context);
    }
    else {
        const std::string& function_name = function_call.func_name;
        FunctionDefinition function_to_be_invoked = retrieve_function_overload(function_name, argument_types, context);
        ExecutionContext brand_new_execution_context = craft_execution_context(function_to_be_invoked, argument_values);
        return execute_function_body(function_to_be_invoked, brand_new_execution_context);
    }
}

Instruction execute_instruction(const Instruction& instruction, ExecutionContext& context){
    Instruction callback = DoNothing{};
    if (std::holds_alternative<FunctionCall>(instruction))      execute_function_call(std::get<FunctionCall>(instruction), context);
    else if (std::holds_alternative<WhileLoop>(instruction))    callback = execute_while_loop(std::get<WhileLoop>(instruction), context);
    else if (std::holds_alternative<UntilLoop>(instruction))    callback = execute_until_loop(std::get<UntilLoop>(instruction), context);
    else if (std::holds_alternative<Conditional>(instruction))  callback = execute_conditional(std::get<Conditional>(instruction), context);
    else if (std::holds_alternative<Variable>(instruction))     define_variable(std::get<Variable>(instruction), context);
    else if (std::holds_alternative<Constant>(instruction))     define_constant(std::get<Constant>(instruction), context);
    else if (std::holds_alternative<Assignment>(instruction))   execute_assignment(std::get<Assignment>(instruction), context);
    else if (std::holds_alternative<Attempt>(instruction))      std::cout << "executing attempt ;) \n";
    else if (std::holds_alternative<Defer>(instruction))        std::cout << "executing defer ;) \n";
    else if (std::holds_alternative<Return>(instruction))       callback = instruction;
    else if (std::holds_alternative<Break>(instruction))        callback = instruction;
    else if (std::holds_alternative<Continue>(instruction))     callback = instruction;
    else throw std::runtime_error { "invalud statement" };
    return callback;
}

ExpressionResult execute_function_body(const FunctionDefinition& function, ExecutionContext& context){
    for (const Instruction& instruction : function.code){
        Instruction callback = execute_instruction(instruction, context);
        if (not std::holds_alternative<DoNothing>(callback)){
            if (std::holds_alternative<Return>(callback)){
                std::shared_ptr<Instruction> return_value = std::get<Return>(callback).value;
                if (return_value != nullptr) return execute_expression(*return_value, context);
            }       
            else if (std::holds_alternative<Break>(callback))    throw std::runtime_error { "invalid keyword 'break' inside of a function body" };
            else if (std::holds_alternative<Continue>(callback)) throw std::runtime_error { "invalid keyword 'continue' inside of a function body" };
            else throw InternalCompilerError { "cannot recognize callback instruction" };
        }
    }
    return ExpressionResult { BaseType{"Void"}, VoidValue{} };
}