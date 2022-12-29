#pragma once
#include "verse.hpp"

struct Instance { std::string name; TypeSignature typesignature; };
struct Variable : public Instance {};
struct Constant : public Instance { std::shared_ptr<Instruction> value; };

struct StructDefinition { 
    std::string                struct_name; 
    std::vector<TypeSignature> generics; 
    std::vector<Instance>      internal_state;
    std::vector<Instruction>   internal_definitions;
};

struct FunctionDefinition { 
    std::string                func_name; 
    std::vector<TypeSignature> generics;
    std::vector<Instance>      args; 
    std::vector<Instruction>   code; 
    std::vector<Instruction>   internal_definitions;
};