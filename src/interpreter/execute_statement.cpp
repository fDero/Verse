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

Instruction execute_conditional(const Conditional& conditional, ExecutionContext& context){
    auto [condition_type, condition_value] = execute_expression(*conditional.condition, context);
    std::vector<Identifier> local_symbols;
    if (not std::holds_alternative<BaseType>(condition_type)) throw std::runtime_error{ "not a valid if condition" };
    if (std::get<BaseType>(condition_type).base_type != "Bool") throw std::runtime_error{ "not a valid if condition" };
    bool boolean_condition = std::get<BoolValue>(condition_value);
    const std::vector<Instruction>& execution_path = (boolean_condition)? conditional.then : conditional.otherwise;
    for (const Instruction& instruction : execution_path){
        update_local_symbols(instruction, local_symbols);
        Instruction callback = execute_instruction(instruction, context);
        if (not std::holds_alternative<DoNothing>(callback)){
            if (std::holds_alternative<Return>(callback))    return callback;
            if (std::holds_alternative<Break>(callback))     return callback;
            if (std::holds_alternative<Continue>(callback))  return callback;
            throw InternalCompilerError { "cannot recognize callback instruction" };
        }
    }
    remove_local_symbols_from_outside_context(local_symbols, context);
    return DoNothing{};
}

Instruction execute_while_loop(const WhileLoop& while_loop, ExecutionContext& context){
    while(true){
        auto [condition_type, condition_value] = execute_expression(*while_loop.condition, context);
        if (not std::holds_alternative<BaseType>(condition_type)) throw std::runtime_error{ "not a valid condition" };
        if (std::get<BaseType>(condition_type).base_type != "Bool") throw std::runtime_error{ "not a valid condition" };
        if (not std::get<BoolValue>(condition_value)) return DoNothing{};
        std::vector<Identifier> local_symbols;
        for (const Instruction& instruction : while_loop.code){
            update_local_symbols(instruction, local_symbols);
            Instruction callback = execute_instruction(instruction, context);
            if (not std::holds_alternative<DoNothing>(callback)){
                remove_local_symbols_from_outside_context(local_symbols, context);
                if (std::holds_alternative<Return>(callback))    return DoNothing{};
                if (std::holds_alternative<Break>(callback))     return DoNothing{};
                if (std::holds_alternative<Continue>(callback))  break;
                throw InternalCompilerError { "cannot recognize callback instruction" };
            }
        }
        remove_local_symbols_from_outside_context(local_symbols, context);
    }
    return DoNothing{};
}

Instruction execute_until_loop(const UntilLoop& until_loop, ExecutionContext& context){
    while(true){
        std::vector<Identifier> local_symbols;
        for (const Instruction& instruction : until_loop.code){
            update_local_symbols(instruction, local_symbols);
            Instruction callback = execute_instruction(instruction, context);
            if (not std::holds_alternative<DoNothing>(callback)){
                remove_local_symbols_from_outside_context(local_symbols, context);
                if (std::holds_alternative<Return>(callback))    return DoNothing{};
                if (std::holds_alternative<Break>(callback))     return DoNothing{};
                if (std::holds_alternative<Continue>(callback))  break;
                throw InternalCompilerError { "cannot recognize callback instruction" };
            }
        }
        auto [condition_type, condition_value] = execute_expression(*until_loop.condition, context);
        remove_local_symbols_from_outside_context(local_symbols, context);
        if (not std::holds_alternative<BaseType>(condition_type)) throw std::runtime_error{ "not a valid condition" };
        if (std::get<BaseType>(condition_type).base_type != "Bool") throw std::runtime_error{ "not a valid condition" };
        if (std::get<BoolValue>(condition_value)) return DoNothing{};
    }
    return DoNothing{};
}