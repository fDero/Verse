#include "../include/verse.hpp"
#include "../include/procedures.hpp"

bool parse_variable(std::vector<Token>::iterator& it, const std::vector<Token>& tokens, std::vector<Instruction>& output){ 
    if(it->sourcetext != "var") return false; 
    Variable this_var;
    std::shared_ptr<Instruction> value;
    acquire_exact_match(it,tokens,"var");
    acquire_identifier(it, tokens, this_var.name);
    acquire_exact_match(it,tokens,":");
    acquire_typesignature(it,tokens,this_var.typesignature);
    output.push_back(this_var);
    if(it != tokens.end() and it->sourcetext == ";") {
        std::advance(it,1);
        return true;
    } 
    acquire_exact_match(it,tokens,"=");
    acquire_expression(it,tokens,value);
    acquire_exact_match(it,tokens,";");
    std::shared_ptr<Instruction> id = std::make_shared<Instruction>(Identifier{this_var.name});
    output.push_back(Assignment{id,value});
    return true;
}

bool parse_constant(std::vector<Token>::iterator& it, const std::vector<Token>& tokens, std::vector<Instruction>& output){ 
    if(it->sourcetext != "const") return false;
    Constant this_const; 
    acquire_exact_match(it,tokens,"const");
    acquire_identifier(it, tokens, this_const.name);
    acquire_exact_match(it,tokens,":");
    acquire_typesignature(it,tokens,this_const.typesignature);
    acquire_exact_match(it,tokens,"=");
    acquire_expression(it,tokens,this_const.value);
    acquire_exact_match(it,tokens,";");
    output.push_back(this_const);
    return true;
}

bool parse_struct_definition (
    std::vector<Token>::iterator& it, 
    const std::vector<Token>& tokens, 
    std::vector<Instruction>& output, 
    std::shared_ptr<StructDefinition> parent
) {
    if(it->sourcetext != "struct") return false;
    StructDefinition this_struct;
    this_struct.parent_scope = parent;
    acquire_exact_match(it,tokens,"struct");
    acquire_baretype(it,tokens,this_struct.struct_name);
    acquire_simple_generics(it,tokens,this_struct.generics);
    auto expected_brackets_open = it;
    acquire_exact_match(it,tokens,"{");
    while(it != tokens.end() and it->sourcetext != "}"){
        if (it->sourcetext == "func") throw std::runtime_error { "it's illegal to define a function inside of a struct" };
        if (parse_struct_definition(it, tokens, output, std::make_shared<StructDefinition>(this_struct))) continue;
        Instance field;  
        if (!parse_instance(it,tokens,field)) throw SyntaxError { "structs can only contains attributes or nested struct definitions", *it };
        acquire_exact_match(it,tokens,";");
        this_struct.internal_state.push_back(field);
    }
    if (it == tokens.end()) throw SyntaxError { "brackets opened but never closed in struct definition", *expected_brackets_open };
    std::advance(it,1);
    output.push_back(this_struct);
    return true;
}

bool parse_function_definition(
    std::vector<Token>::iterator& it, 
    const std::vector<Token>& tokens, 
    std::vector<Instruction>& output,
    std::shared_ptr<FunctionDefinition> parent
) {    
    if(it->sourcetext != "func") return false;
    FunctionDefinition this_func;
    acquire_exact_match(it,tokens,"func");
    acquire_identifier(it,tokens,this_func.func_name);
    acquire_simple_generics(it,tokens,this_func.generics);
    std::string parent_name = (parent == nullptr)? "global" : parent->func_name;
    this_func.func_name = parent_name + "\\" + this_func.func_name;
    auto expected_parenthesys_opened = it;
    acquire_exact_match(it,tokens,"(");
    if (it != tokens.end() and it->sourcetext != ")" and it->sourcetext != ",") do {
        std::advance(it,it->sourcetext == ",");
        Instance arg; 
        if (!parse_instance(it,tokens,arg)) throw SyntaxError {"unexpected token: " + it->sourcetext + " an argument was expected instead", *it }; 
        this_func.args.push_back(arg);
    } while (it != tokens.end() and it->sourcetext == ",");
    if (it != tokens.end() and it->sourcetext != ")") throw SyntaxError {"unexpected token: " + it->sourcetext + " ')' was expected instead ", *it };
    if (it == tokens.end()) throw SyntaxError {"parenthesys opened but never closed", *expected_parenthesys_opened};
    std::advance(it,1);
    auto expected_brackets_open = it;
    acquire_exact_match(it,tokens,"{");
    while(it != tokens.end() and it->sourcetext != "}"){
        if (it->sourcetext == "struct") throw std::runtime_error { "it's illegal to define a struct inside of a function" };
        if (parse_function_definition(it, tokens, output, std::make_shared<FunctionDefinition>(this_func))) continue;
        acquire_instruction(it,tokens,this_func.code);
    }
    if (it == tokens.end() or it->sourcetext != "}") throw SyntaxError { "brackets opened but never closed in function definition", *expected_brackets_open };
    std::advance(it,1);
    this_func.parent_scope = parent;
    output.push_back(this_func);
    return true;
}