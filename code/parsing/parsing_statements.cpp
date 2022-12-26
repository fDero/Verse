#include "../include/defs.hpp"
#include "../include/procedures.hpp"

bool x_parse_function_definition(std::vector<Token>::iterator& it, const std::vector<Token>& tokens, std::string context, std::vector<Instruction>& output){    
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

bool parse_conditional_statement(std::vector<Token>::iterator& it, const std::vector<Token>& tokens, std::vector<Instruction>& output){
    return false;
}

bool parse_while_loop(std::vector<Token>::iterator& it, const std::vector<Token>& tokens, std::vector<Instruction>& output){
    /* if (it->sourcetext != "while") return false;
    std::advance(it,1);
    std::shared_ptr<Instruction> condition;
    acquire_expression(it,tokens,condition);
    acquire_exact_match(it,tokens,"{");
    std::vector<Instruction> code;
    while(it != tokens.end() and it->sourcetext != "}") parse_instruction(it,tokens,"",code);
    if (it == tokens.end() or it->sourcetext != "}") throw std::runtime_error("brackets opened but never closed in while loop");
    std::advance(it,1);
    output.push_back(WhileLoop{condition,code});
    return true; */
    return false;
}

bool parse_until_loop(std::vector<Token>::iterator& it, const std::vector<Token>& tokens, std::vector<Instruction>& output){
    return false;
}