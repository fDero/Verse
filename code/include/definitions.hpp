#pragma once
#include "verse.hpp"

struct Instantiation { 
    std::string name; 
    TypeSignature typesignature; 
};

struct StructDefinition { 
    std::string struct_name; 
    std::vector<TypeSignature> generics; 
    std::vector<Instantiation> internal_state;
    //
};

struct FunctionDefinition { 
    std::string func_name; 
    std::vector<TypeSignature> generics;
    std::vector<Instantiation> args; 
    std::vector<Instruction> code; 
};