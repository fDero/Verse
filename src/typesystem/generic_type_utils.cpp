#include "../../include/verse.hpp"
#include "../../prototypes/procedures.hpp"

TypeSignature apply_generics_to_typesignature(const TypeSignature& generic_type, const GenericsLookupTable& generics_lookup_table){
    if (std::holds_alternative<BaseType>(generic_type)){
        for (const auto& pair : generics_lookup_table){
            if (std::get<BaseType>(generic_type).base_type == pair.first) return pair.second;
        }
        if (std::get<BaseType>(generic_type).generics.empty()) return generic_type;
        TypeSignature instanciated_generic_type = generic_type;
        for (TypeSignature& generic : std::get<BaseType>(instanciated_generic_type).generics){
            generic = apply_generics_to_typesignature(generic, generics_lookup_table);
        }
        return instanciated_generic_type;
    }
    else if (std::holds_alternative<Pointer>(generic_type)){
        const TypeSignature& pointed = *std::get<Pointer>(generic_type).pointed;
        TypeSignature instanciated_pointed_type = apply_generics_to_typesignature(pointed, generics_lookup_table);
        std::shared_ptr<TypeSignature> new_pointed_type = std::make_shared<TypeSignature>(instanciated_pointed_type);
        return Pointer { new_pointed_type };
    }
    else if (std::holds_alternative<Array>(generic_type)){
        const TypeSignature& array_type = *std::get<Array>(generic_type).type;
        int length = std::get<Array>(generic_type).length;
        TypeSignature instanciated_array_type = apply_generics_to_typesignature(array_type, generics_lookup_table);
        std::shared_ptr<TypeSignature> new_array_type = std::make_shared<TypeSignature>(instanciated_array_type);
        return Array { new_array_type, length };
    }
    else if (std::holds_alternative<NestedType>(generic_type)){
        const TypeSignature& left_type = *std::get<NestedType>(generic_type).left;
        const TypeSignature& right_type = *std::get<NestedType>(generic_type).right;
        TypeSignature instanciated_left_type = apply_generics_to_typesignature(left_type, generics_lookup_table);
        TypeSignature instanciated_right_type = apply_generics_to_typesignature(right_type, generics_lookup_table);
        std::shared_ptr<TypeSignature> left_type_ptr = std::make_shared<TypeSignature>(instanciated_left_type);
        std::shared_ptr<TypeSignature> right_type_ptr = std::make_shared<TypeSignature>(instanciated_right_type);
        return NestedType { left_type_ptr, right_type_ptr };
    }
    throw InternalCompilerError { "somehow a typesignature managed to hold something that is not a base-type, nor a pointer nor an array" };
}