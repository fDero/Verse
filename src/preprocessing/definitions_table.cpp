#include "../include/verse.hpp"
#include "../include/procedures.hpp"

void struct_preprocessing(DefinitionsTable& deftable, const Instruction& instruction){
    const StructDefinition& struct_definition = std::get<StructDefinition>(instruction);
    if (deftable.structs.find(struct_definition.struct_name) != deftable.structs.end()){
        throw std::runtime_error { "another struct already exists with this name" };
    }
    deftable.structs[struct_definition.struct_name] = std::vector<StructDefinition>{ struct_definition };
}

void function_preprocessing(DefinitionsTable& deftable, const Instruction& instruction){
    const FunctionDefinition& function_definition = std::get<FunctionDefinition>(instruction);
    if (deftable.functions.find(function_definition.func_name) != deftable.functions.end()){
        deftable.functions[function_definition.func_name].push_back(function_definition);    
    }
    deftable.functions[function_definition.func_name] = std::vector<FunctionDefinition>{ function_definition };
}

void init_global_definitions_table(const std::vector<std::string>& input_files){
    global_definitions_table.functions.clear();
    global_definitions_table.structs.clear();
    ScopingData global_scope { "global" };
    for (const std::string& input : input_files){
        std::vector<Token> tokens = get_tokens_from_file(input); 
        std::vector<Instruction> instructions = get_instructions_from_tokens(tokens);
        for (const Instruction& instruction : instructions){
            if (std::holds_alternative<FunctionDefinition>(instruction)) function_preprocessing(global_definitions_table, instruction);
            else if (std::holds_alternative<StructDefinition>(instruction)) struct_preprocessing(global_definitions_table, instruction);
            else throw std::runtime_error { "found a non-definition instruction in global scope" };
        } 
    }
}