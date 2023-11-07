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

struct Return    { std::shared_ptr<Instruction> value; };
struct Defer     { std::shared_ptr<Instruction> operation; };
struct Break     { std::string loop_tag; };
struct Continue  { std::string loop_tag; };
struct DoNothing {};

struct Attempt { 
    std::vector<std::vector<Instruction>> attempts;
    std::vector<Instruction> otherwise; 
};

