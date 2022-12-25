#include "../include/defs.hpp"
#include "../include/procedures.hpp"

bool parse_prefix_operator(std::vector<Token>::iterator& it, const std::vector<Token>& tokens, Instruction& target){
    if (prefixes.find(it->sourcetext) == prefixes.end()) return false;
    std::string operator_id = it->sourcetext;
    std::advance(it,1);
    std::shared_ptr<Instruction> operand;
    acquire_expression(it,tokens,operand);
    target = UnaryOperator{operator_id,operand};
    fix_expression(target);
    return true;
}

bool parse_infix_operator(std::vector<Token>::iterator& it, const std::vector<Token>& tokens, const Instruction& expr, std::vector<Instruction>& output){
    if (infixies.find(it->sourcetext) == infixies.end()) return false;
    std::string text = it->sourcetext;
    std::advance(it,1);
    std::shared_ptr<Instruction> rx;
    acquire_expression(it,tokens,rx);
    std::shared_ptr<Instruction> lx = std::make_shared<Instruction>(expr);
    output.push_back(BinaryOperator{text, lx, rx});       
    fix_expression(output.back());
    return true;
}

int get_precedence(const Instruction& expr){
    if (std::holds_alternative<BinaryOperator>(expr)){
        BinaryOperator op = std::get<BinaryOperator>(expr);
        if (op.text == "+")     return 1;
        if (op.text == "-")     return 1;
        if (op.text == "*")     return 2;
        if (op.text == "/")     return 2;
        if (op.text == "%")     return 2;
        if (op.text == "^")     return 3;
        if (op.text == "==")    return 4;
        if (op.text == "!=")    return 4;
        if (op.text == "<=")    return 4;
        if (op.text == ">=")    return 4;
        if (op.text == "&&")    return 5;
        if (op.text == "||")    return 5;
        if (op.text == "^^")    return 5;
        if (op.text == ".")     return 7;
    }
    if (std::holds_alternative<UnaryOperator>(expr))  return 6;
    if (std::holds_alternative<FunctionCall>(expr)) return 8;
    if (std::holds_alternative<Identifier>(expr)) return 8;
    if (std::holds_alternative<Literal>(expr)) return 8;
    throw std::runtime_error(
        "[INTERNAL ERROR]: precedence computation has been tried on non-expression instruction"
    );
}

void fix_expression(Instruction& expr){
    if (std::holds_alternative<BinaryOperator>(expr)){
        if (not std::holds_alternative<BinaryOperator>(*(std::get<BinaryOperator>(expr).rx))) return;
        BinaryOperator current_root = std::get<BinaryOperator>(expr);
        BinaryOperator current_root_rx = std::get<BinaryOperator>(*(std::get<BinaryOperator>(expr).rx));
        if (get_precedence(current_root) < get_precedence(current_root_rx)) return;
        BinaryOperator new_root_lx = BinaryOperator{current_root.text,current_root.lx, current_root_rx.lx};
        BinaryOperator new_root = BinaryOperator{current_root_rx.text,std::make_shared<Instruction>(new_root_lx),current_root_rx.rx};
        expr = new_root;
    }
}