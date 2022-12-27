#pragma once

//tokenization
std::vector<Token> tokenize_file(const std::string& input_filepath);

//parsing
std::string updated_context(const std::string& context, const std::string& scope);
void acquire_exact_match(std::vector<Token>::iterator& it, const std::vector<Token>& tokens, const std::string& match);
void acquire_identifier(std::vector<Token>::iterator& it, const std::vector<Token>& tokens, std::string& name);
void acquire_typesignature(std::vector<Token>::iterator& it, const std::vector<Token>& tokens, std::string& type);
void acquire_expression(std::vector<Token>::iterator& it, const std::vector<Token>& tokens, std::shared_ptr<Instruction>& value);
void acquire_terminal(std::vector<Token>::iterator& it, const std::vector<Token>& tokens, std::shared_ptr<Instruction>& value);

bool parse_instantiation(std::vector<Token>::iterator& it, const std::vector<Token>& tokens, std::vector<Instruction>& output);
bool parse_struct_definition(std::vector<Token>::iterator& it, const std::vector<Token>& tokens, std::string context, std::vector<Instruction>& output);
bool parse_function_definition(std::vector<Token>::iterator& it, const std::vector<Token>& tokens, std::string context, std::vector<Instruction>& output);
bool parse_conditional_statement(std::vector<Token>::iterator& it, const std::vector<Token>& tokens, std::vector<Instruction>& output);
bool parse_while_loop(std::vector<Token>::iterator& it, const std::vector<Token>& tokens, std::vector<Instruction>& output);
bool parse_until_loop(std::vector<Token>::iterator& it, const std::vector<Token>& tokens, std::vector<Instruction>& output);
bool parse_expression(std::vector<Token>::iterator& it, const std::vector<Token>& tokens, std::vector<Instruction>& output);

bool parse_prefix_operator(std::vector<Token>::iterator& it, const std::vector<Token>& tokens, Instruction& target);
bool parse_infix_operator(std::vector<Token>::iterator& it, const std::vector<Token>& tokens, Instruction& target);
bool parse_terminal(std::vector<Token>::iterator& it, const std::vector<Token>& tokens, Instruction& target);
void fix_expression(Instruction& expr);
void operator_precedence_lockout(Instruction& expr);
bool parse_assignment(std::vector<Token>::iterator& it, const std::vector<Token>& tokens, Instruction& expr);

bool parse_non_terminated_expression(std::vector<Token>::iterator& it, const std::vector<Token>& tokens, std::vector<Instruction>& output);
void parse_instruction(std::vector<Token>::iterator& it, const std::vector<Token>& tokens, std::string context, std::vector<Instruction>& output);
void parse_file(std::vector<Token>::iterator& it, const std::vector<Token>& tokens, std::string context, std::vector<Instruction>& output);

//compilation
void compile_json(const std::string& input_filepath, const std::string& output_filepath);
void compile_xml(const std::string& input_filepath, const std::string& output_filepath);
void translate_instructions_into_xml(const std::vector<Instruction>& instructions, std::fstream& output, const std::string& prefix);