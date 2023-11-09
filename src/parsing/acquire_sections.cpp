#include "../../include/verse.hpp"
#include "../../prototypes/procedures.hpp"

void acquire_expression(std::vector<Token>::iterator& it, const std::vector<Token>& tokens, std::shared_ptr<Instruction>& value){
    std::vector<Instruction> expression_wrapper;
    auto expected_expression_position = it;
    if (not parse_non_terminated_expression(it,tokens, expression_wrapper)) {
        std::string found = (it == tokens.end())? "(END OF FILE)" : it->sourcetext;
        throw SyntaxError { "unexpected token: " + found + " instead of that, an expression was expected", *expected_expression_position };
    }
    value = std::make_shared<Instruction>(expression_wrapper[0]);
}

void acquire_codeblock(std::vector<Token>::iterator& it, const std::vector<Token>& tokens, std::vector<Instruction>& code){
    if (it != tokens.end() and it->sourcetext != "{") {
        auto single_line_codeblock_begin = it;
        if (it->sourcetext == "struct") throw SyntaxError { "struct definitions not allowed in single-line codeblock", *single_line_codeblock_begin };
        if (it->sourcetext == "func")   throw SyntaxError { "function definitions not allowed in single-line codeblock", *single_line_codeblock_begin };
        acquire_instruction(it,tokens,code);
    } 
    else {
        auto brackets_opened = it;
        acquire_exact_match(it,tokens,"{");
        while(it != tokens.end() and it->sourcetext != "}") {
            auto begin_current_line_in_multiline_codeblock = it;
            if (it->sourcetext == "struct") throw SyntaxError { "struct definitions not allowed in multi-line codeblock", *begin_current_line_in_multiline_codeblock };
            if (it->sourcetext == "func")   throw SyntaxError { "function definitions not allowed in multi-line codeblock", *begin_current_line_in_multiline_codeblock };
            acquire_instruction(it,tokens,code);
        }
        if (it == tokens.end() or it->sourcetext != "}") throw SyntaxError { "brackets opened but never closed", *brackets_opened };
        std::advance(it,1);
    }
}

void acquire_struct_state_section(
    std::vector<Token>::iterator& it, const std::vector<Token>& tokens, 
    std::vector<Instruction>& output, std::shared_ptr<StructDefinition> parent,
    StructDefinition& this_struct
){
    auto expected_brackets_open = it;
    acquire_exact_match(it,tokens,"{");
    while(it != tokens.end() and it->sourcetext != "}"){
        if (it->sourcetext == "func") throw std::runtime_error { "it's illegal to define a function inside of a struct" };
        if (parse_struct_definition(it, tokens, output, std::make_shared<StructDefinition>(this_struct))) continue;
        acquire_field(it, tokens, this_struct.internal_state);
    }
    if (it == tokens.end()) throw SyntaxError { "brackets opened but never closed in struct definition", *expected_brackets_open };
    std::advance(it,1);
}

void acquire_function_definition_arguments_section(
    std::vector<Token>::iterator& it, const std::vector<Token>& tokens, 
    std::vector<Instruction>& output, std::shared_ptr<FunctionDefinition> parent,
    FunctionDefinition& this_func
){
    auto expected_parenthesys_opened = it;
    acquire_exact_match(it,tokens,"(");
    if (it != tokens.end() and it->sourcetext != ")" and it->sourcetext != ",") do {
        std::advance(it,it->sourcetext == ",");
        acquire_argument(it, tokens, this_func.args);
    } while (it != tokens.end() and it->sourcetext == ",");
    if (it == tokens.end()) throw SyntaxError {"parenthesys opened but never closed", *expected_parenthesys_opened};
    if (it->sourcetext != ")") throw SyntaxError {"unexpected token: " + it->sourcetext + " ')' was expected instead ", *it };
    std::advance(it,1);
}

void acquire_function_definition_code_section(
    std::vector<Token>::iterator& it, const std::vector<Token>& tokens, 
    std::vector<Instruction>& output, std::shared_ptr<FunctionDefinition> parent, 
    FunctionDefinition& this_func
){
    auto expected_brackets_open = it;
    acquire_exact_match(it,tokens,"{");
    while(it != tokens.end() and it->sourcetext != "}"){
        if (it->sourcetext == "struct") throw std::runtime_error { "it's illegal to define a struct inside of a function" };
        if (parse_function_definition(it, tokens, output, std::make_shared<FunctionDefinition>(this_func))) continue;
        acquire_instruction(it,tokens,this_func.code);
    }
    if (it == tokens.end() or it->sourcetext != "}") throw SyntaxError { "brackets opened but never closed in function definition", *expected_brackets_open };
    std::advance(it,1);
}