#include "../include/verse.hpp"
#include "../include/procedures.hpp"

std::string type_to_string(const TypeSignature& type){
    if (std::holds_alternative<BaseType>(type)){
        std::string type_str = std::get<BaseType>(type).base_type;
        std::string generics_str = "<";
        for (const TypeSignature& generic : std::get<BaseType>(type).generics){
            generics_str += type_to_string(generic) + ",";
        }
        generics_str.back() = '>';
        if (generics_str.size() <= 1) return type_str;
        return type_str + generics_str;
    }
    else if (std::holds_alternative<Pointer>(type)) return "#" + type_to_string(*std::get<Pointer>(type).pointed);
    else if (std::holds_alternative<Array>(type)) return "Array[" + type_to_string(*std::get<Pointer>(type).pointed) + "]";
    else if (std::holds_alternative<NestedType>(type)) {
        std::string left = type_to_string(*std::get<NestedType>(type).left);
        std::string right = type_to_string(*std::get<NestedType>(type).right);
        return left + "." + right;
    }
    else throw InternalCompilerError { "somehow a typesignature is not a base-type, nor an array nor a pointer" };
}

std::string type_to_string_without_generics(const TypeSignature& type){
    if (std::holds_alternative<BaseType>(type)) return std::get<BaseType>(type).base_type;
    else if (std::holds_alternative<Pointer>(type)) return "#" + type_to_string_without_generics(*std::get<Pointer>(type).pointed);
    else if (std::holds_alternative<Array>(type)) return "Array[" + type_to_string_without_generics(*std::get<Pointer>(type).pointed) + "]";
    else if (std::holds_alternative<NestedType>(type)) {
        std::string left = type_to_string_without_generics(*std::get<NestedType>(type).left);
        std::string right = type_to_string_without_generics(*std::get<NestedType>(type).right);
        return left + "." + right;
    }
    else throw InternalCompilerError { "somehow a typesignature is not a base-type, nor an array nor a pointer" };
}

std::string most_derived_type(const TypeSignature& type){
    if (std::holds_alternative<BaseType>(type)) return std::get<BaseType>(type).base_type;
    if (std::holds_alternative<Pointer>(type)) return most_derived_type(*std::get<Pointer>(type).pointed);
    if (std::holds_alternative<Array>(type)) return most_derived_type(*std::get<Array>(type).type);
    if (std::holds_alternative<NestedType>(type)) return most_derived_type(*std::get<NestedType>(type).right);
    throw InternalCompilerError {
        "Typesignature is neither a base-type, nor a pointer, nor an array nor a nested-type"
    };
}

std::string get_qualified_struct_name(const StructDefinition& structdef){    
    std::string prefix = (structdef.parent_scope != nullptr)? get_qualified_struct_name(*structdef.parent_scope) + "." : "";
    std::string name = structdef.struct_name;
    std::string generics = "<";
    for (const auto& generic : structdef.generics) generics += "[^,]*,";
    generics.back() = '>';
    if (generics.size() <= 1) generics.clear();
    return (prefix + name + generics);
}