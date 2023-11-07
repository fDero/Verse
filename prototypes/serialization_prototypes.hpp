#pragma once
#include "../include/verse.hpp"

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