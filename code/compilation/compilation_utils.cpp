#include "../include/verse.hpp"
#include "../include/procedures.hpp"

void initialize_output_file(const std::string& filename){
    std::fstream output = std::fstream(filename,  std::fstream::in | std::fstream::out | std::fstream::trunc);
    output.close();
}