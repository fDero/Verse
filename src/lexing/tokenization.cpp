#include "../include/verse.hpp"
#include "../include/procedures.hpp"
#include "../include/errors.hpp"

inline const std::set<char> discardable{'\t','\r','\0','\n',' '}; 

void inspect_for_errors(const std::string& sourcecode, const int current,const TokenInfo& data){
    std::string tmp;
    for (int i = current; i < sourcecode.size() and discardable.find(sourcecode[i]) == discardable.end(); i++) tmp.push_back(sourcecode[i]);
    if (tmp.size() > 0) throw TokenizationError{ "unrecognized token: " + tmp, tmp, data };
}

std::string extract_token(const std::string& sourcecode, const int current, const TokenInfo& data){
    std::string extracted; 
    if ((extracted = extract_text(sourcecode,current,data)) != "")    return extracted;
    if ((extracted = extract_symbol(sourcecode,current,data)) != "")  return extracted;
    if ((extracted = extract_number(sourcecode,current,data)) != "")  return extracted;
    if ((extracted = extract_string(sourcecode,current,data)) != "")  return extracted;
    inspect_for_errors(sourcecode,current,data);
    return extracted;
}

std::vector<Token> get_tokens_from_file(const std::string& input_filename){
    std::fstream source_code;
    source_code.open(input_filename,std::ios::in);
    if (!source_code.is_open()) throw CommandLineError { "no such file has been found: " + input_filename };
    std::vector<Token> tokens;
    std::string line;
    for(unsigned long line_number = 1;  getline(source_code, line); line_number++) {
        unsigned int char_pos = 0;
        unsigned int tok_number = 0;
        while (char_pos < line.size()){ 
            TokenInfo data {input_filename, line_number, tok_number, char_pos};
            std::string tokentxt = extract_token(line,char_pos,data);
            if (!tokentxt.empty()) {
                tokens.push_back(Token{tokentxt, input_filename, line_number, tok_number++, char_pos});
            }
            char_pos += tokentxt.empty() + tokentxt.size();
        }
    }
    source_code.close();
    return tokens;
}