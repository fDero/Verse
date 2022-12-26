#include "../include/defs.hpp"
#include "../include/procedures.hpp"

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

void acquire_typesignature(std::vector<Token>::iterator& it, const std::vector<Token>& tokens, std::string& type){
    bool is_type = (it != tokens.end() and isalpha(it->sourcetext[0]) and isupper(it->sourcetext[0]));
    type = (is_type)? it->sourcetext : "/ERROR";
    std::advance(it,is_type);
    std::string found = (it == tokens.end())? "(END OF FILE)" : it->sourcetext;
    if(not is_type) throw std::runtime_error("unexpected token: " + found + " instead of: " + "type");
}

void acquire_expression(std::vector<Token>::iterator& it, const std::vector<Token>& tokens, std::shared_ptr<Instruction>& value){
    std::vector<Instruction> expression_wrapper;
    if (parse_non_terminated_expression(it,tokens, expression_wrapper)) value = std::make_shared<Instruction>(expression_wrapper[0]);    
    else {
        std::string found = (it == tokens.end())? "(END OF FILE)" : it->sourcetext;
        throw std::runtime_error("unexpected token: " + found + " instead of: " + "expression");
    }
}

void acquire_terminal(std::vector<Token>::iterator& it, const std::vector<Token>& tokens, std::shared_ptr<Instruction>& value){
    Instruction terminal;
    if (parse_terminal(it,tokens, terminal)) value = std::make_shared<Instruction>(terminal);
    else {
        std::string found = (it == tokens.end())? "(END OF FILE)" : it->sourcetext;
        throw std::runtime_error("unexpected token: " + found + " instead of: " + "expression");
    }
}

std::string updated_context(const std::string& context, const std::string& scope){
    return context + (context.empty()? "" : context_concatenation) + scope;
}