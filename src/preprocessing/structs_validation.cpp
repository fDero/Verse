#include "../include/verse.hpp"
#include "../include/procedures.hpp"

std::set<std::string> already_validated_structs;

StructDefinition find_correct_struct_definition_in_definitions_set(const TypeSignature& type, const std::vector<StructDefinition>& definitions){
    if (definitions.empty()) return StructDefinition {}; else return definitions[0]; //<--- temporary, going to change soon
}

StructDefinition retrieve_struct_definition_from_global_scope(const BaseType& target_type){
    std::string candidate_name = "global\\" + target_type.base_type;
    auto target_definitions_set_search_outcome = global_definitions_table.structs.find(candidate_name);
    if (target_definitions_set_search_outcome == global_definitions_table.structs.end()) throw std::runtime_error { "no such struct found in this scope" };
    StructDefinition target_definition = find_correct_struct_definition_in_definitions_set(target_type, target_definitions_set_search_outcome->second);
    if (target_definition.struct_name.empty()) throw std::runtime_error { "no such struct found in this scope" };
    return target_definition;
}

StructDefinition retrieve_struct_definition_from_inside_struct(const BaseType& target_type, const StructDefinition& struct_definition){
    std::string candidate_name = struct_definition.struct_name + "\\" + target_type.base_type;
    auto target_definitions_set_search_outcome = global_definitions_table.structs.find(candidate_name);
    if (target_definitions_set_search_outcome == global_definitions_table.structs.end()) {
        if (struct_definition.parent_scope == nullptr) return retrieve_struct_definition_from_global_scope(target_type);
        return retrieve_struct_definition_from_inside_struct(target_type, *struct_definition.parent_scope);
    }
    else {
        std::vector<StructDefinition>& target_definitions_set = target_definitions_set_search_outcome->second;
        StructDefinition target_definition = find_correct_struct_definition_in_definitions_set(target_type, target_definitions_set);
        if (not target_definition.struct_name.empty()) return target_definition;
        if (struct_definition.parent_scope == nullptr) return retrieve_struct_definition_from_global_scope(target_type);
        return retrieve_struct_definition_from_inside_struct(target_type, *struct_definition.parent_scope);
    }
}

void validate_struct_field_typesignature(TypeSignature& type, StructDefinition& type_struct, StructDefinition& struct_definition, bool avoiding_loops){
    if (std::holds_alternative<BaseType>(type) and !is_default_integral_type(std::get<BaseType>(type))){
        if (given_type_is_a_template_generic_for_this_struct(std::get<BaseType>(type), type_struct)) return;
        StructDefinition type_definition = retrieve_struct_definition_from_inside_struct(std::get<BaseType>(type),type_struct);
        void validate_one_single_struct(StructDefinition& struct_definition);
        if (type_definition.struct_name == struct_definition.struct_name and type_definition.generics.size() == struct_definition.generics.size()) {
            if (avoiding_loops) throw std::runtime_error {"struct definitions loop detected"}; 
            else return;
        }
        validate_one_single_struct(type_definition);
        for (Instance& field : type_definition.internal_state) {
            if (std::holds_alternative<Pointer>(field.typesignature)) continue;
            validate_struct_field_typesignature(field.typesignature, type_definition, struct_definition, avoiding_loops);
        }
    }
    else if (std::holds_alternative<BaseType>(type) and is_default_integral_type(std::get<BaseType>(type))) return;
    else if (std::holds_alternative<Pointer>(type)) {
        validate_struct_field_typesignature(*std::get<Pointer>(type).pointed, struct_definition, struct_definition, false);
    }
    else if (std::holds_alternative<Array>(type)) validate_struct_field_typesignature(*std::get<Array>(type).type, struct_definition, struct_definition, true);
    else if (std::holds_alternative<NestedType>(type)) throw std::runtime_error{ "not implemented yet" };
    else throw InternalCompilerError { "type signature not recognized" };
}

bool template_generic_name_is_already_taken(const TypeSignature& template_generic, const StructDefinition& struct_definition){
    if (not std::holds_alternative<BaseType>(template_generic)) throw std::runtime_error { "a template generic is supposed to be a base-type" };
    if (is_default_integral_type(std::get<BaseType>(template_generic))) return true;
    std::shared_ptr<StructDefinition> struct_definition_ptr = std::make_shared<StructDefinition>(struct_definition);
    std::string name_in_global_scope = std::string{"global\\"} + std::get<BaseType>(template_generic).base_type;
    if (global_definitions_table.structs.find(name_in_global_scope) != global_definitions_table.structs.end()) return true;
    while (struct_definition_ptr != nullptr){
        std::string qualified_name = struct_definition_ptr->struct_name + "\\" + std::get<BaseType>(template_generic).base_type;
        if (global_definitions_table.structs.find(qualified_name) != global_definitions_table.structs.end()) return true;
        struct_definition_ptr = struct_definition_ptr->parent_scope;
    }
    return false;
}

bool template_generic_is_unique(const TypeSignature& target_generic, const StructDefinition& struct_definition){
    int counter = 0;
    if (std::holds_alternative<BaseType>(target_generic))
        for (const TypeSignature& template_generic : struct_definition.generics) {
            if (not std::holds_alternative<BaseType>(template_generic)) return false;
            counter += (std::get<BaseType>(template_generic).base_type == std::get<BaseType>(target_generic).base_type);
        }
    return (counter <= 1);
}

void validate_struct_template_generic(const TypeSignature& template_generic, const StructDefinition& struct_definition){
    if (not std::holds_alternative<BaseType>(template_generic)) throw std::runtime_error { "a template generic is supposed to be a base-type" };
    if (not std::get<BaseType>(template_generic).generics.empty()) throw std::runtime_error { "a template generic can't have generics itself" };
    if (template_generic_name_is_already_taken(template_generic, struct_definition)) throw std::runtime_error { "the name for this generic is already taken" };
    if (not template_generic_is_unique(template_generic, struct_definition)) throw std::runtime_error { "duplicated generic in struct definition" };
}

void validate_one_single_struct(StructDefinition& struct_definition){
    if (already_validated_structs.find(struct_definition.struct_name) != already_validated_structs.end()) return;
    already_validated_structs.insert(struct_definition.struct_name);
    for (const TypeSignature& template_generic : struct_definition.generics) 
        validate_struct_template_generic(template_generic, struct_definition);
    for (Instance& field : struct_definition.internal_state) 
        validate_struct_field_typesignature(field.typesignature, struct_definition, struct_definition, true);
}

void validate_structs_definitions(){
    for (auto& struct_definitions_table_entry : global_definitions_table.structs) 
        for (auto& struct_definition : struct_definitions_table_entry.second)
            validate_one_single_struct(struct_definition);
}