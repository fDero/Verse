#include "../include/verse.hpp"
#include "../include/procedures.hpp"

bool is_default_integral_type(const BaseType& type){
    if (type.base_type == "Int")    return true;
    if (type.base_type == "Float")  return true;
    if (type.base_type == "Char")   return true;
    if (type.base_type == "String") return true;
    if (type.base_type == "Bool")   return true;
    return false;
}

bool types_are_equal(const TypeSignature& typex, const TypeSignature& typey){
    if (std::holds_alternative<BaseType>(typex)){
        if (not std::holds_alternative<BaseType>(typey)) return false;
        if (std::get<BaseType>(typex).base_type != std::get<BaseType>(typey).base_type) return false;
        if (std::get<BaseType>(typex).generics.size() != std::get<BaseType>(typey).generics.size()) return false;
        std::vector<TypeSignature>::const_iterator typex_generics_cursor = std::get<BaseType>(typex).generics.begin();
        std::vector<TypeSignature>::const_iterator typey_generics_cursor = std::get<BaseType>(typey).generics.begin();
        while (typey_generics_cursor != std::get<BaseType>(typey).generics.end()) {
            if (not types_are_equal(*typex_generics_cursor, *typey_generics_cursor)) return false;
            std::advance(typex_generics_cursor,1);
            std::advance(typey_generics_cursor,1);
        }
        return true;
    }
    if (std::holds_alternative<Pointer>(typex)) {
        if (not std::holds_alternative<Pointer>(typey)) return false;
        return types_are_equal(*std::get<Pointer>(typex).pointed, *std::get<Pointer>(typey).pointed);
    }
    if (std::holds_alternative<Array>(typex)) {
        if (not std::holds_alternative<Array>(typey)) return false;
        if (std::get<Array>(typex).length != std::get<Array>(typey).length) return false;
        return types_are_equal(*std::get<Array>(typex).type, *std::get<Array>(typey).type);
    }
    if (std::holds_alternative<NestedType>(typex)){
        if (not std::holds_alternative<NestedType>(typey)) return false;
        bool left_equal = types_are_equal(*std::get<NestedType>(typex).left, *std::get<NestedType>(typey).left);
        bool right_equal = types_are_equal(*std::get<NestedType>(typex).right, *std::get<NestedType>(typey).right);
        return (left_equal and right_equal);
    }
    throw InternalCompilerError {
        "somehow a typesignature was parsed correctly and yet the interpreter doesn't recognize it " 
        "as a base-type nor an array nor a pointer nor a nested-type (dot-concatenation) of any of the previous"
    };
}

bool given_type_is_a_template_generic(const BaseType& target_type, const std::vector<TypeSignature>& generics){
    for (const TypeSignature& generic : generics){
        if (std::get<BaseType>(generic).base_type != target_type.base_type) continue;
        if (target_type.generics.size() > 0) continue;
        return true;
    }
    return false;
}

bool given_type_is_a_template_generic_for_this_struct(const BaseType& target_type, const StructDefinition& struct_definition){
    if(given_type_is_a_template_generic(target_type, struct_definition.generics)) return true;
    if(struct_definition.parent_scope == nullptr) return false;
    return given_type_is_a_template_generic_for_this_struct(target_type, *struct_definition.parent_scope);
}

bool typesignatures_vectors_are_equals(const std::vector<TypeSignature>& lx, const std::vector<TypeSignature>&rx){
    if (lx.size() != rx.size()) return false;
    for (int i = 0; i < lx.size(); i++) if (not types_are_equal(lx[i], rx[i])) return false;
    return true;
}