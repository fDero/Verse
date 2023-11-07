#pragma once
#include "../include/verse.hpp"

std::vector<Instruction> get_instructions_from_tokens(std::vector<Token>& tokens);
void acquire_exact_match(std::vector<Token>::iterator&,const std::vector<Token>&,const std::string&);
void acquire_identifier(std::vector<Token>::iterator&,const std::vector<Token>&,std::string&);
void acquire_typesignature(std::vector<Token>::iterator&,const std::vector<Token>&,TypeSignature&);
void acquire_baretype(std::vector<Token>::iterator&,const std::vector<Token>&,std::string&);
void acquire_expression(std::vector<Token>::iterator&,const std::vector<Token>&,std::shared_ptr<Instruction>&);
void acquire_terminal(std::vector<Token>::iterator&,const std::vector<Token>&,std::shared_ptr<Instruction>&);
void acquire_codeblock(std::vector<Token>::iterator&,const std::vector<Token>&,std::vector<Instruction>&);
void acquire_instruction(std::vector<Token>::iterator&,const std::vector<Token>&,std::vector<Instruction>&);
void acquire_generics(std::vector<Token>::iterator&,const std::vector<Token>&,std::vector<TypeSignature>&);
void acquire_simple_generics(std::vector<Token>::iterator&,const std::vector<Token>&,std::vector<TypeSignature>&);
bool parse_instance(std::vector<Token>::iterator&,const std::vector<Token>&,Instance&);
bool parse_struct_definition (std::vector<Token>::iterator&,const std::vector<Token>&,std::vector<Instruction>&, std::shared_ptr<StructDefinition>);
bool parse_function_definition(std::vector<Token>::iterator&,const std::vector<Token>&,std::vector<Instruction>&, std::shared_ptr<FunctionDefinition>);
bool parse_constant(std::vector<Token>::iterator&,const std::vector<Token>&,std::vector<Instruction>&);
bool parse_variable(std::vector<Token>::iterator&,const std::vector<Token>&,std::vector<Instruction>&);
bool parse_conditional(std::vector<Token>::iterator&,const std::vector<Token>&,std::vector<Instruction>&);
bool parse_while_loop(std::vector<Token>::iterator&,const std::vector<Token>&,std::vector<Instruction>&);
bool parse_until_loop(std::vector<Token>::iterator&,const std::vector<Token>&,std::vector<Instruction>&);
bool parse_continue(std::vector<Token>::iterator&,const std::vector<Token>&,std::vector<Instruction>&);
bool parse_break(std::vector<Token>::iterator&,const std::vector<Token>&,std::vector<Instruction>&);
bool parse_return(std::vector<Token>::iterator&,const std::vector<Token>&,std::vector<Instruction>&);
bool parse_defer(std::vector<Token>::iterator&,const std::vector<Token>&,std::vector<Instruction>&);
bool parse_attempt(std::vector<Token>::iterator&,const std::vector<Token>&,std::vector<Instruction>&);
bool parse_expression(std::vector<Token>::iterator&,const std::vector<Token>&,std::vector<Instruction>&);
void operator_precedence_lockout(Instruction&);
void fix_expression(Instruction&);
bool parse_prefix_operator(std::vector<Token>::iterator&,const std::vector<Token>&,Instruction&);
bool parse_infix_operator(std::vector<Token>::iterator&,const std::vector<Token>&,Instruction&);
bool parse_assignment(std::vector<Token>::iterator&,const std::vector<Token>&,Instruction&);
bool parse_terminal(std::vector<Token>::iterator&,const std::vector<Token>&,Instruction&);
bool parse_non_terminated_expression(std::vector<Token>::iterator&,const std::vector<Token>&,std::vector<Instruction>&);