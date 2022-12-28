#pragma once
#include "verse.hpp"

struct Conditional {
    std::shared_ptr<Instruction> condition;
    std::vector<Instruction> then;
    std::vector<Instruction> otherwise;
};

struct WhileLoop { 
    std::shared_ptr<Instruction> condition;
    std::vector<Instruction> code;
};

struct UntilLoop { 
    std::shared_ptr<Instruction> condition;
    std::vector<Instruction> code;
};