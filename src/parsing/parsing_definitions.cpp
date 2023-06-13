#include "../include/verse.hpp"
#include "../include/procedures.hpp"

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

bool parse_struct_definition(std::vector<Token>::iterator& it, const std::vector<Token>& tokens, std::vector<Instruction>& output){
    if(it->sourcetext != "struct") return false;
    StructDefinition this_struct;
    acquire_exact_match(it,tokens,"struct");
    acquire_baretype(it,tokens,this_struct.struct_name);
    acquire_simple_generics(it,tokens,this_struct.generics);
    acquire_exact_match(it,tokens,"{");
    while(it != tokens.end() and it->sourcetext != "}"){
        if (parse_struct_definition(it,tokens,this_struct.internal_definitions)) continue;
        Instance field;  
        acquire_instance(it,tokens,field);
        acquire_exact_match(it,tokens,";");
        this_struct.internal_state.push_back(field);
    }
    if (it == tokens.end()) throw std::runtime_error("brackets opened but never closed in struct definition");
    std::advance(it,1);
    output.push_back(this_struct);
    return true;
}

bool parse_function_definition(std::vector<Token>::iterator& it, const std::vector<Token>& tokens, std::vector<Instruction>& output){    
    if(it->sourcetext != "func") return false;
    FunctionDefinition this_func;
    acquire_exact_match(it,tokens,"func");
    acquire_identifier(it,tokens,this_func.func_name);
    acquire_simple_generics(it,tokens,this_func.generics);
    acquire_exact_match(it,tokens,"(");
    if (it != tokens.end() and it->sourcetext != ")" and it->sourcetext != ",") do {
        std::advance(it,it->sourcetext == ",");
        Instance arg; 
        acquire_instance(it,tokens,arg);
        this_func.args.push_back(arg);
    } while (it != tokens.end() and it->sourcetext == ",");
    if (it != tokens.end() and it->sourcetext != ")") throw std::runtime_error("unexpected token: " + it->sourcetext + " instead of: )");
    if (it == tokens.end()) throw std::runtime_error("parenthesys opened but never closed");
    std::advance(it,1);
    acquire_exact_match(it,tokens,"{");
    while(it != tokens.end() and it->sourcetext != "}"){
        if (parse_struct_definition(it,tokens,this_func.internal_definitions))   continue;
        if (parse_function_definition(it,tokens,this_func.internal_definitions)) continue;
        acquire_instruction(it,tokens,this_func.code);
    }
    if (it == tokens.end() or it->sourcetext != "}") throw std::runtime_error("brackets opened but never closed in function definition");
    std::advance(it,1);
    output.push_back(this_func);
    return true;
}