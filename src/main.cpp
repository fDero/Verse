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
            case Mode::unspecified:   assert_unreachable();                                 break;
        }
    }
    catch (const CommandLineError& err){
        std::cout 
        << bold_red("COMMANDLINE ERROR: \n\t") 
        << red(err.error_message + "\n\n")
        << purple("type 'verse --help' in your console to get more informations\n\n");
    }
    catch (const TokenizationError& err){
        std::cout 
        << bold_red("TOKENIZATION ERROR: \n\t")
        << red(err.error_message)
        << purple("\n in file: ") << err.data.filename
        << purple("\n at line: ") << err.data.line_number
        << purple("\n tok num: ") << err.data.tok_number
        << "\n\n";
    }
    catch (const SyntaxError& err){
        std::cout
        << bold_red("SYNTAX ERROR: \n\t")
        << red(err.error_message)
        << purple("\n in file: ") << err.error_token.filename
        << purple("\n at line: ") << err.error_token.line_number
        << purple("\n tok num: ") << err.error_token.tok_number
        << "\n\n";
    }
    catch (const InternalCompilerError& err){
        std::cout 
        << bold_red("INTERNAL COMPILER ERROR: \n\t")  
        << red(err.error_message + "\n\n")
        << yellow("please, write an extensive bug report explaining the issue and report it on the github page ") 
        << yellow("of this project at https://www.github.com/Verse\n\n");
    }
}