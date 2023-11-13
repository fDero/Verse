#include "../../include/verse.hpp"
#include "../../prototypes/procedures.hpp"

void ensure_correct_formatting_of_main_function(const FunctionDefinition& main_function){
    if (not main_function.generics.empty()) throw std::runtime_error { "the main function cannot has generics" };
    if (not main_function.args.empty()) throw std::runtime_error { "the main function cannot has parameters" };
}

FunctionDefinition find_main_entry_point(){
    auto main_function_search_outcome = global_functions_definitions.find("main");
    if (main_function_search_outcome == global_functions_definitions.end()) throw std::runtime_error { " can't find main entry point " };
    const OverloadSet& main_overload_set =main_function_search_outcome->second;
    if (main_overload_set.empty()) throw InternalCompilerError { "somehow an overload set is empty" };
    if (main_overload_set.size() > 1) throw std::runtime_error { "the main function cannot be overloaded" };
    FunctionDefinition main_entry_point = main_overload_set.back();
    ensure_correct_formatting_of_main_function(main_entry_point);
    return main_entry_point;
}