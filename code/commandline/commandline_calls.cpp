#include "../include/verse.hpp"
#include "../include/procedures.hpp"
#include "../include/commandline.hpp"

void compile(const std::vector<std::string>& inputs, const std::vector<std::string>& outputs){
    for (const std::string& out : outputs){
        for (const std::string& in : inputs){
            if (file_extension(in) != FileExtension::verse) throw std::runtime_error("input files must be .verse");
            switch (file_extension(out)) {
                case FileExtension::xml:    compile_xml(in,out);    break;
                case FileExtension::json:   compile_json(in,out);   break;
            }   
        }
    }
}

void evaluate(const std::vector<std::string>& inputs, const std::vector<std::string>& outputs){

}

void debug(const std::vector<std::string>& inputs, const std::vector<std::string>& outputs){

}

void version(){
    std::cout << "version: pre-release\n";
    std::cout << "check for updates at https://www.github.com/fDero/Verse\n\n";
}

void help(){

}