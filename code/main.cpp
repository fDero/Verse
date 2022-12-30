#include "include/verse.hpp"
#include "include/procedures.hpp"
#include "include/commandline.hpp"

int main(int argc, char **argv){
    try {
        CommandLine command_line = read_commandline(argc,argv);
        switch (command_line.mode){
            case Mode::compiler:      compile(command_line.inputs, command_line.outputs);   break;
            case Mode::interpreter:   evaluate(command_line.inputs, command_line.outputs);  break;
            case Mode::debugger:      debug(command_line.inputs, command_line.outputs);     break;
            case Mode::version:       display_commandline_version();                        break;
            case Mode::help:          display_commandline_help();                           break;
        }
    }
    catch (const TokenizationError& err){
        std::cout 
        << "TOKENIZATION ERROR:\n\t" 
        << err.error_message
        << "\n in file: " << err.data.filename
        << "\n at line: " << err.data.line_number
        << "\n tok num: " << err.data.tok_number;
    }
}