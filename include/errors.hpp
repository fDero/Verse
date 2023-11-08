#pragma once
#include "verse.hpp"

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

struct SyntaxError {
    std::string error_message;
    Token error_token;
};

struct InternalCompilerError {
    std::string error_message;
};

struct CommandLineError {
    std::string error_message;
};

inline InternalCompilerError unrecognized_error { 
    "an unrecognized error has occurred, the point of failure is unknown" 
};