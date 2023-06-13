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

struct InternalCompilerError {
    std::string error_message;
};

struct CommandLineError {
    std::string error_message;
};

void inline assert_unreachable(){
    throw InternalCompilerError{
        "an execution path that should have been unreachable has been reached! (assert_unreachable)"
    };
}