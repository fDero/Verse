#pragma once
#include "../include/verse.hpp"

void assert_unreachable();
void display_commandline_error(const CommandLineError&);
void display_tokenization_error(const TokenizationError&);
void display_syntax_error(const SyntaxError&);
void display_ICE(const InternalCompilerError&);
void display_runtime_error(const std::runtime_error&);