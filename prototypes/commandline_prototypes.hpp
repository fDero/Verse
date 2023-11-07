#pragma once
#include "../include/verse.hpp"

CommandLine read_commandline(int,char**);
FileExtension file_extension(const std::string& filename);
void compile(const std::vector<std::string>&,const std::vector<std::string>&);
void run(const std::vector<std::string>&,const std::vector<std::string>&);
void debug(const std::vector<std::string>&,const std::vector<std::string>&);
void display_commandline_version();
void display_commandline_help(); 

inline std::string red(const std::string& str)    { return std::string("\e[0;31m") + str + std::string("\e[0;0m"); }
inline std::string green(const std::string& str)  { return std::string("\e[0;32m") + str + std::string("\e[0;0m"); }
inline std::string yellow(const std::string& str) { return std::string("\e[0;33m") + str + std::string("\e[0;0m"); }
inline std::string blue(const std::string& str)   { return std::string("\e[0;34m") + str + std::string("\e[0;0m"); }
inline std::string purple(const std::string& str) { return std::string("\e[0;35m") + str + std::string("\e[0;0m"); }
inline std::string aqua(const std::string& str)   { return std::string("\e[0;36m") + str + std::string("\e[0;0m"); }
inline std::string gray(const std::string& str)   { return std::string("\e[0;37m") + str + std::string("\e[0;0m"); }

inline std::string bold_red(const std::string& str)    { return std::string("\e[1;31m") + str + std::string("\e[0;0m"); }
inline std::string bold_green(const std::string& str)  { return std::string("\e[1;32m") + str + std::string("\e[0;0m"); }
inline std::string bold_yellow(const std::string& str) { return std::string("\e[1;33m") + str + std::string("\e[0;0m"); }
inline std::string bold_blue(const std::string& str)   { return std::string("\e[1;34m") + str + std::string("\e[0;0m"); }
inline std::string bold_purple(const std::string& str) { return std::string("\e[1;35m") + str + std::string("\e[0;0m"); }
inline std::string bold_aqua(const std::string& str)   { return std::string("\e[1;36m") + str + std::string("\e[0;0m"); }
inline std::string bold_gray(const std::string& str)   { return std::string("\e[1;37m") + str + std::string("\e[0;0m"); }