#include "../../include/verse.hpp"
#include "../../prototypes/procedures.hpp"

void acquire_instruction(std::vector<Token>::iterator& it, const std::vector<Token>& tokens, std::vector<Instruction>& output){
    if (parse_variable(it,tokens,output))                     return;
    if (parse_constant(it,tokens,output))                     return;
    if (parse_struct_definition(it,tokens,output, nullptr))   return;
    if (parse_function_definition(it,tokens,output, nullptr)) return;
    if (parse_conditional(it,tokens,output))                  return;
    if (parse_while_loop(it,tokens,output))                   return;
    if (parse_until_loop(it,tokens,output))                   return;
    if (parse_return(it,tokens,output))                       return;
    if (parse_defer(it,tokens,output))                        return;
    if (parse_break(it,tokens,output))                        return;
    if (parse_continue(it,tokens,output))                     return;
    if (parse_attempt(it,tokens,output))                      return;
    if (parse_expression(it,tokens,output))                   return;
    throw SyntaxError {"unexpected token", *it};
}

std::vector<Instruction> get_instructions_from_tokens(std::vector<Token>& tokens){ 
    std::vector<Instruction> output;
    std::vector<Token>::iterator it = tokens.begin();
    while (it != tokens.end()) acquire_instruction(it,tokens,output);
    return output;
}