#include "../../include/verse.hpp"
#include "../../prototypes/procedures.hpp"


void update_local_symbols(const Instruction& instruction, std::vector<Identifier>& local_symbols){
    if (std::holds_alternative<Variable>(instruction)){
        local_symbols.push_back(Identifier{std::get<Variable>(instruction).name});
    }
    else if (std::holds_alternative<Constant>(instruction)){
        local_symbols.push_back(Identifier{std::get<Constant>(instruction).name});
    }
}

void remove_local_symbols_from_outside_context(const std::vector<Identifier>& local_symbols, ExecutionContext& context){
    for (const Identifier& local : local_symbols){
        context.constant_types.erase(local.name);
        context.constant_values.erase(local.name);
        context.variable_types.erase(local.name);
        context.variable_values.erase(local.name);
    }
}

bool evaluate_boolean_condition(const Instruction& condition, ExecutionContext& context){
    auto [condition_type, condition_value] = execute_expression(condition, context);
    if (not std::holds_alternative<BaseType>(condition_type)) throw std::runtime_error{ "not a valid if condition" };
    if (std::get<BaseType>(condition_type).base_type != "Bool") throw std::runtime_error{ "not a valid if condition" };
    return std::get<BoolValue>(condition_value);
}

Instruction execute_code_block_once(const std::vector<Instruction>& code, ExecutionContext& context){
    std::vector<Identifier> local_symbols;
    for (const Instruction& instruction : code){
        update_local_symbols(instruction, local_symbols);
        Instruction callback = execute_instruction(instruction, context);
        if (std::holds_alternative<Return>(callback)) return callback;
        else if (std::holds_alternative<Break>(callback) or std::holds_alternative<Continue>(callback)) {
            remove_local_symbols_from_outside_context(local_symbols, context);
            return callback;
        }
    }
    remove_local_symbols_from_outside_context(local_symbols, context);
    return DoNothing{};
}

Instruction execute_conditional(const Conditional& conditional, ExecutionContext& context){
    bool boolean_condition = evaluate_boolean_condition(*conditional.condition, context);
    const std::vector<Instruction>& execution_path = (boolean_condition)? conditional.then : conditional.otherwise;
    Instruction callback =  execute_code_block_once(execution_path, context);
    if (not std::holds_alternative<DoNothing>(callback)){
        if (std::holds_alternative<Return>(callback))    return callback;
        if (std::holds_alternative<Break>(callback))     return callback;
        if (std::holds_alternative<Continue>(callback))  return callback;
        throw InternalCompilerError { "cannot recognize callback instruction" };
    }
    return DoNothing{};
}

Instruction execute_while_loop(const WhileLoop& while_loop, ExecutionContext& context){
    while(true){
        bool boolean_condition = evaluate_boolean_condition(*while_loop.condition, context);
        if (not boolean_condition) return DoNothing{};
        Instruction callback = execute_code_block_once(while_loop.code, context);
        if (not std::holds_alternative<DoNothing>(callback)){
            if (std::holds_alternative<Return>(callback))    return callback;
            if (std::holds_alternative<Break>(callback))     return DoNothing{};
            if (std::holds_alternative<Continue>(callback))  break;
            throw InternalCompilerError { "cannot recognize callback instruction" };
        }
    }
    return DoNothing{};
}

Instruction execute_until_loop(const UntilLoop& until_loop, ExecutionContext& context){
    while(true){
        Instruction callback = execute_code_block_once(until_loop.code, context);
        if (not std::holds_alternative<DoNothing>(callback)){
            if (std::holds_alternative<Return>(callback))    return callback;
            if (std::holds_alternative<Break>(callback))     return DoNothing{};
            if (std::holds_alternative<Continue>(callback))  break;
            throw InternalCompilerError { "cannot recognize callback instruction" };
        }
        bool boolean_condition = evaluate_boolean_condition(*until_loop.condition, context);
        if (boolean_condition) return DoNothing{};
    }
    return DoNothing{};
}