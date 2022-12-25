#include "../include/defs.hpp"
#include "../include/procedures.hpp"

bool parse_instantiation(std::vector<Token>::iterator& it, const std::vector<Token>& tokens, std::vector<Instruction>& output){ 
    std::string name, type;
    std::shared_ptr<Instruction> value;
    if(it->sourcetext == "var") std::advance(it,1); 
    else return false;
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
    output.push_back(Assignment{name, value});
    return true;
}

bool parse_struct_definition(std::vector<Token>::iterator& it, const std::vector<Token>& tokens, std::string context, std::vector<Instruction>& output){
    std::string struct_name;
    std::vector<Instantiation> internal_state;
    if(it->sourcetext == "struct") std::advance(it,1);
    else return false;
    acquire_typesignature(it,tokens,struct_name);
    struct_name = updated_context(context,struct_name);
    acquire_exact_match(it,tokens,"{");
    while(it != tokens.end() and it->sourcetext != "}"){
        if (parse_struct_definition(it,tokens,struct_name,output)) continue;
        std::string name, type;
        acquire_identifier(it, tokens, name);
        acquire_exact_match(it,tokens,":");
        acquire_typesignature(it,tokens,type);
        acquire_exact_match(it,tokens,";");
        internal_state.push_back(Instantiation{name,type});
    }
    if (it == tokens.end()) throw std::runtime_error("brackets opened but never closed in struct definition");
    std::advance(it,1);
    output.push_back(StructDefinition{struct_name, internal_state});
    return true;
}

bool parse_function_definition(std::vector<Token>::iterator& it, const std::vector<Token>& tokens, std::string context, std::vector<Instruction>& output){    
    std::string func_name;
    std::vector<Instantiation> arguments;
    std::vector<Instruction> code;
    if(it->sourcetext == "func") std::advance(it,1);
    else return false;
    acquire_identifier(it,tokens,func_name);
    func_name = updated_context(context,func_name);
    acquire_exact_match(it,tokens,"(");
    if (it != tokens.end() and it->sourcetext != ")" and it->sourcetext != ",") do {
        std::advance(it,it->sourcetext == ",");
        std::string name, type;
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
        parse_instruction(it,tokens,func_name,code);
    }
    if (it == tokens.end() or it->sourcetext != "}") throw std::runtime_error("brackets opened but never closed in function definition");
    std::advance(it,1);
    output.push_back(FunctionDefinition{func_name,arguments,code});
    return true;
}
