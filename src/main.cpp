#include "../include/verse.hpp"
#include "../prototypes/procedures.hpp"
#include "../include/commandline.hpp"

int main(int argc, char** argv){
    try {
        CommandLine command_line = read_commandline(argc,argv);
        switch (command_line.mode){
            case Mode::compiler:      compile(command_line.inputs, command_line.outputs);   break;
            case Mode::interpreter:   run(command_line.inputs, command_line.outputs);       break;
            case Mode::debugger:      debug(command_line.inputs, command_line.outputs);     break;
            case Mode::version:       display_commandline_version();                        break;
            case Mode::help:          display_commandline_help();                           break;
            case Mode::unspecified:   assert_unreachable();                                 break;
        }
    }
    catch (const CommandLineError& err)       { display_commandline_error(err);  }
    catch (const TokenizationError& err)      { display_tokenization_error(err); }
    catch (const SyntaxError& err)            { display_syntax_error(err);       }
    catch (const InternalCompilerError& err)  { display_ICE(err);                }
    catch (...)                               { display_ICE(unrecognized_error); }
}