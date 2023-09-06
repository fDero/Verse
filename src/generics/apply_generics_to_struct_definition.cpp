#include "../include/verse.hpp"
#include "../include/procedures.hpp"

StructDefinition apply_generics_to_struct_definition(const StructDefinition& struct_template, const GenericsLookupTable& generics_lookup_table){
    StructDefinition instanciated_struct = struct_template;
    for (Instance& field : instanciated_struct.internal_state){
        field.typesignature = apply_generics_to_typesignature(field.typesignature, generics_lookup_table);
    }
    return instanciated_struct;
}