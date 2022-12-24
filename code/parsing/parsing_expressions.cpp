#include "../include/defs.hpp"
#include "../include/procedures.hpp"

bool parse_char_literal(std::vector<Token>::iterator& it, const std::vector<Token>& tokens, Instruction& target){
    bool is_char_literal = it->sourcetext[0] == '\'';
    if (is_char_literal) target = Literal{it->sourcetext,"char"};
    std::advance(it,is_char_literal);
    return is_char_literal;
}

bool parse_string_literal(std::vector<Token>::iterator& it, const std::vector<Token>& tokens, Instruction& target){
    bool is_string_literal = it->sourcetext[0] == '"';
    if (is_string_literal) target = Literal{it->sourcetext,"string"};
    std::advance(it,is_string_literal);
    return is_string_literal;
}

bool parse_number_literal(std::vector<Token>::iterator& it, const std::vector<Token>& tokens, Instruction& target){
    if (it->sourcetext == ".") return false;
    bool floating;
    for (char c : it->sourcetext) {
        if (c == '.') floating = true;
        else if (!isdigit(c)) return false; 
    }
    target = (floating)? Literal{it->sourcetext,"float"} : Literal{it->sourcetext,"int"};
    std::advance(it,1);
    return true;
}

bool parse_bool_literal(std::vector<Token>::iterator& it, const std::vector<Token>& tokens, Instruction& target){
    if (it->sourcetext != "true" and it->sourcetext != "false") return false;
    target = Literal{it->sourcetext,"bool"};
    std::advance(it,1);
    return true;
}

bool parse_terminal(std::vector<Token>::iterator& it, const std::vector<Token>& tokens, Instruction& target){
    if (parse_char_literal(it,tokens,target))       return true;
    if (parse_string_literal(it,tokens,target))     return true;
    if (parse_number_literal(it,tokens,target))     return true;
    if (parse_bool_literal(it,tokens,target))       return true;
    return false;
}

bool parse_prefix_operator(std::vector<Token>::iterator& it, const std::vector<Token>& tokens, Instruction& target){
    if (prefixes.find(it->sourcetext) == prefixes.end()) return false;
    std::string operator_id = it->sourcetext;
    std::advance(it,1);
    std::shared_ptr<Instruction> operand;
    acquire_expression(it,tokens,operand);
    target = FunctionCall{"prefix_operator_(" + operator_id + ")",{*operand}};
    return true;
}

bool parse_infix_operator(std::vector<Token>::iterator& it, const std::vector<Token>& tokens, std::string& target){
    if (infixies.find(it->sourcetext) == infixies.end()) return false;
    target = it->sourcetext;
    std::advance(it,1);
    return true;
}

bool parse_non_terminated_expression(std::vector<Token>::iterator& it, const std::vector<Token>& tokens, std::vector<Instruction>& output){
    Instruction expr;
    std::string binary_infix_operator_id; 
    std::shared_ptr<Instruction> rx;
    if (!parse_prefix_operator(it,tokens,expr) and !parse_terminal(it,tokens,expr)) return false;
    if (parse_infix_operator(it,tokens,binary_infix_operator_id)) {
        acquire_expression(it,tokens,rx);
        output.push_back(FunctionCall{binary_infix_operator_id, {expr, *rx}});       
    } else {
        output.push_back(expr);
    }
    return true;
}

bool parse_expression(std::vector<Token>::iterator& it, const std::vector<Token>& tokens, std::vector<Instruction>& output){
    if (not parse_non_terminated_expression(it,tokens,output)) return false;
    acquire_exact_match(it,tokens,";");
    return true;
}
