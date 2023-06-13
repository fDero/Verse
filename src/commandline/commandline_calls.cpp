#include "../include/verse.hpp"
#include "../include/procedures.hpp"
#include "../include/commandline.hpp"

void validate_input_files(const std::vector<std::string>& inputs){
    for(const std::string& in : inputs) {
        if (file_extension(in) != FileExtension::verse) throw std::runtime_error("input files must be .verse");
    }
}

void compile(const std::vector<std::string>& inputs, const std::vector<std::string>& outputs){
    validate_input_files(inputs);
    for (const std::string& out : outputs) switch (file_extension(out)) {
        case FileExtension::xml:   compile_xml(inputs,out);    break;
        case FileExtension::json:  compile_json(inputs,out);   break;
    }
}

void evaluate(const std::vector<std::string>& inputs, const std::vector<std::string>& outputs){
    std::cout << "the verse interpreter is not yet implemented\n";
    std::cout << "check for updates at https://www.github.com/fDero/Verse\n\n";
}

void debug(const std::vector<std::string>& inputs, const std::vector<std::string>& outputs){
    std::cout << "the verse debugger is not yet implemented\n";
    std::cout << "check for updates at https://www.github.com/fDero/Verse\n\n";

}

void display_commandline_version(){
    std::cout << "version: pre-release\n";
    std::cout << "check for updates at https://www.github.com/fDero/Verse\n\n";
}

void display_commandline_help(){
    std::cout << "compile verse code: \n\t verse -c <input files> -o <output files>\n\n";
    std::cout << "run code directly: \n\t verse -r <input files>\n\n";
    std::cout << "debug your code: \n\t verse -d <input files>\n\n";
    std::cout << "show current version: \n\t verse -v\n\n";

    std::cout << ">> every input file must be saved as .verse\n";
    std::cout << ">> two different output files can't share the same file extension\n";
    std::cout << ">> the only supported output formats are .asm, .o, .exe, .out, .xml and .json\n";
    std::cout << "(xml and json files are only for debug purpuses)\n\n";
    
    std::cout << "see the documentation for an in-depth explaination of the verse toolchain\n";
    std::cout << "check for updates at https://www.github.com/fDero/Verse\n\n";
}