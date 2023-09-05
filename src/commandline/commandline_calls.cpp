#include "../include/verse.hpp"
#include "../include/procedures.hpp"
#include "../include/commandline.hpp"

void validate_input_files(const std::vector<std::string>& inputs){
    for(const std::string& in : inputs) {
        if (file_extension(in) != FileExtension::verse) 
            throw CommandLineError { "input files must be .verse" };
    }
}

void verse_output_error(){
    throw CommandLineError { 
        ".verse file extension cannot be used for output files. type 'verse --help' for more informations" 
    };
}

void compile(const std::vector<std::string>& inputs, const std::vector<std::string>& outputs){
    validate_input_files(inputs);
    if (inputs.empty()) throw CommandLineError { "unspecified input files: don't know what to do" };
    if (outputs.empty()) throw CommandLineError { "unspecified output target: don't know what to do" };
    for (const std::string& out : outputs) switch (file_extension(out)) {
        case FileExtension::xml:   compile_xml(inputs,out);    break;
        case FileExtension::json:  compile_json(inputs,out);   break;
        case FileExtension::verse: verse_output_error();       break;
    }
}

void run(const std::vector<std::string>& input_files, const std::vector<std::string>& outputs){
    if (not outputs.empty()) throw CommandLineError { 
        "running your code directly with the verse interpreter does not produce output compilation files" 
    };
    init_global_definitions_table(input_files);
    initialize_print_macros();
    initialize_type_macros();
    FunctionDefinition main_entry_point = find_main_entry_point();
    ExecutionContext call_with_no_arguments_context;
    execute_function_body(main_entry_point, call_with_no_arguments_context);
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