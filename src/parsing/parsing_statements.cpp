#include "../../include/verse.hpp"
#include "../../prototypes/procedures.hpp"

bool parse_conditional(std::vector<Token>::iterator& it, const std::vector<Token>& tokens, std::vector<Instruction>& output){
    if (it->sourcetext != "if") return false;
    acquire_exact_match(it,tokens,"if");
    std::shared_ptr<Instruction> condition;
    std::vector<Instruction> then;
    std::vector<Instruction> otherwise;
    acquire_expression(it,tokens,condition);
    acquire_codeblock(it,tokens,then);
    if (it == tokens.end() or it->sourcetext != "else") {
        output.push_back(Conditional{condition,then,otherwise});
        return true;
    }
    acquire_exact_match(it,tokens,"else");
    acquire_codeblock(it,tokens,otherwise);
    output.push_back(Conditional{condition,then,otherwise});
    return true;
}

bool parse_while_loop(std::vector<Token>::iterator& it, const std::vector<Token>& tokens, std::vector<Instruction>& output){
    if (it->sourcetext != "while") return false;
    acquire_exact_match(it,tokens,"while");
    std::shared_ptr<Instruction> condition;
    std::vector<Instruction> code;
    acquire_expression(it,tokens,condition);
    acquire_codeblock(it,tokens,code);
    output.push_back(WhileLoop{condition,code});
    return true;
}

bool parse_until_loop(std::vector<Token>::iterator& it, const std::vector<Token>& tokens, std::vector<Instruction>& output){
    if (it->sourcetext != "until") return false;
    acquire_exact_match(it,tokens,"until");
    std::shared_ptr<Instruction> condition;
    std::vector<Instruction> code;
    acquire_expression(it,tokens,condition);
    acquire_codeblock(it,tokens,code);
    output.push_back(UntilLoop{condition,code});
    return true;
}

bool parse_continue(std::vector<Token>::iterator& it, const std::vector<Token>& tokens, std::vector<Instruction>& output){
    if (it->sourcetext != "continue") return false;
    acquire_exact_match(it,tokens,"continue");
    acquire_exact_match(it,tokens,";");
    output.push_back(Continue{});
    return true;
}

bool parse_break(std::vector<Token>::iterator& it, const std::vector<Token>& tokens, std::vector<Instruction>& output){
    if (it->sourcetext != "break") return false;
    acquire_exact_match(it,tokens,"break");
    acquire_exact_match(it,tokens,";");
    output.push_back(Break{});
    return true;
}

bool parse_return(std::vector<Token>::iterator& it, const std::vector<Token>& tokens, std::vector<Instruction>& output){
    if (it->sourcetext != "return") return false;
    acquire_exact_match(it,tokens,"return");
    if(it != tokens.end() and it->sourcetext == ";") {
        output.push_back(Return{nullptr});    
        std::advance(it,1);
        return true;
    } 
    std::shared_ptr<Instruction> value;
    acquire_expression(it,tokens,value);
    acquire_exact_match(it,tokens,";");
    output.push_back(Return{value});
    return true;
}

bool parse_defer(std::vector<Token>::iterator& it, const std::vector<Token>& tokens, std::vector<Instruction>& output){
    if (it->sourcetext != "defer") return false;
    acquire_exact_match(it,tokens,"defer");
    std::shared_ptr<Instruction> code;
    acquire_expression(it,tokens,code); 
    acquire_exact_match(it,tokens,";");
    output.push_back(Defer{code});
    return true;
}

bool parse_attempt(std::vector<Token>::iterator& it, const std::vector<Token>& tokens, std::vector<Instruction>& output){
    if (it->sourcetext != "attempt") return false;
    std::vector<std::vector<Instruction>> attempts;
    std::vector<Instruction> otherwise;
    while (it != tokens.end() and it->sourcetext == "attempt") {
        acquire_exact_match(it,tokens,"attempt");
        attempts.push_back(std::vector<Instruction>{});
        acquire_codeblock(it,tokens,attempts.back());
    }
    if (it != tokens.end() and it->sourcetext == "default") {
        acquire_exact_match(it,tokens,"default");
        acquire_codeblock(it,tokens,otherwise);
    } 
    output.push_back(Attempt{attempts,otherwise});
    return true;
}