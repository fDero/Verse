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
    else if (std::holds_alternative<Pointer>(type)) throw std::runtime_error("pointers not yet supported");
    else if (std::holds_alternative<Array>(type)) throw std::runtime_error("arrays not yet supported");
    else if (std::holds_alternative<NestedType>(type)) {
        std::string left = type_to_string(*std::get<NestedType>(type).left);
        std::string right = type_to_string(*std::get<NestedType>(type).right);
        return left + "." + right;
    }
    else throw InternalCompilerError { "somehow a typesignature is not a base-type, nor an array nor a pointer" };
}