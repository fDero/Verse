#include "../../include/verse.hpp"
#include "../../prototypes/procedures.hpp"

bool parse_variable(std::vector<Token>::iterator& it, const std::vector<Token>& tokens, std::vector<Instruction>& output){ 
    if(it->sourcetext != "var") return false; 
    Variable this_var;
    std::shared_ptr<Instruction> value;
    acquire_exact_match(it,tokens,"var");
    acquire_identifier(it, tokens, this_var.name);
    acquire_exact_match(it,tokens,":");
    acquire_typesignature(it,tokens,this_var.typesignature);
    output.push_back(this_var);
    if(it != tokens.end() and it->sourcetext == ";") {
        std::advance(it,1);
        return true;
    } 
    acquire_exact_match(it,tokens,"=");
    acquire_expression(it,tokens,value);
    acquire_exact_match(it,tokens,";");
    std::shared_ptr<Instruction> id = std::make_shared<Instruction>(Identifier{this_var.name});
    output.push_back(Assignment{id,value});
    return true;
}

bool parse_constant(std::vector<Token>::iterator& it, const std::vector<Token>& tokens, std::vector<Instruction>& output){ 
    if(it->sourcetext != "const") return false;
    Constant this_const; 
    acquire_exact_match(it,tokens,"const");
    acquire_identifier(it, tokens, this_const.name);
    acquire_exact_match(it,tokens,":");
    acquire_typesignature(it,tokens,this_const.typesignature);
    acquire_exact_match(it,tokens,"=");
    acquire_expression(it,tokens,this_const.value);
    acquire_exact_match(it,tokens,";");
    output.push_back(this_const);
    return true;
}

bool parse_struct_definition (
    std::vector<Token>::iterator& it, const std::vector<Token>& tokens, 
    std::vector<Instruction>& output, std::shared_ptr<StructDefinition> parent
) {
    if(it->sourcetext != "struct") return false;
    StructDefinition this_struct;
    this_struct.parent_scope = parent;
    acquire_exact_match(it,tokens,"struct");
    acquire_baretype(it,tokens,this_struct.struct_name);
    acquire_simple_generics(it,tokens,this_struct.generics);
    acquire_struct_state_section(it, tokens, output, parent, this_struct);
    output.push_back(this_struct);
    return true;
}

bool parse_function_definition(
    std::vector<Token>::iterator& it, const std::vector<Token>& tokens, 
    std::vector<Instruction>& output, std::shared_ptr<FunctionDefinition> parent
) {    
    if(it->sourcetext != "func") return false;
    FunctionDefinition this_func;
    acquire_exact_match(it,tokens,"func");
    acquire_identifier(it,tokens,this_func.func_name);
    acquire_simple_generics(it,tokens,this_func.generics);
    std::string parent_name = (parent == nullptr)? "global" : parent->func_name;
    this_func.func_name = parent_name + "\\" + this_func.func_name;
    acquire_function_definition_arguments_section(it, tokens, output, parent, this_func);
    acquire_function_definition_code_section(it, tokens, output, parent, this_func);
    this_func.parent_scope = parent;
    output.push_back(this_func);
    return true;
}