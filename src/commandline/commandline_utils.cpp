#include "../include/verse.hpp"
#include "../include/procedures.hpp"
#include "../include/commandline.hpp"

bool compiler_flag(int& i, int argc, char **argv, CommandLine& state){
    if (std::string(argv[i]) != "-c" and std::string(argv[i]) != "--compile") return false;
    while (++i < argc and argv[i][0] != '-')  state.inputs.push_back(argv[i]);
    if (state.mode != Mode::unspecified) throw CommandLineError { "conflicting flags" };
    state.mode = Mode::compiler;
    return true;
}

bool interpreter_flag(int& i, int argc, char **argv, CommandLine& state){
    if (std::string(argv[i]) != "-r" and std::string(argv[i]) != "--run") return false;
    while (++i < argc and argv[i][0] != '-')  state.inputs.push_back(argv[i]);
    if (state.mode != Mode::unspecified) throw CommandLineError { "conflicting flags" };
    state.mode = Mode::interpreter;
    return true;
}

bool debugger_flag(int& i, int argc, char **argv, CommandLine& state){
    if (std::string(argv[i]) != "-d" and std::string(argv[i]) != "--debug") return false;
    while (++i < argc and argv[i][0] != '-') state.inputs.push_back(argv[i]);
    if (state.mode != Mode::unspecified) throw CommandLineError { "conflicting flags" };
    state.mode = Mode::debugger;
    return true;
}

bool output_flag(int& i, int argc, char **argv, CommandLine& state){
    if (std::string(argv[i]) != "-o" and std::string(argv[i]) != "--output") return false;
    while (++i < argc and argv[i][0] != '-') state.outputs.push_back(argv[i]);
    if (state.outputs.empty()) throw CommandLineError { "-o flag specified but no target were given" };
    return true;
}

bool version_flag(int& i, int argc, char **argv, CommandLine& state){
    if (std::string(argv[i]) != "-v" and std::string(argv[i]) != "--version") return false;
    if (i + 1 < argc or !state.inputs.empty() or !state.outputs.empty() or state.mode != Mode::unspecified) 
        throw CommandLineError { "if you use the version flag (-v / --version) that's supposed to be the only one" };
    state.mode = Mode::version;
    return true;
}

bool help_flag(int& i, int argc, char **argv, CommandLine& state){
    if (std::string(argv[i]) != "-h" and std::string(argv[i]) != "--help") return false;
    if (i + 1 < argc or !state.inputs.empty() or !state.outputs.empty() or state.mode != Mode::unspecified) 
        throw CommandLineError { "if you use the help flag (-h / --help) that's supposed to be the only one" };
    state.mode = Mode::help;
    return true;
}

CommandLine read_commandline(int argc, char **argv){
    if (argc < 2) throw CommandLineError { "unspecified flags: don't know what to do" }; 
    CommandLine state {{}, {}, Mode::unspecified};
    int i = 1;
    while (i < argc){
        if (compiler_flag(i, argc, argv, state))    continue;
        if (interpreter_flag(i, argc, argv, state)) continue;
        if (output_flag(i, argc, argv, state))      continue;
        if (debugger_flag(i,argc,argv, state))      continue;
        if (version_flag(i,argc,argv, state))       break;
        if (help_flag(i,argc,argv, state))          break;
        throw CommandLineError { "unrecognized input: " + std::string(argv[i]) };
    }
    return state;
}

FileExtension file_extension(const std::string& filename){
    if (filename.size() >= 5 and filename.substr(filename.size()-4,4) == ".xml")   return FileExtension::xml;
    if (filename.size() >= 6 and filename.substr(filename.size()-5,5) == ".json")  return FileExtension::json;
    if (filename.size() >= 7 and filename.substr(filename.size()-6,6) == ".verse") return FileExtension::verse;
    throw CommandLineError { "unrecognized file extension for file: " + filename };
}