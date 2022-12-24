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

inline const std::set<char> symbols{'+','-','*','/','=','.',':','<','>','!','(',')','[',']','{','}',','};
inline const std::set<std::string> combinations{">=","<=","!=","++","--","==","->","<-",">>","<<","&&","||","^^"};
inline const std::set<char> discardable {'\t','\r','\0','\n',' '}; 

inline const std::string pointer_prefix = "#";
inline const std::string context_concatenation = "::"; 
inline const std::string indent = "    ";

struct Token {
    std::string sourcetext;
    std::string filename;
    unsigned long line_number;
    unsigned int tok_number;
    unsigned int char_pos;
};

struct TokenInfo {
    std::string filename;
    unsigned long line_number;
    unsigned int tok_number;
    unsigned int char_pos;
};

struct TokenizationError {
    std::string error_message;
    std::string source_text;
    TokenInfo data;
};

struct Instantiation; struct StructDefinition; struct FunctionDefinition;
struct FunctionCall; struct Identifier; struct Literal; 
struct Assignment; struct Conditional; struct WhileLoop; struct UntilLoop;

using Instruction = std::variant<
    Instantiation,
    StructDefinition,
    FunctionDefinition,
    Identifier,
    Literal,
    FunctionCall,
    Assignment,
    WhileLoop,
    UntilLoop,
    Conditional
>;

struct Instantiation { 
    std::string name; 
    std::string typesignature; 
};

struct StructDefinition { 
    std::string struct_name; 
    std::vector<Instantiation> internal_state; 
};

struct FunctionDefinition { 
    std::string func_name; 
    std::vector<Instantiation> args; 
    std::vector<Instruction> code; 
};

struct FunctionCall { 
    std::string func_name; 
    std::vector<Instruction> args; 
};

struct Identifier { 
    std::string name; 
};

struct Literal { 
    std::string value; 
    std::string pseudotype; 
};

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

struct Assignment {
    std::string name;
    std::shared_ptr<Instruction> value;
};