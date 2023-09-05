#include "../include/verse.hpp"
#include "../include/procedures.hpp"

ExpressionResult verselang_typeof_macro(const std::vector<TypeSignature>& arguments){
    if (arguments.size() != 1) throw std::runtime_error{ "wrong number of arguments for typestr" };
    return { BaseType{"String"}, (StringValue)type_to_string(arguments[0]) };
}

void initialize_type_macros(){

    auto typeof_macro = std::make_pair<std::string, verselang_macro_procedure>("typeof", 
        [](const ArgumentTypes& types, const ArgumentValues& values, ExecutionContext& context){ 
            return verselang_typeof_macro(types); 
        }
    );

    verselang_macros.insert(typeof_macro);
}
