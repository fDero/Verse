#pragma once

//commandline
CommandLine read_commandline(int,char**);
FileExtension file_extension(const std::string& filename);
void compile(const std::vector<std::string>&,const std::vector<std::string>&);
void evaluate(const std::vector<std::string>&,const std::vector<std::string>&);
void debug(const std::vector<std::string>&,const std::vector<std::string>&);
void display_commandline_version();
void display_commandline_help(); 

//lexing
std::vector<Token> get_tokens_from_file(const std::string&);
std::string extract_string(const std::string&,const int,const TokenInfo&);
std::string extract_symbol(const std::string&,const int,const TokenInfo&);
std::string extract_number(const std::string&,const int,const TokenInfo&);
std::string extract_text(const std::string&,const int,const TokenInfo&);

//parsing
std::vector<Instruction> get_instructions_from_tokens(std::vector<Token>& tokens);
void acquire_exact_match(std::vector<Token>::iterator&,const std::vector<Token>&,const std::string&);
void acquire_identifier(std::vector<Token>::iterator&,const std::vector<Token>&,std::string&);
void acquire_typesignature(std::vector<Token>::iterator&,const std::vector<Token>&,TypeSignature&);
void acquire_baretype(std::vector<Token>::iterator&,const std::vector<Token>&,std::string&);
void acquire_expression(std::vector<Token>::iterator&,const std::vector<Token>&,std::shared_ptr<Instruction>&);
void acquire_terminal(std::vector<Token>::iterator&,const std::vector<Token>&,std::shared_ptr<Instruction>&);
void acquire_codeblock(std::vector<Token>::iterator&,const std::vector<Token>&,std::vector<Instruction>&);
void acquire_instruction(std::vector<Token>::iterator&,const std::vector<Token>&,std::vector<Instruction>&);
void acquire_instance(std::vector<Token>::iterator&,const std::vector<Token>&,Instance&);
void acquire_generics(std::vector<Token>::iterator&,const std::vector<Token>&,std::vector<TypeSignature>&);
void acquire_simple_generics(std::vector<Token>::iterator&,const std::vector<Token>&,std::vector<TypeSignature>&);
bool parse_struct_definition(std::vector<Token>::iterator&,const std::vector<Token>&,std::vector<Instruction>&);
bool parse_function_definition(std::vector<Token>::iterator&,const std::vector<Token>&,std::vector<Instruction>&);
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

//seialization
std::string serialize_type(const TypeSignature&);
std::string serialize_generics(const std::vector<TypeSignature>&);
void translate_tokens_into_json(const std::vector<Token>&,std::fstream&);
void translate_instructions_into_xml(const std::vector<Instruction>&,std::fstream&,const std::string&);
void compile_json(const std::vector<std::string>&,const std::string&);
void compile_xml(const std::vector<std::string>&,const std::string&);
bool convert_variable_into_xml(const Instruction& instr, std::fstream& output, const std::string& prefix);
bool convert_constant_into_xml(const Instruction& instr, std::fstream& output, const std::string& prefix);
bool convert_struct_definition_into_xml(const Instruction& instr, std::fstream& output, const std::string& prefix);
bool convert_function_definition_into_xml(const Instruction& instr, std::fstream& output, const std::string& prefix);
bool convert_function_call_into_xml(const Instruction& instr, std::fstream& output, const std::string& prefix);
bool convert_identifier_into_xml(const Instruction& instr, std::fstream& output, const std::string& prefix);
bool convert_literal_into_xml(const Instruction& instr, std::fstream& output, const std::string& prefix);
bool convert_binary_operator_into_xml(const Instruction& instr, std::fstream& output, const std::string& prefix);
bool convert_unary_operator_into_xml(const Instruction& instr, std::fstream& output, const std::string& prefix);
bool convert_assignment_into_xml(const Instruction& instr, std::fstream& output, const std::string& prefix);
bool convert_while_into_xml(const Instruction& instr, std::fstream& output, const std::string& prefix);
bool convert_until_into_xml(const Instruction& instr, std::fstream& output, const std::string& prefix);
bool convert_conditional_into_xml(const Instruction& instr, std::fstream& output, const std::string& prefix);
bool convert_continue_into_xml(const Instruction& instr, std::fstream& output, const std::string& prefix);
bool convert_break_into_xml(const Instruction& instr, std::fstream& output, const std::string& prefix);
bool convert_return_into_xml(const Instruction& instr, std::fstream& output, const std::string& prefix);
bool convert_defer_into_xml(const Instruction& instr, std::fstream& output, const std::string& prefix);
bool convert_attempt_into_xml(const Instruction& instr, std::fstream& output, const std::string& prefix);