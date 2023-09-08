#include "../include/verse.hpp"
#include "../include/procedures.hpp"

std::string craft_type_regex(const BaseType& type){
    std::string regex = type.base_type + "<";
    for (const TypeSignature& generic : type.generics) regex += ".*,";
    regex.back() = '>';
    if (type.generics.empty()) regex.pop_back();
    return ".*" + regex + "$";
}

std::string craft_struct_regex(const StructDefinition& structdef){
    std::string regex = structdef.struct_name;
    for (const TypeSignature& generic : structdef.generics) regex += ".*,";
    regex.back() = '>';
    if (structdef.generics.empty()) regex.pop_back();
    if (structdef.parent_scope != nullptr){
        regex = craft_struct_regex(*structdef.parent_scope) + "." + regex;
    }
    return regex;
}

StructDefinition retrieve_actual_struct_from_struct_field_typesignature(BaseType& type, StructDefinition& structdef){
    std::vector<std::string> available_candidates;
    std::regex type_regex {craft_type_regex(type)};
    for (const std::string& candidate : global_structs_names_register[type.base_type]){
        if (std::regex_match(candidate, type_regex)) available_candidates.push_back(candidate);
    }
    std::shared_ptr<StructDefinition> scope = std::make_shared<StructDefinition>(structdef);
    while (scope != nullptr){
        std::regex struct_regex {craft_struct_regex(structdef) + "." + craft_type_regex(type)};
        for (const std::string& candidate : available_candidates){
            if (std::regex_match(candidate, struct_regex)) return global_structs_definitions[candidate];
        }
        scope = scope->parent_scope;
    }
    std::regex struct_regex {craft_type_regex(type)};
    for (const std::string& candidate : available_candidates){
        if (std::regex_match(candidate, struct_regex)) return global_structs_definitions[candidate];
    }
    return StructDefinition{};
}

TypeSignature get_typesignature_from_struct(StructDefinition& structdef){
    if (structdef.parent_scope == nullptr) return BaseType{ structdef.struct_name, structdef.generics };
    return NestedType { 
        std::make_shared<TypeSignature>(get_typesignature_from_struct(*structdef.parent_scope)),
        std::make_shared<TypeSignature>(BaseType{structdef.struct_name, structdef.generics})
    };
}

void fully_qualify_struct_field_basetype(TypeSignature& type, StructDefinition& structdef){
    if (not std::holds_alternative<BaseType>(type)) throw InternalCompilerError { "attempt to qualify as a base-type a non base-type token" };
    StructDefinition retrieved = retrieve_actual_struct_from_struct_field_typesignature(std::get<BaseType>(type), structdef);
    std::string old = type_to_string(type);
    retrieved.generics = std::get<BaseType>(type).generics;
    for (TypeSignature& generic : retrieved.generics) fully_qualify_struct_field_typesignature(generic, structdef);
    if (not retrieved.struct_name.empty()) type = get_typesignature_from_struct(retrieved);
}

void fully_qualify_struct_field_nestedtype(NestedType& type, StructDefinition& structdef){
    for (TypeSignature& generic : std::get<BaseType>(*type.right).generics) fully_qualify_struct_field_typesignature(generic, structdef);
    fully_qualify_struct_field_typesignature(*type.left, structdef);
}


void fully_qualify_struct_field_typesignature(TypeSignature& type, StructDefinition& structdef){
    if (std::holds_alternative<Pointer>(type)) fully_qualify_struct_field_typesignature(*std::get<Pointer>(type).pointed, structdef);
    else if (std::holds_alternative<Array>(type)) fully_qualify_struct_field_typesignature(*std::get<Array>(type).type, structdef);
    else if (std::holds_alternative<BaseType>(type)) fully_qualify_struct_field_basetype(type, structdef);
    else if (std::holds_alternative<NestedType>(type)) fully_qualify_struct_field_nestedtype(std::get<NestedType>(type), structdef);
}

void fully_qualify_struct_fields(){
    for (auto& structdef_data : global_structs_definitions){
        for (Instance& field : structdef_data.second.internal_state){
            fully_qualify_struct_field_typesignature(field.typesignature, structdef_data.second);
        }
    }
}