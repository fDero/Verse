#include "../../include/verse.hpp"
#include "../../prototypes/procedures.hpp"

TypeSignature apply_generics_to_nested_type(const NestedType& nested_type, const GenericsLookupTable& generics_lookup_table){
    const TypeSignature& left_type = *nested_type.left;
    const TypeSignature& right_type = *nested_type.right;
    TypeSignature instanciated_left_type = apply_generics_to_typesignature(left_type, generics_lookup_table);
    TypeSignature instanciated_right_type = apply_generics_to_typesignature(right_type, generics_lookup_table);
    std::shared_ptr<TypeSignature> left_type_ptr = std::make_shared<TypeSignature>(instanciated_left_type);
    std::shared_ptr<TypeSignature> right_type_ptr = std::make_shared<TypeSignature>(instanciated_right_type);
    return NestedType { left_type_ptr, right_type_ptr };
}

TypeSignature apply_generics_to_array_type(const Array& array_type, const GenericsLookupTable& generics_lookup_table){
    const TypeSignature& stored_type = *array_type.type;
    int length = array_type.length;
    TypeSignature instanciated_stored_type = apply_generics_to_typesignature(stored_type, generics_lookup_table);
    std::shared_ptr<TypeSignature> new_stored_type = std::make_shared<TypeSignature>(instanciated_stored_type);
    return Array { new_stored_type, length };   
}

TypeSignature apply_generics_to_pointer_type(const Pointer& pointer_type, const GenericsLookupTable& generics_lookup_table){
    const TypeSignature& pointed = *pointer_type.pointed;
    TypeSignature instanciated_pointed_type = apply_generics_to_typesignature(pointed, generics_lookup_table);
    std::shared_ptr<TypeSignature> new_pointed_type = std::make_shared<TypeSignature>(instanciated_pointed_type);
    return Pointer { new_pointed_type };
}

TypeSignature apply_generics_to_base_type(const BaseType& type, const GenericsLookupTable& generics_lookup_table){
    BaseType instanciated_type = type;
    auto base_type_replacement = generics_lookup_table.find(type.base_type);
    if (base_type_replacement != generics_lookup_table.end()) return base_type_replacement->second;   
    for (TypeSignature& generic : instanciated_type.generics){
        generic = apply_generics_to_typesignature(generic, generics_lookup_table);
    }
    return instanciated_type;
}

TypeSignature apply_generics_to_typesignature(const TypeSignature& generic_type, const GenericsLookupTable& generics_lookup_table){
    if (std::holds_alternative<BaseType>(generic_type)){
        BaseType generic_base_type = std::get<BaseType>(generic_type);
        return apply_generics_to_base_type(generic_base_type, generics_lookup_table);
    }
    else if (std::holds_alternative<Pointer>(generic_type)){
        Pointer generic_pointer_type = std::get<Pointer>(generic_type);
        return apply_generics_to_pointer_type(generic_pointer_type, generics_lookup_table);
    }
    else if (std::holds_alternative<Array>(generic_type)){
        Array generic_array_type = std::get<Array>(generic_type);
        return apply_generics_to_array_type(generic_array_type, generics_lookup_table);
    }
    else if (std::holds_alternative<NestedType>(generic_type)){
        NestedType generic_nested_type = std::get<NestedType>(generic_type);
        return apply_generics_to_nested_type(generic_nested_type, generics_lookup_table);
    }
    throw InternalCompilerError { 
        "somehow a typesignature managed to hold something that is not a base-type, nor a pointer nor an array" 
    };
}