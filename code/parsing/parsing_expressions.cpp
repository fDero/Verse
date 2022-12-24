#include "../include/defs.hpp"
#include "../include/procedures.hpp"

bool parse_char_literal(std::vector<Token>::iterator& it, const std::vector<Token>& tokens, std::vector<Instruction>& output){
    bool is_char_literal = it->sourcetext[0] == '\'';
    if (is_char_literal) output.push_back(Literal{it->sourcetext,"char"});
    std::advance(it,is_char_literal);
    return is_char_literal;
}

bool parse_string_literal(std::vector<Token>::iterator& it, const std::vector<Token>& tokens, std::vector<Instruction>& output){
    bool is_string_literal = it->sourcetext[0] == '"';
    if (is_string_literal) output.push_back(Literal{it->sourcetext,"string"});
    std::advance(it,is_string_literal);
    return is_string_literal;
}

bool parse_number_literal(std::vector<Token>::iterator& it, const std::vector<Token>& tokens, std::vector<Instruction>& output){
    if (it->sourcetext == ".") return false;
    bool floating;
    for (char c : it->sourcetext) {
        if (c == '.') floating = true;
        else if (!isdigit(c)) return false; 
    }
    if (floating) output.push_back(Literal{it->sourcetext,"float"});
    else output.push_back(Literal{it->sourcetext,"int"});
    std::advance(it,1);
    return true;
}

bool parse_bool_literal(std::vector<Token>::iterator& it, const std::vector<Token>& tokens, std::vector<Instruction>& output){
    if (it->sourcetext != "true" and it->sourcetext != "false") return false;
    output.push_back(Literal{it->sourcetext,"bool"});
    std::advance(it,1);
    return true;
}

bool parse_terminal(std::vector<Token>::iterator& it, const std::vector<Token>& tokens, std::vector<Instruction>& output){
    if (parse_char_literal(it,tokens,output))       return true;
    if (parse_string_literal(it,tokens,output))     return true;
    if (parse_number_literal(it,tokens,output))     return true;
    if (parse_bool_literal(it,tokens,output))       return true;
    return false;
}

bool parse_expression(std::vector<Token>::iterator& it, const std::vector<Token>& tokens, std::vector<Instruction>& output){
    if (parse_terminal(it,tokens,output)) {
        acquire_exact_match(it,tokens,";");
        return true;
    };
    return false;
}
