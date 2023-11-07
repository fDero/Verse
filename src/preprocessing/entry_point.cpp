#include "../../include/verse.hpp"
#include "../../prototypes/procedures.hpp"

void ensure_correct_formatting_of_main_function(const FunctionDefinition& main_function){
    if (not main_function.generics.empty()) throw std::runtime_error { "the main function cannot has generics" };
    if (not main_function.args.empty()) throw std::runtime_error { "the main function cannot has parameters" };
    if (main_function.parent_scope != nullptr) throw InternalCompilerError { "somehow main function has a parent scope, even tough it's in global scope" };
}

FunctionDefinition find_main_entry_point(){
    if (global_functions_definitions.find("global\\main") == global_functions_definitions.end()) throw std::runtime_error { " can't find main entry point " };
    const OverloadSet& main_overload_set = global_functions_definitions.find("global\\main")->second;
    if (main_overload_set.empty()) throw InternalCompilerError { "somehow an overload set is empty" };
    if (main_overload_set.size() > 1) throw std::runtime_error { "the main function cannot be overloaded" };
    FunctionDefinition main_entry_point = main_overload_set.back();
    ensure_correct_formatting_of_main_function(main_entry_point);
    return main_entry_point;
}