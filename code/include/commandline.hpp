#pragma once
#include "verse.hpp"

enum class Mode {
    standard, version, help,
    compiler, interpreter, debugger
};

struct CommandLine {
    std::vector<std::string> inputs;
    std::vector<std::string> outputs;
    Mode mode;
};