#pragma once
#include "verse.hpp"

struct FunctionCall { 
    std::string func_name; 
    std::vector<Instruction> args; 
};

struct BinaryOperator {
    std::string text;
    std::shared_ptr<Instruction> lx;
    std::shared_ptr<Instruction> rx;
    bool wrapped_in_parenthesys = false;
};

struct UnaryOperator {
    std::string text;
    std::shared_ptr<Instruction> operand;
    bool wrapped_in_parenthesys = false;
};

struct Assignment {
    std::shared_ptr<Instruction> target;
    std::shared_ptr<Instruction> value;
};

struct Identifier { 
    std::string name; 
};

struct Literal { 
    std::string value; 
    std::string pseudotype; 
};