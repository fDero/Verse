#pragma once
#include "../include/verse.hpp"

StructDefinition retrieve_struct_definition(const TypeSignature&);
FunctionDefinition retrieve_function_overload(const std::string&,const ArgumentTypes&,ExecutionContext&);