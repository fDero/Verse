#pragma once
#include <iostream>
#include <string>
#include <set>
#include <map>
#include <sstream>
#include <fstream>
#include <vector>
#include <exception>
#include <regex>
#include <utility>
#include <functional>
#include <variant>
#include <memory>
#include <stdio.h>

struct Token {
    std::string sourcetext;
    std::string filename;
    unsigned long line_number;
    unsigned int tok_number;
    unsigned int char_pos;
};

struct Instantiation;  struct StructDefinition; struct FunctionDefinition;
struct FunctionCall;   struct UnaryOperator;    struct BinaryOperator;
struct WhileLoop;      struct UntilLoop;        struct Conditional; 
struct Assignment;     struct Literal;          struct Identifier;              

using Instruction = std::variant<
    Instantiation,      StructDefinition,       FunctionDefinition,
    FunctionCall,       UnaryOperator,          BinaryOperator,
    WhileLoop,          UntilLoop,              Conditional,
    Assignment,         Literal,                Identifier
>;

#include "types.hpp"
#include "errors.hpp"
#include "definitions.hpp"
#include "expressions.hpp"
#include "statements.hpp"
