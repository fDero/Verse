#pragma once
#include "verse.hpp"
#include "../prototypes/procedures.hpp"

inline void dump(const std::list<std::vector<TypeSignature>>& generics){
    for (const auto& generics_vector : generics) {
        std::cerr << "[ ";
        for (const auto& generic : generics_vector) std::cerr << type_to_string(generic) << " ";
        std::cerr << "] ";
    }
    std::cerr << std::endl;
}

inline void dump(const GenericsLookupTable& glt){
    for (const auto& pair : glt) {
        std::cerr << pair.first << " " << type_to_string(pair.second) << " ";
    }
    std::cerr << "\n";
}

inline void dump_global_structs_names_and_defs(){
    std::cerr << "\n\n---------------------------------------------------------\n\n";
    for (const auto& names_register_entry : global_structs_names_register){
        std::cerr << names_register_entry.first << " : ";
        for (const std::string& name : names_register_entry.second){
            std::cerr << name << " ";
        }
        std::cerr << "\n";
    }
    std::cerr << "\n";
    for (const auto& definitions_register_entry : global_structs_definitions){
        std::cerr << definitions_register_entry.first << "\n";
    }
    std::cerr << "\n\n---------------------------------------------------------\n\n";
}