#include "../include/verse.hpp"
#include "../include/procedures.hpp"


ExpressionResult execute_logical_and_binary_operator(const BinaryOperator& binary_operator, ExecutionContext& context){
    auto [type, lx, rx] = execute_standard_binary_operator(binary_operator, context);
    if (std::get<BaseType>(type).base_type != "Bool") throw std::runtime_error { "binary operator is not defined on this type" };
    return { BaseType{"Bool"}, (BoolValue)(std::get<BoolValue>(lx) && std::get<BoolValue>(rx)) };
}

ExpressionResult execute_logical_or_binary_operator(const BinaryOperator& binary_operator, ExecutionContext& context){
    auto [type, lx, rx] = execute_standard_binary_operator(binary_operator, context);
    if (std::get<BaseType>(type).base_type != "Bool") throw std::runtime_error { "binary operator is not defined on this type" };
    return { BaseType{"Bool"}, (BoolValue)(std::get<BoolValue>(lx) || std::get<BoolValue>(rx)) };
}

ExpressionResult execute_logical_xor_binary_operator(const BinaryOperator& binary_operator, ExecutionContext& context){
    auto [type, lx, rx] = execute_standard_binary_operator(binary_operator, context);
    if (std::get<BaseType>(type).base_type != "Bool") throw std::runtime_error { "binary operator is not defined on this type" };
    return { BaseType{"Bool"}, (BoolValue)(std::get<BoolValue>(lx) != std::get<BoolValue>(rx)) };
}

ExpressionResult execute_less_then_comparison(const BinaryOperator& binary_operator, ExecutionContext& context){
    auto [type, lx, rx] = execute_standard_binary_operator(binary_operator, context);
    if (std::get<BaseType>(type).base_type == "Int")    return { BaseType{"Bool"}, (BoolValue) (std::get<IntegerValue>(lx) < std::get<IntegerValue>(rx)) };
    if (std::get<BaseType>(type).base_type == "Float")  return { BaseType{"Bool"}, (BoolValue) (std::get<FloatValue>(lx) < std::get<FloatValue>(rx)) };
    if (std::get<BaseType>(type).base_type == "Char")   return { BaseType{"Bool"}, (BoolValue) (std::get<CharValue>(lx) < std::get<CharValue>(rx)) };
    if (std::get<BaseType>(type).base_type == "String") return { BaseType{"Bool"}, (BoolValue) (std::get<StringValue>(lx) < std::get<StringValue>(rx)) };
    if (std::get<BaseType>(type).base_type == "Bool")   return { BaseType{"Bool"}, (BoolValue) (std::get<BoolValue>(lx) < std::get<BoolValue>(rx)) };
    throw std::runtime_error { "binary operator is not defined on this type" };
}

ExpressionResult execute_greater_then_comparison(const BinaryOperator& binary_operator, ExecutionContext& context){
    auto [type, lx, rx] = execute_standard_binary_operator(binary_operator, context);
    if (std::get<BaseType>(type).base_type == "Int")    return { BaseType{"Bool"}, (BoolValue) (std::get<IntegerValue>(lx) > std::get<IntegerValue>(rx)) };
    if (std::get<BaseType>(type).base_type == "Float")  return { BaseType{"Bool"}, (BoolValue) (std::get<FloatValue>(lx) > std::get<FloatValue>(rx)) };
    if (std::get<BaseType>(type).base_type == "Char")   return { BaseType{"Bool"}, (BoolValue) (std::get<CharValue>(lx) > std::get<CharValue>(rx)) };
    if (std::get<BaseType>(type).base_type == "String") return { BaseType{"Bool"}, (BoolValue) (std::get<StringValue>(lx) > std::get<StringValue>(rx)) };
    if (std::get<BaseType>(type).base_type == "Bool")   return { BaseType{"Bool"}, (BoolValue) (std::get<BoolValue>(lx) > std::get<BoolValue>(rx)) };
    throw std::runtime_error { "binary operator is not defined on this type" };
}

ExpressionResult execute_less_then_or_equal_to_comparison(const BinaryOperator& binary_operator, ExecutionContext& context){
    auto [type, lx, rx] = execute_standard_binary_operator(binary_operator, context);
    if (std::get<BaseType>(type).base_type == "Int")    return { BaseType{"Bool"}, (BoolValue) (std::get<IntegerValue>(lx) <= std::get<IntegerValue>(rx)) };
    if (std::get<BaseType>(type).base_type == "Float")  return { BaseType{"Bool"}, (BoolValue) (std::get<FloatValue>(lx) <= std::get<FloatValue>(rx)) };
    if (std::get<BaseType>(type).base_type == "Char")   return { BaseType{"Bool"}, (BoolValue) (std::get<CharValue>(lx) <= std::get<CharValue>(rx)) };
    if (std::get<BaseType>(type).base_type == "String") return { BaseType{"Bool"}, (BoolValue) (std::get<StringValue>(lx) <= std::get<StringValue>(rx)) };
    if (std::get<BaseType>(type).base_type == "Bool")   return { BaseType{"Bool"}, (BoolValue) (std::get<BoolValue>(lx) <= std::get<BoolValue>(rx)) };
    throw std::runtime_error { "binary operator is not defined on this type" };
}

ExpressionResult execute_greater_then_or_equal_to_comparison(const BinaryOperator& binary_operator, ExecutionContext& context){
    auto [type, lx, rx] = execute_standard_binary_operator(binary_operator, context);
    if (std::get<BaseType>(type).base_type == "Int")    return { BaseType{"Bool"}, (BoolValue) (std::get<IntegerValue>(lx) >= std::get<IntegerValue>(rx)) };
    if (std::get<BaseType>(type).base_type == "Float")  return { BaseType{"Bool"}, (BoolValue) (std::get<FloatValue>(lx) >= std::get<FloatValue>(rx)) };
    if (std::get<BaseType>(type).base_type == "Char")   return { BaseType{"Bool"}, (BoolValue) (std::get<CharValue>(lx) >= std::get<CharValue>(rx)) };
    if (std::get<BaseType>(type).base_type == "String") return { BaseType{"Bool"}, (BoolValue) (std::get<StringValue>(lx) >= std::get<StringValue>(rx)) };
    if (std::get<BaseType>(type).base_type == "Bool")   return { BaseType{"Bool"}, (BoolValue) (std::get<BoolValue>(lx) >= std::get<BoolValue>(rx)) };
    throw std::runtime_error { "binary operator is not defined on this type" };
}

ExpressionResult execute_equality_comparison(const BinaryOperator& binary_operator, ExecutionContext& context){
    auto [type, lx, rx] = execute_standard_binary_operator(binary_operator, context);
    if (std::get<BaseType>(type).base_type == "Int")    return { BaseType{"Bool"}, (BoolValue) (std::get<IntegerValue>(lx) == std::get<IntegerValue>(rx)) };
    if (std::get<BaseType>(type).base_type == "Float")  return { BaseType{"Bool"}, (BoolValue) (std::get<FloatValue>(lx) == std::get<FloatValue>(rx)) };
    if (std::get<BaseType>(type).base_type == "Char")   return { BaseType{"Bool"}, (BoolValue) (std::get<CharValue>(lx) == std::get<CharValue>(rx)) };
    if (std::get<BaseType>(type).base_type == "String") return { BaseType{"Bool"}, (BoolValue) (std::get<StringValue>(lx) == std::get<StringValue>(rx)) };
    if (std::get<BaseType>(type).base_type == "Bool")   return { BaseType{"Bool"}, (BoolValue) (std::get<BoolValue>(lx) == std::get<BoolValue>(rx)) };
    throw std::runtime_error { "binary operator is not defined on this type" };
}

ExpressionResult execute_inequality_comparison(const BinaryOperator& binary_operator, ExecutionContext& context){
    auto [type, lx, rx] = execute_standard_binary_operator(binary_operator, context);
    if (std::get<BaseType>(type).base_type == "Int")    return { BaseType{"Bool"}, (BoolValue) (std::get<IntegerValue>(lx) != std::get<IntegerValue>(rx)) };
    if (std::get<BaseType>(type).base_type == "Float")  return { BaseType{"Bool"}, (BoolValue) (std::get<FloatValue>(lx) != std::get<FloatValue>(rx)) };
    if (std::get<BaseType>(type).base_type == "Char")   return { BaseType{"Bool"}, (BoolValue) (std::get<CharValue>(lx) != std::get<CharValue>(rx)) };
    if (std::get<BaseType>(type).base_type == "String") return { BaseType{"Bool"}, (BoolValue) (std::get<StringValue>(lx) != std::get<StringValue>(rx)) };
    if (std::get<BaseType>(type).base_type == "Bool")   return { BaseType{"Bool"}, (BoolValue) (std::get<BoolValue>(lx) != std::get<BoolValue>(rx)) };
    throw std::runtime_error { "binary operator is not defined on this type" };
}

ExpressionResult execute_logical_not(const Instruction& operand, ExecutionContext& context){
    auto [type, value] = execute_expression(operand, context);
    if (not std::holds_alternative<BaseType>(type)) throw std::runtime_error { "non base-type operands for binary operator" };
    if (not is_default_integral_type(type)) throw std::runtime_error { "non integral-type operands for binary operator" };
    if (std::get<BaseType>(type).base_type != "Bool") throw std::runtime_error { "logical not operator is not defined on this type" }; 
    return { BaseType{"Bool"}, (BoolValue)(!std::get<BoolValue>(value)) };
}

ExpressionResult execute_logical_binary_operator(const BinaryOperator& binary_operator, ExecutionContext& context){
    if (binary_operator.text == "||") return execute_logical_or_binary_operator(binary_operator, context);
    if (binary_operator.text == "&&") return execute_logical_and_binary_operator(binary_operator, context);
    if (binary_operator.text == "^^") return execute_logical_xor_binary_operator(binary_operator, context);
    if (binary_operator.text == "<=") return execute_less_then_or_equal_to_comparison(binary_operator, context);
    if (binary_operator.text == ">=") return execute_greater_then_or_equal_to_comparison(binary_operator, context);
    if (binary_operator.text == "==") return execute_equality_comparison(binary_operator, context);
    if (binary_operator.text == "!=") return execute_inequality_comparison(binary_operator, context);
    if (binary_operator.text == "<")  return execute_less_then_comparison(binary_operator, context);
    if (binary_operator.text == ">")  return execute_greater_then_comparison(binary_operator, context);
    throw InternalCompilerError {
        "somehow a token was parsed as a logical-binary-operator, even tough it cannot be recognized"
    };
}