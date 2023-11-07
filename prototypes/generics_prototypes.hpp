#pragma once
#include "../include/verse.hpp"

TypeSignature apply_generics_to_typesignature(const TypeSignature&,const GenericsLookupTable&);
StructDefinition apply_generics_to_struct_definition(const StructDefinition&, const GenericsLookupTable&);
StructDefinition retrieve_and_instanciate_struct(const TypeSignature&);