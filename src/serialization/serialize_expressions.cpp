#include "../../include/verse.hpp"
#include "../../prototypes/procedures.hpp"

bool convert_function_call_into_xml(const Instruction& instr, std::fstream& output, const std::string& prefix){
    if (not std::holds_alternative<FunctionCall>(instr)) return false;
    FunctionCall funcall = std::get<FunctionCall>(instr);
    output << prefix <<  ("<FUNCALL name=\"" + funcall.func_name + "\">\n");
    translate_instructions_into_xml(funcall.args,output,"\t" + prefix);
    output << prefix << ("</FUNCALL>\n");
    return true;
}

bool convert_identifier_into_xml(const Instruction& instr, std::fstream& output, const std::string& prefix){
    if (not std::holds_alternative<Identifier>(instr)) return false;
    Identifier id = std::get<Identifier>(instr);
    output << prefix <<  ("<IDENTIFIER name=\"" + id.name + "\"/>\n");
    return true;
}

bool convert_literal_into_xml(const Instruction& instr, std::fstream& output, const std::string& prefix){
    if (not std::holds_alternative<Literal>(instr)) return false;
    Literal val = std::get<Literal>(instr);
    std::string value = val.value;
    if (value[0] == '"') value[0] = value.back() = '`'; 
    output << prefix <<  ("<LITERAL value=\"" + value + "\" pseudotype=\"" + val.pseudotype + "\"/>\n");
    return true;
} 

bool convert_binary_operator_into_xml(const Instruction& instr, std::fstream& output, const std::string& prefix){
    if (not std::holds_alternative<BinaryOperator>(instr)) return false;
    BinaryOperator oper = std::get<BinaryOperator>(instr);
    output << prefix <<  ("<OPERATOR text=\"" + oper.text + "\"" + ">\n");
    translate_instructions_into_xml({*(oper.lx)},output,"\t" + prefix);
    translate_instructions_into_xml({*(oper.rx)},output,"\t" + prefix);
    output << prefix <<  ("</OPERATOR>\n");
    return true;
} 

bool convert_unary_operator_into_xml(const Instruction& instr, std::fstream& output, const std::string& prefix){
    if (not std::holds_alternative<UnaryOperator>(instr)) return false;
    UnaryOperator oper = std::get<UnaryOperator>(instr);
    output << prefix <<  ("<OPERATOR text=\"" + oper.text + "\"" + ">\n");
    translate_instructions_into_xml({*(oper.operand)},output,"\t" + prefix);
    output << prefix <<  ("</OPERATOR>\n");
    return true;
} 

bool convert_assignment_into_xml(const Instruction& instr, std::fstream& output, const std::string& prefix){
    if (not std::holds_alternative<Assignment>(instr)) return false;
    Assignment ass = std::get<Assignment>(instr);
    output << prefix <<  ("<ASSIGNMENT>\n");
    translate_instructions_into_xml({*(ass.target)},output,"\t" + prefix);
    translate_instructions_into_xml({*(ass.value)},output,"\t" + prefix);
    output << prefix <<  ("</ASSIGNMENT>\n");
    return true;
}