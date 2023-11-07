#include "../../include/verse.hpp"
#include "../../prototypes/procedures.hpp"

StructDefinition struct_retrieval_helper_function(const std::string& struct_base_name, const std::string& struct_fully_qualified_name){
    std::vector<std::string>& candidates = global_structs_names_register[struct_base_name];
    StructDefinition best_match = StructDefinition{};
    long distance_from_optimal = std::numeric_limits<long>::max();
    for (const std::string& candidate : candidates){
        StructDefinition& candidate_definition = global_structs_definitions[candidate];
        if(candidate == struct_fully_qualified_name) return candidate_definition;
        if (std::regex_match(struct_fully_qualified_name, std::regex{candidate})){
            if (candidate_definition.generics.size() < distance_from_optimal){
                distance_from_optimal = candidate_definition.generics.size();
                best_match = candidate_definition;
            }
        }
    }
    return best_match;
}

StructDefinition retrieve_struct_definition(const TypeSignature& type){
    std::string struct_base_name = most_derived_type(type);
    std::string struct_fully_qualified_name = type_to_string(type);
    StructDefinition retrieved = struct_retrieval_helper_function(struct_base_name, struct_fully_qualified_name);
    if (retrieved.struct_name.empty()) throw std::runtime_error { "no such struct named: " + type_to_string(type) + " in this scope" };
    return retrieved;
}
