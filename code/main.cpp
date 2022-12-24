#include "include/defs.hpp"
#include "include/procedures.hpp"

int main(int argc, char **argv){
    try {
        std::string input_file = argv[2];
        std::string output_file = argv[4];
        std::string output_file2 = argv[5];
        compile_json(input_file,output_file2);
        compile_xml(input_file,output_file);
    }
    catch (const TokenizationError& err){
        std::cout 
        << "TOKENIZATION ERROR:\n\t" 
        << err.error_message
        << "\n in file: " << err.data.filename
        << "\n at line: " << err.data.line_number
        << "\n tok num: " << err.data.tok_number
        ;
    }
}