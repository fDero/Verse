#include "../../include/verse.hpp"
#include "../../prototypes/procedures.hpp"


Instruction execute_conditional(const Conditional& conditional, ExecutionContext& context){
    auto [condition_type, condition_value] = execute_expression(*conditional.condition, context);
    if (not std::holds_alternative<BaseType>(condition_type)) throw std::runtime_error{ "not a valid if condition" };
    if (std::get<BaseType>(condition_type).base_type != "Bool") throw std::runtime_error{ "not a valid if condition" };
    if (not std::holds_alternative<BoolValue>(condition_value)) throw InternalCompilerError { "teschio" };
    bool boolean_condition = std::get<BoolValue>(condition_value);
    const std::vector<Instruction>& execution_path = (boolean_condition)? conditional.then : conditional.otherwise;
    for (const Instruction& instruction : execution_path){
        Instruction callback = execute_instruction(instruction, context);
        if (not std::holds_alternative<DoNothing>(callback)){
            if (std::holds_alternative<Return>(callback))    return callback;
            if (std::holds_alternative<Break>(callback))     return callback;
            if (std::holds_alternative<Continue>(callback))  return callback;
            throw InternalCompilerError { "cannot recognize callback instruction" };
        }
    }
    return DoNothing{};
}

Instruction execute_while_loop(const WhileLoop& while_loop, ExecutionContext& context){
    while(true){
        auto [condition_type, condition_value] = execute_expression(*while_loop.condition, context);
        if (not std::holds_alternative<BaseType>(condition_type)) throw std::runtime_error{ "not a valid if condition" };
        if (std::get<BaseType>(condition_type).base_type != "Bool") throw std::runtime_error{ "not a valid if condition" };
        if (not std::holds_alternative<BoolValue>(condition_value)) throw InternalCompilerError { "teschio" };
        if (not std::get<BoolValue>(condition_value)) return DoNothing{};
        for (const Instruction& instruction : while_loop.code){
            Instruction callback = execute_instruction(instruction, context);
            if (not std::holds_alternative<DoNothing>(callback)){
                if (std::holds_alternative<Return>(callback))    return DoNothing{};
                if (std::holds_alternative<Break>(callback))     return DoNothing{};
                if (std::holds_alternative<Continue>(callback))  break;
                throw InternalCompilerError { "cannot recognize callback instruction" };
            }
        }
    }
}

Instruction execute_until_loop(const UntilLoop& until_loop, ExecutionContext& context){
    while(true){
        for (const Instruction& instruction : until_loop.code){
            Instruction callback = execute_instruction(instruction, context);
            if (not std::holds_alternative<DoNothing>(callback)){
                if (std::holds_alternative<Return>(callback))    return DoNothing{};
                if (std::holds_alternative<Break>(callback))     return DoNothing{};
                if (std::holds_alternative<Continue>(callback))  break;
                throw InternalCompilerError { "cannot recognize callback instruction" };
            }
        }
        auto [condition_type, condition_value] = execute_expression(*until_loop.condition, context);
        if (not std::holds_alternative<BaseType>(condition_type)) throw std::runtime_error{ "not a valid if condition" };
        if (std::get<BaseType>(condition_type).base_type != "Bool") throw std::runtime_error{ "not a valid if condition" };
        if (not std::holds_alternative<BoolValue>(condition_value)) throw InternalCompilerError { "teschio" };
        if (std::get<BoolValue>(condition_value)) return DoNothing{};
    }
}