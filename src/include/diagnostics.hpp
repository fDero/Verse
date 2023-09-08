#pragma once
#include "verse.hpp"
#include "procedures.hpp"

inline void dump(TemplateGenerics tgs){
    for (const auto& tg : tgs) {
        std::cerr << "[ ";
        for (const auto& t : tg) std::cerr << type_to_string(t) << " ";
        std::cerr << "] ";
    }
    std::cerr << std::endl;
}

inline void dump(InstanciatedGenerics tgs){
    for (const auto& tg : tgs) {
        std::cerr << "[ ";
        for (const auto& t : tg) std::cerr << type_to_string(t) << " ";
        std::cerr << "] ";
    }
    std::cerr << std::endl;
}

inline void dump(GenericsLookupTable glt){
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
    for (const auto& definitons_register_entry : global_structs_definitions){
        std::cerr << definitons_register_entry.first << "\n";
    }
    std::cerr << "\n\n---------------------------------------------------------\n\n";
}