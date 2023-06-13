#include "../include/verse.hpp"
#include "../include/procedures.hpp"

void acquire_instruction(std::vector<Token>::iterator& it, const std::vector<Token>& tokens, std::vector<Instruction>& output){
    if (parse_variable(it,tokens,output))             return;
    if (parse_constant(it,tokens,output))             return;
    if (parse_struct_definition(it,tokens,output))    return;
    if (parse_function_definition(it,tokens,output))  return;
    if (parse_conditional(it,tokens,output))          return;
    if (parse_while_loop(it,tokens,output))           return;
    if (parse_until_loop(it,tokens,output))           return;
    if (parse_return(it,tokens,output))               return;
    if (parse_defer(it,tokens,output))                return;
    if (parse_break(it,tokens,output))                return;
    if (parse_continue(it,tokens,output))             return;
    if (parse_attempt(it,tokens,output))              return;
    if (parse_expression(it,tokens,output))           return;
    throw std::runtime_error("unexpected token: " + it->sourcetext);
}

std::vector<Instruction> get_instructions_from_tokens(std::vector<Token>& tokens){ 
    std::vector<Instruction> output;
    std::vector<Token>::iterator it = tokens.begin();
    while (it != tokens.end()) acquire_instruction(it,tokens,output);
    return output;
}

void acquire_exact_match(std::vector<Token>::iterator& it, const std::vector<Token>& tokens, const std::string& match){
    bool is_match = (it != tokens.end() and it->sourcetext == match);
    std::advance(it,is_match);
    std::string found = (it == tokens.end())? "(END OF FILE)" : it->sourcetext;
    if(not is_match) throw std::runtime_error("unexpected token: " + found + " instead of: " + match);
}

void acquire_identifier(std::vector<Token>::iterator& it, const std::vector<Token>& tokens, std::string& name){
    bool is_identifier = (it != tokens.end() and isalpha(it->sourcetext[0]) and islower(it->sourcetext[0]));
    name = (is_identifier)? it->sourcetext : "/ERROR";
    std::advance(it,is_identifier);
    std::string found = (it == tokens.end())? "(END OF FILE)" : it->sourcetext;
    if(not is_identifier) throw std::runtime_error("unexpected token: " + found + " instead of: " + "identifier");
}

void acquire_instance(std::vector<Token>::iterator& it, const std::vector<Token>& tokens, Instance& target){
    acquire_identifier(it, tokens, target.name);
    acquire_exact_match(it,tokens,":");
    acquire_typesignature(it,tokens,target.typesignature);
}

void acquire_baretype(std::vector<Token>::iterator& it, const std::vector<Token>& tokens, std::string& type){
    bool is_type = (it != tokens.end() and isalpha(it->sourcetext[0]) and isupper(it->sourcetext[0]));
    type = (is_type)? it->sourcetext : "/ERROR";
    std::advance(it,is_type);
    std::string found = (it == tokens.end())? "(END OF FILE)" : it->sourcetext;
    if(not is_type) throw std::runtime_error("unexpected token: " + found + " instead of: " + "type");
}

void acquire_generics(std::vector<Token>::iterator& it, const std::vector<Token>& tokens, std::vector<TypeSignature>& generics){
    if (it == tokens.end() or it->sourcetext != "<") return;
    do {
        std::advance(it,1);
        TypeSignature generic;
        acquire_typesignature(it,tokens,generic);    
        generics.push_back(generic);
    } while (it != tokens.end() and it->sourcetext == ",");
    acquire_exact_match(it,tokens,">");
}

void acquire_simple_generics(std::vector<Token>::iterator& it, const std::vector<Token>& tokens, std::vector<TypeSignature>& generics){
    if (it == tokens.end() or it->sourcetext != "<") return;
    do {
        std::advance(it,1);
        std::string generic_base_type;
        acquire_baretype(it,tokens,generic_base_type);    
        generics.push_back(BaseType{generic_base_type,{}});
    } while (it != tokens.end() and it->sourcetext == ",");
    acquire_exact_match(it,tokens,">");
}

void acquire_typesignature(std::vector<Token>::iterator& it, const std::vector<Token>& tokens, TypeSignature& type){
    std::string base_type;
    std::vector<TypeSignature> generics;
    acquire_baretype(it,tokens,base_type);
    acquire_generics(it,tokens,generics);
    type = BaseType{base_type,generics};
    while (it != tokens.end()){
        if (it->sourcetext == "*") { 
            std::advance(it,1); 
            type = Pointer{std::make_shared<TypeSignature>(type)};
            continue;
        }
        if (it->sourcetext == "["){
            std::advance(it,1); 
            acquire_exact_match(it,tokens,"]");
            type = Array{std::make_shared<TypeSignature>(type),0}; 
            continue;
        }
        break;
    }
}

void acquire_expression(std::vector<Token>::iterator& it, const std::vector<Token>& tokens, std::shared_ptr<Instruction>& value){
    std::vector<Instruction> expression_wrapper;
    if (not parse_non_terminated_expression(it,tokens, expression_wrapper)) {
        std::string found = (it == tokens.end())? "(END OF FILE)" : it->sourcetext;
        throw std::runtime_error("unexpected token: " + found + " instead of: " + "expression");
    }
    value = std::make_shared<Instruction>(expression_wrapper[0]);
}

void acquire_terminal(std::vector<Token>::iterator& it, const std::vector<Token>& tokens, std::shared_ptr<Instruction>& value){
    Instruction terminal;
    if (not parse_terminal(it,tokens, terminal)) {
        std::string found = (it == tokens.end())? "(END OF FILE)" : it->sourcetext;
        throw std::runtime_error("unexpected token: " + found + " instead of: " + "expression");
    }
    value = std::make_shared<Instruction>(terminal);
}

void acquire_codeblock(std::vector<Token>::iterator& it, const std::vector<Token>& tokens, std::vector<Instruction>& code){
    if (it != tokens.end() and it->sourcetext != "{") {
        if (parse_struct_definition(it,tokens,code))   throw std::runtime_error("struct definitions not allowed in codeblock");
        if (parse_function_definition(it,tokens,code)) throw std::runtime_error("function definitions not allowed in codeblock");
        acquire_instruction(it,tokens,code);
    } 
    else {
        acquire_exact_match(it,tokens,"{");
        while(it != tokens.end() and it->sourcetext != "}") {
            if (parse_struct_definition(it,tokens,code))   throw std::runtime_error("struct definitions not allowed in codeblock");
            if (parse_function_definition(it,tokens,code)) throw std::runtime_error("function definitions not allowed in codeblock");
            acquire_instruction(it,tokens,code);
        }
        if (it == tokens.end() or it->sourcetext != "}") throw std::runtime_error("brackets opened but never closed");
        std::advance(it,1);
    }
}