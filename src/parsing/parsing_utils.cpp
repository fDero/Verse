#include "../include/verse.hpp"
#include "../include/procedures.hpp"

void acquire_instruction(std::vector<Token>::iterator& it, const std::vector<Token>& tokens, std::vector<Instruction>& output){
    if (parse_variable(it,tokens,output))                     return;
    if (parse_constant(it,tokens,output))                     return;
    if (parse_struct_definition(it,tokens,output,"global"))   return;
    if (parse_function_definition(it,tokens,output,"global")) return;
    if (parse_conditional(it,tokens,output))                  return;
    if (parse_while_loop(it,tokens,output))                   return;
    if (parse_until_loop(it,tokens,output))                   return;
    if (parse_return(it,tokens,output))                       return;
    if (parse_defer(it,tokens,output))                        return;
    if (parse_break(it,tokens,output))                        return;
    if (parse_continue(it,tokens,output))                     return;
    if (parse_attempt(it,tokens,output))                      return;
    if (parse_expression(it,tokens,output))                   return;
    throw SyntaxError {"unexpected token", *it};
}

std::vector<Instruction> get_instructions_from_tokens(std::vector<Token>& tokens){ 
    std::vector<Instruction> output;
    std::vector<Token>::iterator it = tokens.begin();
    while (it != tokens.end()) acquire_instruction(it,tokens,output);
    return output;
}

std::set<std::string> forbidden_identifiers {
    "if", "else", "while", "until", "struct", "var", "const", 
    "func", "defer", "attempt", "continue", "break"
};

void acquire_exact_match(std::vector<Token>::iterator& it, const std::vector<Token>& tokens, const std::string& match){
    auto expected_match_position = it;
    bool is_match = (it != tokens.end() and it->sourcetext == match);
    std::advance(it,is_match);
    std::string found = (it == tokens.end())? "(END OF FILE)" : it->sourcetext;
    if(not is_match) throw SyntaxError {"unexpected token: " + found + " instead of: " + match, *expected_match_position };
}

void acquire_identifier(std::vector<Token>::iterator& it, const std::vector<Token>& tokens, std::string& name){    
    auto expected_identifier_position = it;
    bool is_identifier = (it != tokens.end() and isalpha(it->sourcetext[0]) and islower(it->sourcetext[0]));
    name = (is_identifier)? it->sourcetext : "/ERROR";
    if(forbidden_identifiers.find(it->sourcetext) != forbidden_identifiers.end()) throw SyntaxError { "use of a forbidden name as identifier", *it};
    std::advance(it,is_identifier);
    std::string found = (it == tokens.end())? "(END OF FILE)" : it->sourcetext;
    if(not is_identifier) throw SyntaxError { "unexpected token: " + found + " an identifier was expected instead", *expected_identifier_position };
}

bool parse_instance(std::vector<Token>::iterator& it, const std::vector<Token>& tokens, Instance& target){
    if (forbidden_identifiers.find(it->sourcetext) != forbidden_identifiers.end()) return false;
    acquire_identifier(it, tokens, target.name);
    acquire_exact_match(it,tokens,":");
    acquire_typesignature(it,tokens,target.typesignature);
    return true;
}

void acquire_baretype(std::vector<Token>::iterator& it, const std::vector<Token>& tokens, std::string& type){
    auto expected_type_position = it;
    bool is_type = (it != tokens.end() and isalpha(it->sourcetext[0]) and isupper(it->sourcetext[0]));
    type = (is_type)? it->sourcetext : "/ERROR";
    std::advance(it,is_type);
    std::string found = (it == tokens.end())? "(END OF FILE)" : it->sourcetext;
    if(not is_type) throw SyntaxError { "unexpected token: " + found + " a typesignature was expacted instead", *expected_type_position };
}

void acquire_generics(std::vector<Token>::iterator& it, const std::vector<Token>& tokens, std::vector<TypeSignature>& generics){
    if (it == tokens.end() or it->sourcetext != "<") return;
    do {
        std::advance(it,1);
        TypeSignature generic;
        acquire_typesignature(it,tokens,generic);    
        generics.push_back(generic);
    } while (it != tokens.end() and it->sourcetext == ",");
    acquire_exact_match(it,tokens,">");
}

void acquire_simple_generics(std::vector<Token>::iterator& it, const std::vector<Token>& tokens, std::vector<TypeSignature>& generics){
    if (it == tokens.end() or it->sourcetext != "<") return;
    do {
        std::advance(it,1);
        std::string generic_base_type;
        acquire_baretype(it,tokens,generic_base_type);    
        generics.push_back(BaseType{generic_base_type,{}});
    } while (it != tokens.end() and it->sourcetext == ",");
    acquire_exact_match(it,tokens,">");
}

void acquire_typesignature_utility(std::vector<Token>::iterator& it, const std::vector<Token>& tokens, TypeSignature& type){
    std::string base_type;
    std::vector<TypeSignature> generics;
    acquire_baretype(it,tokens,base_type);
    acquire_generics(it,tokens,generics);
    type = BaseType{base_type,generics};
    while (it != tokens.end() and it->sourcetext == "."){
        std::advance(it,1);
        TypeSignature following_type_specs;
        acquire_typesignature_utility(it, tokens, following_type_specs);
        std::shared_ptr<TypeSignature> type_ptr = std::make_shared<TypeSignature>(type);
        std::shared_ptr<TypeSignature> following_ptr = std::make_shared<TypeSignature>(following_type_specs);
        type = NestedType { type_ptr, following_ptr };    
    }
}

void acquire_typesignature(std::vector<Token>::iterator& it, const std::vector<Token>& tokens, TypeSignature& type){
    if (it != tokens.end() and it->sourcetext == "#"){
        acquire_exact_match(it, tokens, "#");
        acquire_typesignature(it, tokens, type);
        type = Pointer{std::make_shared<TypeSignature>(type)};
    }
    else {
        acquire_typesignature_utility(it, tokens, type);
    }
}

void acquire_expression(std::vector<Token>::iterator& it, const std::vector<Token>& tokens, std::shared_ptr<Instruction>& value){
    std::vector<Instruction> expression_wrapper;
    auto expected_expression_position = it;
    if (not parse_non_terminated_expression(it,tokens, expression_wrapper)) {
        std::string found = (it == tokens.end())? "(END OF FILE)" : it->sourcetext;
        throw SyntaxError { "unexpected token: " + found + " instead of that, an expression was expected", *expected_expression_position };
    }
    value = std::make_shared<Instruction>(expression_wrapper[0]);
}

void acquire_terminal(std::vector<Token>::iterator& it, const std::vector<Token>& tokens, std::shared_ptr<Instruction>& value){
    Instruction terminal;
    auto expected_terminal_position = it;
    if (not parse_terminal(it,tokens, terminal)) {
        std::string found = (it == tokens.end())? "(END OF FILE)" : it->sourcetext;
        throw SyntaxError { "unexpected token: " + found + " instead of that, a terminal was expected", *expected_terminal_position };
    }
    value = std::make_shared<Instruction>(terminal);
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