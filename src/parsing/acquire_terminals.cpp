#include "../../include/verse.hpp"
#include "../../prototypes/procedures.hpp"

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

void acquire_argument(std::vector<Token>::iterator& it, const std::vector<Token>& tokens, std::vector<Instance>& args){
    if (forbidden_identifiers.find(it->sourcetext) != forbidden_identifiers.end()) {
        throw SyntaxError {"unexpected token: " + it->sourcetext + " an argument was expected instead", *it};
    }
    Instance arg;
    acquire_identifier(it, tokens, arg.name);
    acquire_exact_match(it,tokens,":");
    acquire_typesignature(it,tokens,arg.typesignature);
    args.push_back(arg);
}

void acquire_field(std::vector<Token>::iterator& it, const std::vector<Token>& tokens, std::vector<Instance>& fields){
    if (forbidden_identifiers.find(it->sourcetext) != forbidden_identifiers.end()) {
        throw SyntaxError {"unexpected token: " + it->sourcetext + " a struct field was expected instead", *it};
    }
    Instance field;
    acquire_identifier(it, tokens, field.name);
    acquire_exact_match(it,tokens,":");
    acquire_typesignature(it,tokens,field.typesignature);
    acquire_exact_match(it,tokens,";");
    fields.push_back(field);
}

void acquire_baretype(std::vector<Token>::iterator& it, const std::vector<Token>& tokens, std::string& type){
    auto expected_type_position = it;
    bool is_type = (it != tokens.end() and isalpha(it->sourcetext[0]) and isupper(it->sourcetext[0]));
    type = (is_type)? it->sourcetext : "/ERROR";
    std::advance(it,is_type);
    std::string found = (it == tokens.end())? "(END OF FILE)" : it->sourcetext;
    if(not is_type) throw SyntaxError { "unexpected token: " + found + " a typesignature was expacted instead", *expected_type_position };
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