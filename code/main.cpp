#include "include/verse.hpp"
#include "include/procedures.hpp"

void read_commandline(int argc, char **argv){
    if (argc < 2) throw std::runtime_error("don't know what to do");
    for (int i = 1; i < argc; i++){
        std::cout << argv[i] << std::endl;
    }
}

int main(int argc, char **argv){
    try {
        read_commandline(argc,argv);
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
        << "\n tok num: " << err.data.tok_number;
    }
}