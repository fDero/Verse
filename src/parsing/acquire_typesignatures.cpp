#include "../../include/verse.hpp"
#include "../../prototypes/procedures.hpp"

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
