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