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

void display_error_context(const std::string& filename, int line_number, int char_pos){
    std::ifstream infile(filename);
    std::string line;
    
    int spread = 4;
    
    for (int linenum = 1; std::getline(infile, line); linenum++) {

        if (linenum > line_number - spread and linenum < line_number){
            std::cout << "\t" << line << "\n";
        }
        
        if (linenum == line_number){
            std::cout << "\t";
            for (int i = 0; i < line.size(); i++){
                if(i != char_pos) std::cout << yellow(line.substr(i,1)); 
                else std::cout << red(line.substr(i,1));
                char_pos += (isalnum(line[i]) and i == char_pos); 
            }
            std::cout << "\n";
        }
        
        if (linenum < line_number + spread and linenum > line_number){
            std::cout << "\t" << line << "\n";
        }
        
        if (linenum > line_number + spread) break;
    }
}

void display_commandline_error(const CommandLineError& err){
    std::cout << std::endl << bold_red("COMMANDLINE ERROR: \n └─ ") 
    << red(err.error_message + "\n\n")
    << purple("type 'verse --help' in your console to get more informations\n\n");
}

void display_tokenization_error(const TokenizationError& err){
    std::cout << std::endl
    << bold_red("TOKENIZATION ERROR: \n └─ ")
    << red(err.error_message) << "\n\n";
    display_error_context(err.data.filename, err.data.line_number, err.data.char_pos);
    std::cout << purple("\n in file: ") << err.data.filename << " "
    << purple("at line: ") << err.data.line_number << "\n\n";
}

void display_syntax_error(const SyntaxError& err){
    std::cout << std::endl
    << bold_red("SYNTAX ERROR: \n └─ ")
    << red(err.error_message) << "\n\n";
    display_error_context(err.error_token.filename, err.error_token.line_number, err.error_token.char_pos);
    std::cout << purple("\n in file: ") << err.error_token.filename
    << purple(" at line: ") << err.error_token.line_number << "\n\n";
}

void display_ICE(const InternalCompilerError& err){
    std::cout << std::endl
    << bold_red("INTERNAL COMPILER ERROR: \n └─ ")  
    << red(err.error_message + "\n\n")
    << yellow("please, write an extensive bug report explaining the issue and report it on the github page ") 
    << yellow("of this project at https://www.github.com/Verse\n\n");
}