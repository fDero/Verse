#pragma once
#include "../include/verse.hpp"

FunctionDefinition find_main_entry_point();
void fully_qualify_struct_field_typesignature(TypeSignature&,StructDefinition&);
void init_global_definitions_table(const std::vector<std::string>&);
void fully_qualify_struct_fields();