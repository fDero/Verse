#include "include/defs.hpp"
#include "include/procedures.hpp"

int main(int argc, char **argv){
    std::string input_file = argv[2];
    std::string output_file = argv[4];
    std::string output_file2 = argv[5];
    compile_json(input_file,output_file2);
    compile_xml(input_file,output_file);
}