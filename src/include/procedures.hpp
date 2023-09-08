#pragma once
#include "verse.hpp"

//commandline
CommandLine read_commandline(int,char**);
FileExtension file_extension(const std::string& filename);
void compile(const std::vector<std::string>&,const std::vector<std::string>&);
void run(const std::vector<std::string>&,const std::vector<std::string>&);
void debug(const std::vector<std::string>&,const std::vector<std::string>&);
void display_commandline_version();
void display_commandline_help(); 

//errors
void assert_unreachable();
void display_commandline_error(const CommandLineError&);
void display_tokenization_error(const TokenizationError&);
void display_syntax_error(const SyntaxError&);
void display_ICE(const InternalCompilerError&);

//commandline utilities
inline std::string red(const std::string& str)    { return std::string("\e[0;31m") + str + std::string("\e[0;0m"); }
inline std::string green(const std::string& str)  { return std::string("\e[0;32m") + str + std::string("\e[0;0m"); }
inline std::string yellow(const std::string& str) { return std::string("\e[0;33m") + str + std::string("\e[0;0m"); }
inline std::string blue(const std::string& str)   { return std::string("\e[0;34m") + str + std::string("\e[0;0m"); }
inline std::string purple(const std::string& str) { return std::string("\e[0;35m") + str + std::string("\e[0;0m"); }
inline std::string aqua(const std::string& str)   { return std::string("\e[0;36m") + str + std::string("\e[0;0m"); }
inline std::string gray(const std::string& str)   { return std::string("\e[0;37m") + str + std::string("\e[0;0m"); }

inline std::string bold_red(const std::string& str)    { return std::string("\e[1;31m") + str + std::string("\e[0;0m"); }
inline std::string bold_green(const std::string& str)  { return std::string("\e[1;32m") + str + std::string("\e[0;0m"); }
inline std::string bold_yellow(const std::string& str) { return std::string("\e[1;33m") + str + std::string("\e[0;0m"); }
inline std::string bold_blue(const std::string& str)   { return std::string("\e[1;34m") + str + std::string("\e[0;0m"); }
inline std::string bold_purple(const std::string& str) { return std::string("\e[1;35m") + str + std::string("\e[0;0m"); }
inline std::string bold_aqua(const std::string& str)   { return std::string("\e[1;36m") + str + std::string("\e[0;0m"); }
inline std::string bold_gray(const std::string& str)   { return std::string("\e[1;37m") + str + std::string("\e[0;0m"); }

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

//preprocessing
FunctionDefinition find_main_entry_point();
void fully_qualify_struct_field_typesignature(TypeSignature&,StructDefinition&);
void init_global_definitions_table(const std::vector<std::string>&);
void fully_qualify_struct_fields();

//generics
TypeSignature apply_generics_to_typesignature(const TypeSignature&,const GenericsLookupTable&);
StructDefinition apply_generics_to_struct_definition(const StructDefinition&, const GenericsLookupTable&);
StructDefinition retrieve_and_instanciate_struct(const TypeSignature&);

//scoping
StructDefinition retrieve_struct_definition(const TypeSignature&);
FunctionDefinition retrieve_function_overload(const std::string&,const ArgumentTypes&,ExecutionContext&);

//interpreter
Instruction execute_instruction(const Instruction&,ExecutionContext&);
Instruction execute_conditional(const Conditional&, ExecutionContext&);
Instruction execute_until_loop(const UntilLoop&, ExecutionContext&);
Instruction execute_while_loop(const WhileLoop&, ExecutionContext&);
BinaryOperatorData execute_standard_binary_operator(const BinaryOperator&,ExecutionContext&);
ExpressionResult dot_access_on_struct_member(const Instruction&,ExecutionContext&);
ExpressionResult execute_function_call(const FunctionCall&,ExecutionContext&);
ExpressionResult execute_function_body(const FunctionDefinition&,ExecutionContext&);
ExpressionResult execute_math_binary_operator(const BinaryOperator&,ExecutionContext&);
ExpressionResult execute_logical_binary_operator(const BinaryOperator&,ExecutionContext&);
ExpressionResult execute_logical_unary_operator(const UnaryOperator&,ExecutionContext&);
ExpressionResult execute_math_unary_operator(const UnaryOperator&,ExecutionContext&);
ExpressionResult execute_expression(const Instruction&,ExecutionContext&);
ExpressionResult execute_logical_not(const Instruction&,ExecutionContext&);
ExpressionResult execute_minus_sign(const Instruction&,ExecutionContext&);
ExpressionResult execute_plus_sign(const Instruction&,ExecutionContext&);
ExpressionResult execute_address_operator(const Instruction&,ExecutionContext&);
ExpressionResult verselang_print_macro(const std::vector<RuntimeValue>&);
RuntimeValue default_value(const TypeSignature&);
void execute_assignment(const Assignment&, ExecutionContext&);
void define_variable(const Variable&, ExecutionContext&);
void define_constant(const Constant&, ExecutionContext&);
void initialize_print_macros();
void initialize_type_macros();

//typesystem
bool typesignatures_are_equal(const TypeSignature&, const TypeSignature&);;
bool is_default_integral_type(const TypeSignature&);
std::string type_to_string_without_generics(const TypeSignature&);
std::string type_to_string(const TypeSignature&);
std::string get_qualified_struct_name(const StructDefinition&);
std::string most_derived_type(const TypeSignature&);
InstanciatedGenerics get_instanciated_generics(const TypeSignature&);
TemplateGenerics get_template_generics(const StructDefinition&);
GenericsLookupTable get_generics_lookup_table(const TemplateGenerics&,const InstanciatedGenerics&);