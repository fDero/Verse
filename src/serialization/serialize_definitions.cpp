#include "../include/verse.hpp"
#include "../include/procedures.hpp"

bool convert_variable_into_xml(const Instruction& instr, std::fstream& output, const std::string& prefix){
    if (not std::holds_alternative<Variable>(instr)) return false;
    Variable var = std::get<Variable>(instr);
    std::string typesignature = serialize_type(var.typesignature);
    output << prefix << ("<VAR name=\"" + var.name + "\" type=\"" + typesignature + "\"/>\n"); 
    return true;
}

bool convert_constant_into_xml(const Instruction& instr, std::fstream& output, const std::string& prefix){
    if (not std::holds_alternative<Constant>(instr)) return false;
    Constant constant = std::get<Constant>(instr);
    std::string typesignature = serialize_type(constant.typesignature);
    output << prefix << ("<CONST name=\"" + constant.name + "\" type=\"" + typesignature + "\">\n");
    translate_instructions_into_xml({*(constant.value)},output,"\t" + prefix);
    output << prefix << ("</CONST>\n");
    return true;
}

bool convert_struct_definition_into_xml(const Instruction& instr, std::fstream& output, const std::string& prefix) {
    if (not std::holds_alternative<StructDefinition>(instr)) return false;
    StructDefinition structdef = std::get<StructDefinition>(instr);
    std::string generics = serialize_generics(structdef.generics);
    output << prefix <<  ("<STRUCT name=\"" + structdef.struct_name + "\"" + generics + ">\n");
    translate_instructions_into_xml(structdef.internal_definitions,output,"\t"+prefix);
    for (const Instance& internal_state_var : structdef.internal_state) {
        std::string typesignature = serialize_type(internal_state_var.typesignature);
        output << prefix << ("\t<FIELD name=\"" + internal_state_var.name + "\" type=\"" + typesignature + "\"/>\n");
    }
    output << prefix <<  ("</STRUCT>\n");
    return true;
}

bool convert_function_definition_into_xml(const Instruction& instr, std::fstream& output, const std::string& prefix){
    if (not std::holds_alternative<FunctionDefinition>(instr)) return false;
    FunctionDefinition funcdef = std::get<FunctionDefinition>(instr);
    std::string generics = serialize_generics(funcdef.generics);
    output << prefix <<  ("<FUNCDEF name=\"" + funcdef.func_name + "\"" + generics + ">\n");
    for (const Instance& arg : funcdef.args) {
        std::string typesignature = serialize_type(arg.typesignature);
        output << prefix << ("\t<ARG name=\"" + arg.name + "\" type=\"" + typesignature + "\"/>\n");
    }
    translate_instructions_into_xml(funcdef.internal_definitions,output,"\t"+prefix);
    translate_instructions_into_xml(funcdef.code,output, "\t" + prefix);
    output << prefix <<  ("</FUNCDEF>\n");
    return true;
}