#include "../include/defs.hpp"
#include "../include/procedures.hpp"

void parse_instruction(std::vector<Token>::iterator& it, const std::vector<Token>& tokens, std::string context, std::vector<Instruction>& output){
    if (parse_instantiation(it,tokens,output))                  return;
    if (parse_struct_definition(it,tokens,context,output))      return;
    if (parse_function_definition(it,tokens,context,output))    return;
    if (parse_conditional_statement(it,tokens,output))          return;
    if (parse_while_loop(it,tokens,output))                     return;
    if (parse_until_loop(it,tokens,output))                     return;
    if (parse_expression(it,tokens,output))                     return;
    throw std::runtime_error("unexpected token: " + it->sourcetext);
}

void parse_file(std::vector<Token>::iterator& it, const std::vector<Token>& tokens, std::string context, std::vector<Instruction>& output){ 
    while (it != tokens.end()) {
        parse_instruction(it,tokens,context,output);
    }
}