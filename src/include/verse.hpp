#pragma once
#include <iostream>
#include <string>
#include <set>
#include <map>
#include <iomanip>
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
#include <cmath>
#include <math.h>
#include <map>
#include <list>

struct CommandLine; enum class FileExtension;  enum class Mode;

struct Token {
    std::string sourcetext;
    std::string filename;
    unsigned long line_number;
    unsigned int tok_number;
    unsigned int char_pos;
};

struct Variable;         struct Constant;          struct FunctionDefinition;  
struct EnumDefinition;   struct StructDefinition;  struct UnionDefinition;
struct FunctionCall;     struct UnaryOperator;     struct BinaryOperator;
struct WhileLoop;        struct UntilLoop;         struct Conditional; 
struct Assignment;       struct Literal;           struct Identifier;              
struct Return;           struct Continue;          struct Break;
struct Defer;            struct Attempt;           struct DoNothing;

using Instruction = std::variant<
    Variable,       Constant,          FunctionDefinition,
    /*Enum*/        StructDefinition,  /*Union*/
    FunctionCall,   UnaryOperator,     BinaryOperator,
    WhileLoop,      UntilLoop,         Conditional, 
    Assignment,     Literal,           Identifier,
    Return,         Continue,          Break,
    Attempt,        DoNothing,         Defer
>;

#include "types.hpp"
#include "errors.hpp"
#include "definitions.hpp"
#include "expressions.hpp"
#include "statements.hpp"
#include "interpreter.hpp"

inline std::unordered_map<std::string, std::vector<FunctionDefinition>> global_functions_definitions;
inline std::unordered_map<std::string, std::vector<std::string>> global_structs_names_register;
inline std::unordered_map<std::string, StructDefinition> global_structs_definitions;
inline std::map<std::string, verselang_macro_procedure> verselang_macros;