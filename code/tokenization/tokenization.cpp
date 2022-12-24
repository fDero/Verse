#include "../include/defs.hpp"
#include "../include/procedures.hpp"

std::string extract_number(const std::string& sourcecode, const int current, const TokenInfo& data){
    std::string buffer;
    bool floating = false;
    if (isdigit(sourcecode[current])) {
        for (int i = current; i < sourcecode.size(); i++){
            if (!isdigit(sourcecode[i]) and sourcecode[i] != '.') break;
            if (floating and sourcecode[i] == '.') 
                throw TokenizationError{"multiple decimal points in floating point literal", buffer, data.filename, data.tok_number, data.char_pos};
            floating = (sourcecode[i] == '.');
            buffer.push_back(sourcecode[i]);
        }
    }
    return buffer;
}

std::string extract_text(const std::string& sourcecode, const int current, const TokenInfo& data){
    std::string buffer;
    if (isalpha(sourcecode[current])) {
        for (int i = current; i < sourcecode.size(); i++){
            if (!isalpha(sourcecode[i]) and !isdigit(sourcecode[i]) and sourcecode[i] != '_') break;
            buffer.push_back(sourcecode[i]);
        }
    }
    return buffer;
}

std::string extract_string(const std::string& sourcecode, const int current, const TokenInfo& data){
    std::string buffer;
    bool escape = false;
    if (sourcecode[current] == '"' or sourcecode[current] == '\'' or sourcecode[current] == '`'){
        buffer.push_back(sourcecode[current]);
        for(int i = current + 1; i < sourcecode.size() and !(sourcecode[current] == sourcecode[i] and !escape); i++){
            escape = (sourcecode[i] == '\\' and !escape);
            buffer.push_back(sourcecode[i]);
        }
        if (current+buffer.size() >= sourcecode.size() and sourcecode[current+buffer.size()] != sourcecode[current]){
            throw TokenizationError{"string literal opened but never closed",buffer, data.filename, data.tok_number, data.char_pos};
        }
        buffer.push_back(sourcecode[current]);
    }
    return buffer;
}

std::string extract_special(const std::string& sourcecode, const int current, const TokenInfo& data){
    return (current < sourcecode.size() and sourcecode[current] == ';')? std::string{(sourcecode[current])} : "";
}

std::string extract_symbol(const std::string& sourcecode, const int current, const TokenInfo& data){
    int i = current, j = current + 1;
    if(i >= sourcecode.size() or symbols.find(sourcecode[i]) == symbols.end()) return std::string{};
    if(j >= sourcecode.size() or symbols.find(sourcecode[j]) == symbols.end()) return std::string{sourcecode[i]};
    if(combinations.find({sourcecode[i],sourcecode[j]}) == combinations.end()) return std::string{sourcecode[i]};
    return std::string{sourcecode[i],sourcecode[j]};
}

void inspect_for_errors(const std::string& sourcecode, const int current,const TokenInfo& data){
    std::string tmp;
    for (int i = current; i < sourcecode.size() and discardable.find(sourcecode[i]) == discardable.end(); i++) tmp.push_back(sourcecode[i]);
    if (tmp.size() > 1) throw TokenizationError{"unrecognized token sequence",tmp, data.filename, data.tok_number, data.char_pos};
    if (tmp.size() > 0) throw TokenizationError{"unrecognized token",tmp, data.filename, data.tok_number, data.char_pos};
}

std::string extract_token(const std::string& sourcecode, const int current, const TokenInfo& data){
    std::string extracted; 
    extracted = extract_text(sourcecode,current,data);    if (!extracted.empty()) return extracted;
    extracted = extract_symbol(sourcecode,current,data);  if (!extracted.empty()) return extracted;
    extracted = extract_special(sourcecode,current,data); if (!extracted.empty()) return extracted;
    extracted = extract_number(sourcecode,current,data);  if (!extracted.empty()) return extracted;
    extracted = extract_string(sourcecode,current,data);  if (!extracted.empty()) return extracted;
    inspect_for_errors(sourcecode,current,data);
    return extracted;
}

std::vector<Token> tokenize_file(const std::string& input_filename){
    std::fstream source_code;
    source_code.open(input_filename,std::ios::in);
    if (!source_code.is_open()) throw std::runtime_error("FATAL ERROR: can't find file named: " + input_filename);
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