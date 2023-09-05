#include "../include/verse.hpp"
#include "../include/procedures.hpp"

bool compare_base_types(const BaseType& typex, const BaseType& typey){
    if (typex.base_type != typey.base_type) return false;
    if (typex.generics.size() != typey.generics.size()) return false;
    std::vector<TypeSignature>::const_iterator typex_generics_cursor = typex.generics.begin();
    std::vector<TypeSignature>::const_iterator typey_generics_cursor = typey.generics.begin();
    while (typey_generics_cursor != typey.generics.end()) {
        if (not typesignatures_are_equal(*typex_generics_cursor, *typey_generics_cursor)) return false;
        std::advance(typex_generics_cursor,1);
        std::advance(typey_generics_cursor,1);
    }
    return true;
}

bool typesignatures_are_equal(const TypeSignature& typex, const TypeSignature& typey){
    if (std::holds_alternative<BaseType>(typex)) {
        if (not std::holds_alternative<BaseType>(typey)) return false;
        return compare_base_types(std::get<BaseType>(typex), std::get<BaseType>(typey));
    }
    if (std::holds_alternative<Pointer>(typex)) {
        if (not std::holds_alternative<Pointer>(typey)) return false;
        return typesignatures_are_equal(*std::get<Pointer>(typex).pointed, *std::get<Pointer>(typey).pointed);
    }
    if (std::holds_alternative<Array>(typex)) {
        if (not std::holds_alternative<Array>(typey)) return false;
        if (std::get<Array>(typex).length != std::get<Array>(typey).length) return false;
        return typesignatures_are_equal(*std::get<Array>(typex).type, *std::get<Array>(typey).type);
    }
    if (std::holds_alternative<NestedType>(typex)){
        if (not std::holds_alternative<NestedType>(typey)) return false;
        bool left_equal = typesignatures_are_equal(*std::get<NestedType>(typex).left, *std::get<NestedType>(typey).left);
        bool right_equal = typesignatures_are_equal(*std::get<NestedType>(typex).right, *std::get<NestedType>(typey).right);
        return (left_equal and right_equal);
    }
    throw InternalCompilerError {
        "somehow a typesignature was parsed correctly and yet the interpreter doesn't recognize it " 
        "as a base-type nor an array nor a pointer"
    };
}

bool is_default_integral_type(const TypeSignature& type){
    if (not std::holds_alternative<BaseType>(type)) return false;
    else if (std::get<BaseType>(type).base_type == "Int")    return true;
    else if (std::get<BaseType>(type).base_type == "Float")  return true;
    else if (std::get<BaseType>(type).base_type == "Bool")   return true;
    else if (std::get<BaseType>(type).base_type == "Char")   return true;
    else if (std::get<BaseType>(type).base_type == "String") return true;
    return false;
}