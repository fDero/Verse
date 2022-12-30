#include "../include/verse.hpp"
#include "../include/procedures.hpp"

void translate_tokens_into_json(const std::vector<Token>& tokens, std::fstream& output){
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
    
}

void compile_json(const std::vector<std::string>& input_files, const std::string& output_filepath){
    initialize_output_file(output_filepath);
    std::fstream output = std::fstream(output_filepath, std::ios_base::app);
    output << "[";
    output << "\n\t\" files: "; for (const std::string& input : input_files) output << input << " "; output  << "\"";
    for (const std::string& input : input_files){
        output << ",";
        std::vector<Token> tokens = get_tokens_from_file(input);
        translate_tokens_into_json(tokens, output);
    }
    output << "\n]";
    output.close(); 
}