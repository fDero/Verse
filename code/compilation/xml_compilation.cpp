#include "../include/verse.hpp"
#include "../include/procedures.hpp"

bool convert_instantiation_into_xml(const Instruction& instr, std::fstream& output, const std::string& prefix){
    if (not std::holds_alternative<Instantiation>(instr)) return false;
    Instantiation instance = std::get<Instantiation>(instr);
    std::string typesignature = serialize_type(instance.typesignature);
    output << prefix << ("<INSTANTIATION name=\"" + instance.name + "\" type=\"" + typesignature + "\"/>\n"); 
    return true;
}

bool convert_struct_definition_into_xml(const Instruction& instr, std::fstream& output, const std::string& prefix) {
    if (not std::holds_alternative<StructDefinition>(instr)) return false;
    StructDefinition structdef = std::get<StructDefinition>(instr);
    output << prefix <<  ("<STRUCT name=\"" + structdef.struct_name + "\">\n");
    for (const Instantiation& internal_state_var : structdef.internal_state) {
        std::string typesignature = serialize_type(internal_state_var.typesignature);
        output << prefix << ("\t<FIELD name=\"" + internal_state_var.name + "\" type=\"" + typesignature + "\"/>\n");
    }
    output << prefix <<  ("</STRUCT>\n");
    return true;
}

bool convert_function_definition_into_xml(const Instruction& instr, std::fstream& output, const std::string& prefix){
    if (not std::holds_alternative<FunctionDefinition>(instr)) return false;
    FunctionDefinition funcdef = std::get<FunctionDefinition>(instr);
    output << prefix <<  ("<FUNCDEF name=\"" + funcdef.func_name + "\">\n");
    for (const Instantiation& arg : funcdef.args) {
        std::string typesignature = serialize_type(arg.typesignature);
        output << ("\t<ARG name=\"" + arg.name + "\" type=\"" + typesignature + "\"/>\n");
    }
    output << prefix <<  ("\t<CODE>\n");
    translate_instructions_into_xml(funcdef.code,output, "\t\t" + prefix);
    output << prefix <<  ("\t</CODE>\n");
    output << prefix <<  ("</FUNCDEF>\n");
    return true;
}

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

bool convert_while_into_xml(const Instruction& instr, std::fstream& output, const std::string& prefix){
    if (not std::holds_alternative<WhileLoop>(instr)) return false;
    WhileLoop loop = std::get<WhileLoop>(instr);
    output << prefix <<  ("<WHILE>\n");
    translate_instructions_into_xml({*(loop.condition)},output,"\t" + prefix);
    output << prefix <<  ("\t<CODE>\n");
    translate_instructions_into_xml(loop.code,output,"\t\t" + prefix);
    output << prefix <<  ("\t<CODE>\n");
    output << prefix <<  ("</WHILE>\n");
    return true;
}

bool convert_until_into_xml(const Instruction& instr, std::fstream& output, const std::string& prefix){
    if (not std::holds_alternative<UntilLoop>(instr)) return false;
    UntilLoop loop = std::get<UntilLoop>(instr);
    output << prefix <<  ("<UNTIL>\n");
    translate_instructions_into_xml({*(loop.condition)},output,"\t" + prefix);
    output << prefix <<  ("\t<CODE>\n");
    translate_instructions_into_xml(loop.code,output,"\t\t" + prefix);
    output << prefix <<  ("\t<CODE>\n");
    output << prefix <<  ("</UNTIL>\n");
    return true;
}


bool convert_conditional_into_xml(const Instruction& instr, std::fstream& output, const std::string& prefix){
    if (not std::holds_alternative<Conditional>(instr)) return false;
    Conditional conditional = std::get<Conditional>(instr);
    output << prefix <<  ("<IF>\n");
    translate_instructions_into_xml({*(conditional.condition)},output,"\t" + prefix);
    output << prefix <<  ("\t<THEN>\n");
    translate_instructions_into_xml(conditional.then,output,"\t\t" + prefix);
    output << prefix <<  ("\t</THEN>\n");
    output << prefix <<  ("\t<ELSE>\n");
    translate_instructions_into_xml(conditional.otherwise,output,"\t\t" + prefix);
    output << prefix <<  ("\t</ELSE>\n");
    output << prefix <<  ("</IF>\n");
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

void compile_xml(const std::string& input_filepath, const std::string& output_filepath){
    std::vector<Token> tokens = tokenize_file(input_filepath); 
    std::vector<Token>::iterator primer = tokens.begin();   
    std::fstream output = std::fstream(output_filepath,  std::fstream::in | std::fstream::out | std::fstream::trunc);
    std::vector<Instruction> instructions;
    parse_file(primer, tokens, "", instructions); 
    translate_instructions_into_xml(instructions,output,"");
    output.close(); 
    std::cout << input_filepath << " compiled successfully as " << output_filepath << "\n";
}

void translate_instructions_into_xml(const std::vector<Instruction>& instructions, std::fstream& output, const std::string& prefix){
    for (const auto& instr : instructions) {
        if (convert_instantiation_into_xml(instr,output,prefix))        continue;
        if (convert_binary_operator_into_xml(instr,output,prefix))      continue;
        if (convert_unary_operator_into_xml(instr,output,prefix))       continue;
        if (convert_struct_definition_into_xml(instr,output,prefix))    continue;
        if (convert_function_definition_into_xml(instr,output,prefix))  continue;
        if (convert_function_call_into_xml(instr,output,prefix))        continue;
        if (convert_identifier_into_xml(instr,output,prefix))           continue;
        if (convert_literal_into_xml(instr,output,prefix))              continue;
        if (convert_while_into_xml(instr,output,prefix))                continue;
        if (convert_until_into_xml(instr,output,prefix))                continue;
        if (convert_conditional_into_xml(instr,output,prefix))          continue;
        if (convert_assignment_into_xml(instr,output,prefix))           continue;
        throw std::runtime_error("instruction can't be compiled");
    }
}

std::string serialize_base_type(const TypeSignature& type){
    BaseType base = std::get<BaseType>(type);
    if (base.generics.empty()) return base.base_type;
    std::string serialized = base.base_type + "<";
    for (const TypeSignature& generic : base.generics) serialized += serialize_type(generic) + ",";
    serialized.back() = '>';
    return serialized;
}

std::string serialize_pointer_type(const TypeSignature& type){
    Pointer ptr = std::get<Pointer>(type);
    return serialize_type(*(ptr.pointed)) + "*";
}

std::string serialize_array_type(const TypeSignature& type){
    Array arr = std::get<Array>(type);
    std::string length = (arr.length > 0)? std::to_string(arr.length) : "";
    return serialize_type(*(arr.type)) + "[" + length + "]";
}

std::string serialize_type(const TypeSignature& type){
    if (std::holds_alternative<Pointer>(type)) return serialize_pointer_type(type);
    if (std::holds_alternative<BaseType>(type)) return serialize_base_type(type);
    if (std::holds_alternative<Array>(type)) return serialize_array_type(type);
    throw std::runtime_error("can't serialize ill formed type");
}