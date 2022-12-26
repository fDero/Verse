#include "../include/defs.hpp"
#include "../include/procedures.hpp"

bool parse_conditional_statement(std::vector<Token>::iterator& it, const std::vector<Token>& tokens, std::vector<Instruction>& output){
    return false;
}

bool parse_while_loop(std::vector<Token>::iterator& it, const std::vector<Token>& tokens, std::vector<Instruction>& output){
    if (it->sourcetext != "while") return false;
    std::advance(it,1);
    std::shared_ptr<Instruction> condition;
    acquire_expression(it,tokens,condition);
    acquire_exact_match(it,tokens,"{");
    std::vector<Instruction> code;
    while(it != tokens.end() and it->sourcetext != "}") parse_instruction(it,tokens,"",code);
    if (it == tokens.end() or it->sourcetext != "}") throw std::runtime_error("brackets opened but never closed in while loop");
    std::advance(it,1);
    output.push_back(WhileLoop{condition,code});
    return true;
}

bool parse_until_loop(std::vector<Token>::iterator& it, const std::vector<Token>& tokens, std::vector<Instruction>& output){
    return false;
}