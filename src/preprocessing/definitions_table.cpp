#include "../include/verse.hpp"
#include "../include/procedures.hpp"

void struct_preprocessing(const Instruction& instruction){
    const StructDefinition& struct_definition = std::get<StructDefinition>(instruction);
    std::string fully_qualified_name = get_qualified_struct_name(struct_definition);
    if (global_structs_definitions.find(struct_definition.struct_name) != global_structs_definitions.end()){
        throw std::runtime_error { "another struct already exists with this name" };
    }
    global_structs_definitions[fully_qualified_name] = struct_definition;
    global_structs_names_register[struct_definition.struct_name].push_back(fully_qualified_name);
}

void function_preprocessing(const Instruction& instruction){
    const FunctionDefinition& function_definition = std::get<FunctionDefinition>(instruction);
    global_functions_definitions[function_definition.func_name].push_back(function_definition);
}

void init_global_definitions_table(const std::vector<std::string>& input_files){
    global_functions_definitions.clear();
    global_structs_definitions.clear();
    for (const std::string& input : input_files){
        std::vector<Token> tokens = get_tokens_from_file(input); 
        std::vector<Instruction> instructions = get_instructions_from_tokens(tokens);
        for (const Instruction& instruction : instructions){
            if (std::holds_alternative<FunctionDefinition>(instruction)) function_preprocessing(instruction);
            else if (std::holds_alternative<StructDefinition>(instruction)) struct_preprocessing(instruction);
            else throw std::runtime_error { "found a non-definition instruction in global scope" };
        } 
    }
}