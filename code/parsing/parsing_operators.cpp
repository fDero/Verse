#include "../include/defs.hpp"
#include "../include/procedures.hpp"

bool parse_prefix_operator(std::vector<Token>::iterator& it, const std::vector<Token>& tokens, Instruction& target){
    if (it == tokens.end() or prefixes.find(it->sourcetext) == prefixes.end()) return false;
    std::vector<std::string> encountered_prefixes;
    std::shared_ptr<Instruction> operand;
    while (it != tokens.end() and prefixes.find(it->sourcetext) != prefixes.end()) { 
        encountered_prefixes.push_back(it->sourcetext);
        std::advance(it,1);
    }
    acquire_terminal(it,tokens,operand); 
    UnaryOperator op {encountered_prefixes.back(), operand};
    encountered_prefixes.pop_back();
    auto reverse_prefixes_iterator = encountered_prefixes.rbegin();
    while (reverse_prefixes_iterator != encountered_prefixes.rend()){
        op = UnaryOperator{*reverse_prefixes_iterator, std::make_shared<Instruction>(op)};
        std::advance(reverse_prefixes_iterator,1);
    }
    target = op;
    return true;
}

bool parse_infix_operator(std::vector<Token>::iterator& it, const std::vector<Token>& tokens, Instruction& expr){
    if (it == tokens.end() or infixies.find(it->sourcetext) == infixies.end()) return false;
    std::shared_ptr<Instruction> lx = std::make_shared<Instruction>(expr);
    std::string infix_operator_text = it->sourcetext;
    std::advance(it,1);
    std::shared_ptr<Instruction> rx;
    if (parse_prefix_operator(it,tokens,expr)) rx = std::make_shared<Instruction>(expr);
    else acquire_terminal(it,tokens,rx);
    expr = BinaryOperator{infix_operator_text, lx, rx};
    return true;
}