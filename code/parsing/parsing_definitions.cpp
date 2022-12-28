#include "../include/verse.hpp"
#include "../include/procedures.hpp"

bool parse_instantiation(std::vector<Token>::iterator& it, const std::vector<Token>& tokens, std::vector<Instruction>& output){ 
    if(it->sourcetext != "var") return false; 
    std::advance(it,1); 
    std::string name;
    TypeSignature type;
    std::shared_ptr<Instruction> value;
    acquire_identifier(it, tokens, name);
    acquire_exact_match(it,tokens,":");
    acquire_typesignature(it,tokens,type);
    if(it != tokens.end() and it->sourcetext == ";") {
        output.push_back(Instantiation{name, type});
        std::advance(it,1);
        return true;
    } 
    acquire_exact_match(it,tokens,"=");
    acquire_expression(it,tokens,value);
    acquire_exact_match(it,tokens,";");
    output.push_back(Instantiation{name, type});
    std::shared_ptr<Instruction> id = std::make_shared<Instruction>(Identifier{name});
    output.push_back(BinaryOperator{"=",id,value});
    return true;
}

bool parse_struct_definition(std::vector<Token>::iterator& it, const std::vector<Token>& tokens, std::string context, std::vector<Instruction>& output){
    if(it->sourcetext != "struct") return false;
    std::advance(it,1);
    std::string struct_name;
    std::vector<TypeSignature> generics;
    std::vector<Instantiation> internal_state;
    acquire_baretype(it,tokens,struct_name);
    struct_name = updated_context(context,struct_name);
    acquire_exact_match(it,tokens,"{");
    while(it != tokens.end() and it->sourcetext != "}"){
        if (parse_struct_definition(it,tokens,struct_name,output)) continue;
        std::string name;
        TypeSignature type;
        acquire_identifier(it, tokens, name);
        acquire_exact_match(it,tokens,":");
        acquire_typesignature(it,tokens,type);
        acquire_exact_match(it,tokens,";");
        internal_state.push_back(Instantiation{name,type});
    }
    if (it == tokens.end()) throw std::runtime_error("brackets opened but never closed in struct definition");
    std::advance(it,1);
    output.push_back(StructDefinition{struct_name, generics, internal_state});
    return true;
}

bool parse_function_definition(std::vector<Token>::iterator& it, const std::vector<Token>& tokens, std::string context, std::vector<Instruction>& output){    
    if(it->sourcetext != "func") return false;
    std::advance(it,1);
    std::string func_name;
    std::vector<TypeSignature> generics;
    std::vector<Instantiation> arguments;
    std::vector<Instruction> code;
    acquire_identifier(it,tokens,func_name);
    func_name = updated_context(context,func_name);
    acquire_exact_match(it,tokens,"(");
    if (it != tokens.end() and it->sourcetext != ")" and it->sourcetext != ",") do {
        std::advance(it,it->sourcetext == ",");
        std::string name;
        TypeSignature type;
        acquire_identifier(it, tokens, name);
        acquire_exact_match(it,tokens,":");
        acquire_typesignature(it,tokens,type);
        arguments.push_back(Instantiation{name,type});
    } while (it != tokens.end() and it->sourcetext == ",");
    if (it != tokens.end() and it->sourcetext != ")") throw std::runtime_error("unexpected token: " + it->sourcetext + " instead of: )");
    if (it == tokens.end()) throw std::runtime_error("parenthesys opened but never closed");
    std::advance(it,1);
    acquire_exact_match(it,tokens,"{");
    while(it != tokens.end() and it->sourcetext != "}"){
        if (parse_struct_definition(it,tokens,func_name,output))   continue;
        if (parse_function_definition(it,tokens,func_name,output)) continue;
        acquire_instruction(it,tokens,func_name,code);
    }
    if (it == tokens.end() or it->sourcetext != "}") throw std::runtime_error("brackets opened but never closed in function definition");
    std::advance(it,1);
    output.push_back(FunctionDefinition{func_name,generics,arguments,code});
    return true;
}