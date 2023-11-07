#pragma once
#include "verse.hpp"

struct Instance { std::string name; TypeSignature typesignature; };
struct Variable { std::string name; TypeSignature typesignature; };
struct Constant { std::string name; TypeSignature typesignature; std::shared_ptr<Instruction> value; };

struct StructDefinition { 
    std::string                         struct_name; 
    std::vector<TypeSignature>          generics; 
    std::vector<Instance>               internal_state;
    std::shared_ptr<StructDefinition>   parent_scope;
};

struct FunctionDefinition { 
    std::string                         func_name; 
    std::vector<TypeSignature>          generics;
    std::vector<Instance>               args; 
    std::vector<Instruction>            code; 
    std::shared_ptr<FunctionDefinition> parent_scope;
};