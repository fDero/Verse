#include "../include/verse.hpp"
#include "../include/procedures.hpp"

inline const std::set<char> symbols{'+','-','*','/','=','.',':','<','>','!','(',')','[',']','{','}',',',';','&','|','^','#'};
inline const std::set<std::string> combinations{">=","<=","!=","++","--","==","->","<-","&&","||","^^"};

std::string extract_number(const std::string& sourcecode, const int current, const TokenInfo& data){
    std::string buffer;
    bool floating = false;
    if (isdigit(sourcecode[current])) {
        for (int i = current; i < sourcecode.size(); i++){
            if (!isdigit(sourcecode[i]) and sourcecode[i] != '.') break;
            if (floating and sourcecode[i] == '.') 
                throw TokenizationError{"multiple decimal points in floating point literal", buffer, data };
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
        if (current+buffer.size() >= sourcecode.size() or sourcecode[current+buffer.size()] != sourcecode[current]){
            throw TokenizationError{ "string literal opened but never closed", buffer, data };
        }
        buffer.push_back(sourcecode[current]);
    }
    return buffer;
}

std::string extract_symbol(const std::string& sourcecode, const int current, const TokenInfo& data){
    int i = current, j = current + 1;
    if(i >= sourcecode.size() or symbols.find(sourcecode[i]) == symbols.end()) return std::string{};
    if(j >= sourcecode.size() or symbols.find(sourcecode[j]) == symbols.end()) return std::string{sourcecode[i]};
    if(combinations.find({sourcecode[i],sourcecode[j]}) == combinations.end()) return std::string{sourcecode[i]};
    return std::string{sourcecode[i],sourcecode[j]};
}