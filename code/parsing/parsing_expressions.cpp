#include "../include/verse.hpp"
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

bool parse_identifier(std::vector<Token>::iterator& it, const std::vector<Token>& tokens, Instruction& target){
    if (it == tokens.end() or !isalpha(it->sourcetext[0]) or !islower(it->sourcetext[0])) return false;
    target = Identifier{it->sourcetext};
    std::advance(it,1);
    return true;
}

bool parse_function_call(std::vector<Token>::iterator& it, const std::vector<Token>& tokens, Instruction& target){
    if (it == tokens.end() or !isalpha(it->sourcetext[0]) or !islower(it->sourcetext[0])) return false;
    std::string func_name = it->sourcetext;
    if (std::next(it) == tokens.end() or std::next(it)->sourcetext != "(") return false;  
    std::advance(it,1);
    std::vector<Instruction> args;
    acquire_exact_match(it,tokens,"(");
    if (it != tokens.end() and it->sourcetext != ")" and it->sourcetext != ",") do {
        std::advance(it,it->sourcetext == ",");
        std::shared_ptr<Instruction> value;
        acquire_expression(it,tokens,value);
        args.push_back(*value);
    } while (it != tokens.end() and it->sourcetext == ",");
    if (it != tokens.end() and it->sourcetext != ")") throw std::runtime_error("unexpected token: " + it->sourcetext + " instead of: )");
    if (it == tokens.end()) throw std::runtime_error("parenthesys opened but never closed");
    std::advance(it,1);
    target = FunctionCall{func_name, args};
    return true;
}

bool parse_parenthesys(std::vector<Token>::iterator& it, const std::vector<Token>& tokens, Instruction& target){
    if (it->sourcetext != "(") return false;
    acquire_exact_match(it,tokens,"(");
    std::shared_ptr<Instruction> expr;
    acquire_expression(it,tokens,expr);
    target = *expr;
    acquire_exact_match(it,tokens,")");
    operator_precedence_lockout(target);
    return true;
}

bool parse_terminal(std::vector<Token>::iterator& it, const std::vector<Token>& tokens, Instruction& target){
    if (parse_parenthesys(it,tokens,target))        return true;
    if (parse_char_literal(it,tokens,target))       return true;
    if (parse_string_literal(it,tokens,target))     return true;
    if (parse_number_literal(it,tokens,target))     return true;
    if (parse_bool_literal(it,tokens,target))       return true;
    if (parse_function_call(it,tokens,target))      return true;
    if (parse_identifier(it,tokens,target))         return true;
    return false;
}

bool parse_non_terminated_expression(std::vector<Token>::iterator& it, const std::vector<Token>& tokens, std::vector<Instruction>& output){
    Instruction expr;
    if (!parse_terminal(it,tokens,expr) and !parse_prefix_operator(it,tokens,expr)) return false;
    while (it != tokens.end()) if (not parse_infix_operator(it,tokens,expr) and not parse_assignment(it,tokens,expr)) break;
    output.push_back(expr);
    return true;
}

bool parse_expression(std::vector<Token>::iterator& it, const std::vector<Token>& tokens, std::vector<Instruction>& output){
    if (not parse_non_terminated_expression(it,tokens,output)) return false;
    acquire_exact_match(it,tokens,";");
    return true;
}