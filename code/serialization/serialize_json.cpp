#include "../include/verse.hpp"
#include "../include/procedures.hpp"

void translate_tokens_into_json(const std::vector<Token>& tokens, std::fstream& output){
    output << "[";
    for (auto it = tokens.begin(); it != tokens.end(); it++){
        std::string text = it->sourcetext;
        if (text[0] == '"') text[0] = text.back() = '`'; 
        output  << "\n" << "\t" << "{"
                << "\n" << "\t" << "\t\"sourcetext\":\""  << text             << "\","
                << "\n" << "\t" << "\t\"file_name\":\""   << it->filename     << "\","
                << "\n" << "\t" << "\t\"line_number\":"   << it->line_number  << ","
                << "\n" << "\t" << "\t\"token_number\":"  << it->tok_number   << ","
                << "\n" << "\t" << "\t\"char_pos\":"      << it->char_pos     
                << "\n" << "\t" << "}" 
                << (std::next(it) == tokens.end()? "" : ",");
    }
    output << "\n" << "]";
}

void compile_json(const std::vector<std::string>& input_files, const std::string& output_filepath){
    std::string input_filepath = input_files.back();
    std::vector<Token> tokens = tokenize_file(input_filepath);
    std::vector<Token>::iterator primer = tokens.begin();   
    std::fstream output = std::fstream(output_filepath,  std::fstream::in | std::fstream::out | std::fstream::trunc);
    translate_tokens_into_json(tokens, output);
    output.close(); 
    std::cout << input_filepath << " compiled successfully as " << output_filepath << "\n";
}