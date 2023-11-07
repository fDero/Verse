#include "../../include/verse.hpp"
#include "../../prototypes/procedures.hpp"

void translate_tokens_into_json(const std::vector<Token>& tokens, std::fstream& output){
    for (auto it = tokens.begin(); it != tokens.end(); it++){
        std::string text = it->sourcetext;
        if (text[0] == '"') text[0] = text.back() = '`'; 
        output << "\n" << "\t" << "{";
        output << "\n" << "\t" << "\t\"sourcetext\":\""  << text             << "\",";
        output << "\n" << "\t" << "\t\"file_name\":\""   << it->filename     << "\",";
        output << "\n" << "\t" << "\t\"line_number\":"   << it->line_number  << ",";
        output << "\n" << "\t" << "\t\"token_number\":"  << it->tok_number   << ",";
        output << "\n" << "\t" << "\t\"char_pos\":"      << it->char_pos;     
        output << "\n" << "\t" << "}"; 
        output << (std::next(it) == tokens.end()? "" : ",");
    }
    
}

void compile_json(const std::vector<std::string>& input_files, const std::string& output_filepath){
    std::fstream output = std::fstream(output_filepath,  std::fstream::in | std::fstream::out | std::fstream::trunc);
    output.close();
    output = std::fstream(output_filepath, std::ios_base::app);
    output << "[";
    output << "\n\t\" files: "; for (const std::string& input : input_files) output << input << " "; output  << "\"";
    for (const std::string& input : input_files){
        output << ",";
        std::vector<Token> tokens = get_tokens_from_file(input);
        translate_tokens_into_json(tokens, output);
    }
    output << "\n]";
    output.close(); 
}

void compile_xml(const std::vector<std::string>& input_files, const std::string& output_filepath){
    std::fstream output = std::fstream(output_filepath,  std::fstream::in | std::fstream::out | std::fstream::trunc);
    output.close();
    output = std::fstream(output_filepath, std::ios_base::app);
    for (const std::string& input : input_files){
        std::vector<Token> tokens = get_tokens_from_file(input); 
        std::vector<Instruction> instructions = get_instructions_from_tokens(tokens);
        output << "<!-- file: " << input << " -->\n";
        translate_instructions_into_xml(instructions,output,"");  
    }
    output.close();
}

void translate_instructions_into_xml(const std::vector<Instruction>& instructions, std::fstream& output, const std::string& prefix){
    for (const auto& instr : instructions) {
        if (convert_variable_into_xml(instr,output,prefix))             continue;
        if (convert_constant_into_xml(instr,output,prefix))             continue;
        if (convert_binary_operator_into_xml(instr,output,prefix))      continue;
        if (convert_unary_operator_into_xml(instr,output,prefix))       continue;
        if (convert_struct_definition_into_xml(instr,output,prefix))    continue;
        if (convert_function_definition_into_xml(instr,output,prefix))  continue;
        if (convert_function_call_into_xml(instr,output,prefix))        continue;
        if (convert_identifier_into_xml(instr,output,prefix))           continue;
        if (convert_literal_into_xml(instr,output,prefix))              continue;
        if (convert_assignment_into_xml(instr,output,prefix))           continue;
        if (convert_while_into_xml(instr,output,prefix))                continue;
        if (convert_until_into_xml(instr,output,prefix))                continue;
        if (convert_conditional_into_xml(instr,output,prefix))          continue;
        if (convert_continue_into_xml(instr,output,prefix))             continue;
        if (convert_break_into_xml(instr,output,prefix))                continue;
        if (convert_defer_into_xml(instr,output,prefix))                continue;
        if (convert_return_into_xml(instr,output,prefix))               continue;
        if (convert_attempt_into_xml(instr,output,prefix))              continue;
        throw std::runtime_error("instruction can't be compiled");
    }
}

std::string serialize_generics(const std::vector<TypeSignature>& generics){
    if (generics.empty()) return "";
    std::string result = " generics=\"";
    for (const TypeSignature& generic : generics) result += serialize_type(generic) + ",";
    result.back() = '"';
    return result;
}

std::string serialize_base_type(const TypeSignature& type){
    BaseType base = std::get<BaseType>(type);
    if (base.generics.empty()) return base.base_type;
    std::string serialized = base.base_type + "<";
    for (const TypeSignature& generic : base.generics) serialized += serialize_type(generic) + ",";
    serialized.back() = '>';
    return serialized;
}

std::string serialize_nested_type(const TypeSignature& type){
    NestedType base = std::get<NestedType>(type);
    return serialize_type(*base.left) + "." + serialize_base_type(*base.right);
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
    if (std::holds_alternative<NestedType>(type)) return serialize_nested_type(type);
    throw std::runtime_error("can't serialize ill formed type");
}