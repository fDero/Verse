#include "../include/verse.hpp"
#include "../include/errors.hpp"
#include "../include/procedures.hpp"

#include <iostream>
#include <sstream>
#include <string>
#include <fstream>

void assert_unreachable(){
    throw InternalCompilerError{
        "an execution path that should have been unreachable has been reached! (assert_unreachable)"
    };
}

void display_error_context(const Token& error_token){
    std::ifstream infile(error_token.filename);
    std::string line;
    
    int line_number = 0;
    int char_number = 0;
    int spread = 4;
    
    for (int linenum = 1; std::getline(infile, line); linenum++) {

        if (linenum > error_token.line_number - spread and linenum < error_token.line_number){
            std::cout << "\t" << line << "\n";
        }
        
        if (linenum == error_token.line_number){
            std::cout << "\t\e[0;33m" << line <<"\e[0;0m\n";
        }
        
        if (linenum < error_token.line_number + spread and linenum > error_token.line_number){
            std::cout << "\t" << line << "\n";
        }
        
        if (linenum > error_token.line_number + spread) break;
    }
}

void display_commandline_error(const CommandLineError& err){
    std::cout << std::endl << bold_red("COMMANDLINE ERROR: \n\t") 
    << red(err.error_message + "\n\n")
    << purple("type 'verse --help' in your console to get more informations\n\n");
}

void display_tokenization_error(const TokenizationError& err){
    std::cout << std::endl
    << bold_red("TOKENIZATION ERROR: \n\t")
    << red(err.error_message)
    << purple("\n in file: ") << err.data.filename << " "
    << purple("at line: ") << err.data.line_number << "\n";
}

void display_syntax_error(const SyntaxError& err){
    std::cout << std::endl
    << bold_red("SYNTAX ERROR: \n\t")
    << red(err.error_message) << "\n\n";
    display_error_context(err.error_token);
    std::cout << purple("\n in file: ") << err.error_token.filename
    << purple(" at line: ") << err.error_token.line_number << "\n\n";
}

void display_ICE(const InternalCompilerError& err){
    std::cout << std::endl
    << bold_red("INTERNAL COMPILER ERROR: \n\t")  
    << red(err.error_message + "\n\n")
    << yellow("please, write an extensive bug report explaining the issue and report it on the github page ") 
    << yellow("of this project at https://www.github.com/Verse\n\n");
}