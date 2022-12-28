#include "../include/verse.hpp"
#include "../include/procedures.hpp"

bool parse_conditional(std::vector<Token>::iterator& it, const std::vector<Token>& tokens, std::vector<Instruction>& output){
    if (it->sourcetext != "if") return false;
    std::advance(it,1);
    std::shared_ptr<Instruction> condition;
    std::vector<Instruction> then;
    std::vector<Instruction> otherwise;
    acquire_expression(it,tokens,condition);
    acquire_codeblock(it,tokens,then);
    if (it == tokens.end() or it->sourcetext != "else") {
        output.push_back(Conditional{condition,then,otherwise});
        return true;
    }
    std::advance(it,1);
    acquire_codeblock(it,tokens,otherwise);
    output.push_back(Conditional{condition,then,otherwise});
    return true;
}

bool parse_while_loop(std::vector<Token>::iterator& it, const std::vector<Token>& tokens, std::vector<Instruction>& output){
    if (it->sourcetext != "while") return false;
    std::advance(it,1);
    std::shared_ptr<Instruction> condition;
    std::vector<Instruction> code;
    acquire_expression(it,tokens,condition);
    acquire_codeblock(it,tokens,code);
    output.push_back(WhileLoop{condition,code});
    return true;
}

bool parse_until_loop(std::vector<Token>::iterator& it, const std::vector<Token>& tokens, std::vector<Instruction>& output){
    if (it->sourcetext != "until") return false;
    std::advance(it,1);
    std::shared_ptr<Instruction> condition;
    std::vector<Instruction> code;
    acquire_expression(it,tokens,condition);
    acquire_codeblock(it,tokens,code);
    output.push_back(UntilLoop{condition,code});
    return true;
}