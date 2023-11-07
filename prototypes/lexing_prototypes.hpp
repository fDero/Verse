#pragma once
#include "../include/verse.hpp"

std::vector<Token> get_tokens_from_file(const std::string&);
std::string extract_string(const std::string&,const int,const TokenInfo&);
std::string extract_symbol(const std::string&,const int,const TokenInfo&);
std::string extract_number(const std::string&,const int,const TokenInfo&);
std::string extract_text(const std::string&,const int,const TokenInfo&);