#include "../include/defs.hpp"
#include "../include/procedures.hpp"

bool parse_prefix_operator(std::vector<Token>::iterator& it, const std::vector<Token>& tokens, Instruction& target){
    if (prefixes.find(it->sourcetext) == prefixes.end()) return false;
    std::string operator_id = "@unary_prefix_operator_" + it->sourcetext;
    std::advance(it,1);
    std::shared_ptr<Instruction> operand;
    acquire_expression(it,tokens,operand);
    target = UnaryOperator{operator_id,operand};
    return true;
}

bool parse_infix_operator(std::vector<Token>::iterator& it, const std::vector<Token>& tokens, const Instruction& expr, std::vector<Instruction>& output){
    if (infixies.find(it->sourcetext) == infixies.end()) return false;
    std::string text = "@binary_infix_operator_" + it->sourcetext;
    std::advance(it,1);
    std::shared_ptr<Instruction> rx;
    acquire_expression(it,tokens,rx);
    std::shared_ptr<Instruction> lx = std::make_shared<Instruction>(expr);
    output.push_back(BinaryOperator{text, lx, rx});       
    return true;
}