#include "../include/verse.hpp"
#include "../include/procedures.hpp"

ExpressionResult execute_add_binary_operator(const BinaryOperator& binary_operator,ExecutionContext& context){
    auto [type, lx, rx] = execute_standard_binary_operator(binary_operator, context);
    if (std::get<BaseType>(type).base_type == "Int") return { type, (IntegerValue)(std::get<IntegerValue>(lx) + std::get<IntegerValue>(rx)) };
    if (std::get<BaseType>(type).base_type == "Float") return { type, (FloatValue)(std::get<FloatValue>(lx) + std::get<FloatValue>(rx)) };
    if (std::get<BaseType>(type).base_type == "String") return { type, (StringValue)(std::get<StringValue>(lx) + std::get<StringValue>(rx)) };
    throw std::runtime_error { "binary operator is not defined on this type" };
}

ExpressionResult execute_min_binary_operator(const BinaryOperator& binary_operator,ExecutionContext& context){
    auto [type, lx, rx] = execute_standard_binary_operator(binary_operator, context);
    if (std::get<BaseType>(type).base_type == "Int") return { type, (IntegerValue)(std::get<IntegerValue>(lx) - std::get<IntegerValue>(rx)) };
    if (std::get<BaseType>(type).base_type == "Float") return { type, (FloatValue)(std::get<FloatValue>(lx) - std::get<FloatValue>(rx)) };
    throw std::runtime_error { "binary operator is not defined on this type" };
}

ExpressionResult execute_mul_binary_operator(const BinaryOperator& binary_operator,ExecutionContext& context){
    auto [type, lx, rx] = execute_standard_binary_operator(binary_operator, context);
    if (std::get<BaseType>(type).base_type == "Int") return { type, (IntegerValue)(std::get<IntegerValue>(lx) * std::get<IntegerValue>(rx)) };
    if (std::get<BaseType>(type).base_type == "Float") return { type, (FloatValue)(std::get<FloatValue>(lx) * std::get<FloatValue>(rx)) };
    if (std::get<BaseType>(type).base_type == "String") return { type, (StringValue)(std::get<StringValue>(lx) + " " + std::get<StringValue>(rx)) };
    throw std::runtime_error { "binary operator is not defined on this type" };
}

ExpressionResult execute_div_binary_operator(const BinaryOperator& binary_operator,ExecutionContext& context){
    auto [type, lx, rx] = execute_standard_binary_operator(binary_operator, context);
    if (std::get<BaseType>(type).base_type == "Int") return { type, (IntegerValue)(std::get<IntegerValue>(lx) / std::get<IntegerValue>(rx)) };
    if (std::get<BaseType>(type).base_type == "Float") return { type, (FloatValue)(std::get<FloatValue>(lx) / std::get<FloatValue>(rx)) };
    throw std::runtime_error { "binary operator is not defined on this type" };
}

ExpressionResult execute_mod_binary_operator(const BinaryOperator& binary_operator,ExecutionContext& context){
    auto [type, lx, rx] = execute_standard_binary_operator(binary_operator, context);
    if (std::get<BaseType>(type).base_type == "Int") return { type, (IntegerValue)(std::get<IntegerValue>(lx) % std::get<IntegerValue>(rx)) };
    throw std::runtime_error { "binary operator is not defined on this type" };
}

ExpressionResult execute_pow_binary_operator(const BinaryOperator& binary_operator,ExecutionContext& context){
    auto [lx_type, lx] = execute_expression(*binary_operator.lx, context);
    auto [rx_type, rx] = execute_expression(*binary_operator.rx, context);
    if (not std::holds_alternative<BaseType>(lx_type) or not std::holds_alternative<BaseType>(rx_type)) {
        throw std::runtime_error { "non base-type operands for binary operator" };
    }
    if (not is_default_integral_type(lx_type) or not is_default_integral_type(rx_type)){
        throw std::runtime_error { "non integral-type operands for binary operator" };
    }
    if (std::get<BaseType>(rx_type).base_type != "Int") throw std::runtime_error { "exponents for the power operator (^) are supposed to be integers" };
    if (std::get<BaseType>(lx_type).base_type == "Int") return { BaseType{"Int"}, (IntegerValue)std::pow(std::get<IntegerValue>(lx),std::get<IntegerValue>(rx)) };
    if (std::get<BaseType>(lx_type).base_type == "Float") return { BaseType{"Float"}, (FloatValue)std::pow(std::get<FloatValue>(lx),std::get<IntegerValue>(rx)) };
    throw std::runtime_error { "binary operator is not defined on this type" };
}

ExpressionResult execute_math_binary_operator(const BinaryOperator& binary_operator,ExecutionContext& context){
    if (binary_operator.text == ".")  return dot_access_on_struct_member(binary_operator, context);
    if (binary_operator.text == "+")  return execute_add_binary_operator(binary_operator, context);
    if (binary_operator.text == "-")  return execute_min_binary_operator(binary_operator, context);
    if (binary_operator.text == "*")  return execute_mul_binary_operator(binary_operator, context);
    if (binary_operator.text == "/")  return execute_div_binary_operator(binary_operator, context);
    if (binary_operator.text == "%")  return execute_mod_binary_operator(binary_operator, context);
    if (binary_operator.text == "^")  return execute_pow_binary_operator(binary_operator, context);
    throw InternalCompilerError {
        "somehow a token was parsed as a mathematical-binary-operator, even tough it cannot be recognized"
    };
}

ExpressionResult execute_unary_math_sign(const Instruction& operand, ExecutionContext& context, short sign){
    auto [type, value] = execute_expression(operand, context);
    if (not std::holds_alternative<BaseType>(type)) throw std::runtime_error { "non base-type operands for binary operator" };
    if (not is_default_integral_type(type)) throw std::runtime_error { "non integral-type operands for binary operator" };
    if (std::get<BaseType>(type).base_type == "Int") return { BaseType{"Int"}, (IntegerValue)(std::get<IntegerValue>(value) * sign) };
    if (std::get<BaseType>(type).base_type == "Float") return { BaseType{"Float"}, (FloatValue)(std::get<FloatValue>(value) * sign) };
    throw std::runtime_error { "binary operator is not defined on this type" };
}

ExpressionResult execute_minus_sign(const Instruction& operand, ExecutionContext& context){
    return execute_unary_math_sign(operand, context, -1);
}

ExpressionResult execute_plus_sign(const Instruction& operand, ExecutionContext& context){
    return execute_unary_math_sign(operand, context, 1);
}