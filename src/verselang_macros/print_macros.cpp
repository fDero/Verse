#include "../include/verse.hpp"
#include "../include/procedures.hpp"

void print_struct(const RuntimeValue& value){
    if (std::holds_alternative<StructValue>(value)){
        StructValue structx = std::get<StructValue>(value);
        std::cout << "{ "; verselang_print_macro(structx.fields); std::cout << "} "; 
    }
    else {
        throw InternalCompilerError { "print_strcut() procedure called on a non-struct-value" };
    }
}

void print_array(const RuntimeValue& value){
    if (std::holds_alternative<ArrayValue>(value)){
        ArrayValue array = std::get<ArrayValue>(value);
        std::cout << "[ "; verselang_print_macro(array.values); std::cout << "] ";
    }
    throw InternalCompilerError { "print_array() procedure called on a non-array-value" };
}

void print_pointer(const RuntimeValue& value){
    if (std::holds_alternative<PointerValue>(value)){
        if (std::get<PointerValue>(value).pointer != nullptr) {
            std::cout << "#" << std::setfill('0') << std::setw(16) << std::hex;
            std::cout << std::get<PointerValue>(value).pointer;
            std::cout << std::dec << " ";
        }
        else std::cout << "nullptr" << " ";
    }
}

ExpressionResult verselang_print_macro(const std::vector<RuntimeValue>& arguments){
    std::cout << std::boolalpha;
    for (const RuntimeValue& arg : arguments){
        if (std::holds_alternative<StructValue>(arg)) print_struct(arg);
        else if (std::holds_alternative<ArrayValue>(arg)) print_array(arg);
        else if (std::holds_alternative<PointerValue>(arg)) print_pointer(arg);
        else if (std::holds_alternative<VoidValue>(arg))    std::cout << "void" << " ";
        else if (std::holds_alternative<IntegerValue>(arg)) std::cout << std::get<IntegerValue>(arg) << " ";
        else if (std::holds_alternative<FloatValue>(arg))   std::cout << std::get<FloatValue>(arg)   << " ";
        else if (std::holds_alternative<CharValue>(arg))    std::cout << std::get<CharValue>(arg)    << " ";
        else if (std::holds_alternative<BoolValue>(arg))    std::cout << std::get<BoolValue>(arg)    << " ";
        else if (std::holds_alternative<StringValue>(arg))  std::cout << std::get<StringValue>(arg)  << " ";
        else throw InternalCompilerError { "RuntimeValue cannot be printed (cannot be recognized)" };
    }
    return { BaseType{"Void"} , VoidValue{} };
}

ExpressionResult verselang_println_macro(const std::vector<RuntimeValue>& arguments){
    verselang_print_macro(arguments);
    std::cout << std::endl;
    return { BaseType{"Void"} , VoidValue{} };
}

void initialize_print_macros(){
    
    auto print_macro = std::make_pair<std::string, verselang_macro_procedure>("print", 
        [](const ArgumentTypes& types, const ArgumentValues& values, ExecutionContext& context){ 
            return verselang_print_macro(values); 
        }
    );

    auto println_macro = std::make_pair<std::string, verselang_macro_procedure>("println", 
        [](const ArgumentTypes& types, const ArgumentValues& values, ExecutionContext& context){ 
            return verselang_println_macro(values); 
        }
    );

    verselang_macros.insert(print_macro);
    verselang_macros.insert(println_macro);
}
