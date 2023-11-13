#include "../../include/verse.hpp"
#include "../../prototypes/procedures.hpp"

OverloadSet retrieve_whole_overload_set(const std::string& function_name){
    if (global_functions_definitions.find(function_name) != global_functions_definitions.end()){
        return global_functions_definitions.find(function_name)->second;
    }
    throw std::runtime_error { "no such function exists in the current scope (non-existing overload set)" }; 
}

bool arguments_type_match_exactly(const FunctionDefinition& function, const ArgumentTypes& argument_types){
    if (function.args.size() != argument_types.size()) return false;
    for (int i = 0; i < function.args.size(); i++) {
        if (not typesignatures_are_equal(function.args[i].typesignature, argument_types[i])){
            return false;
        }
    }
    return true;
}

FunctionDefinition retrieve_function_overload(const std::string& function_name, const ArgumentTypes& argument_types, ExecutionContext& context){
    OverloadSet overload_set = retrieve_whole_overload_set(function_name);
    if (overload_set.empty()) throw std::runtime_error { "no such function exists in the current scope (empty overload set)" }; 
    if (overload_set.size() > 1) throw std::runtime_error { "function overloads are not supported yet (work in progress)" };
    const FunctionDefinition& retrieved = overload_set.back();
    if (not arguments_type_match_exactly(retrieved, argument_types)) throw std::runtime_error { "no such function exists in the current scope (args mismatch)" }; 
    return retrieved;
}