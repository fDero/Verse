#pragma once
#include "../include/verse.hpp"

bool typesignatures_are_equal(const TypeSignature&, const TypeSignature&);;
bool is_default_integral_type(const TypeSignature&);
std::string type_to_string_without_generics(const TypeSignature&);
std::string type_to_string(const TypeSignature&);
std::string get_qualified_struct_name(const StructDefinition&);
std::string most_derived_type(const TypeSignature&);
InstanciatedGenerics get_instanciated_generics(const TypeSignature&);
TemplateGenerics get_template_generics(const StructDefinition&);
GenericsLookupTable get_generics_lookup_table(const TemplateGenerics&,const InstanciatedGenerics&);