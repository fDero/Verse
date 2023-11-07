#include "../../include/verse.hpp"
#include "../../prototypes/procedures.hpp"

BinaryOperatorData execute_standard_binary_operator(const BinaryOperator& binary_operator, ExecutionContext& context){
    auto [lx_type, lx_value] = execute_expression(*binary_operator.lx, context);
    auto [rx_type, rx_value] = execute_expression(*binary_operator.rx, context);
    if (not std::holds_alternative<BaseType>(lx_type)) throw std::runtime_error { "non base-type operands for binary operator" };
    if (not std::holds_alternative<BaseType>(rx_type)) throw std::runtime_error { "non base-type operands for binary operator" };
    if (not is_default_integral_type(lx_type)) throw std::runtime_error { "non integral-type operands for binary operator" };
    if (not is_default_integral_type(rx_type)) throw std::runtime_error { "non integral-type operands for binary operator" };
    if (not typesignatures_are_equal(lx_type, rx_type)) throw std::runtime_error { "operand of different types" };
    return BinaryOperatorData { lx_type, lx_value, rx_value };
}

ExpressionResult execute_unary_operator(const UnaryOperator& unary_operator,ExecutionContext& context){
    if (unary_operator.text == "!") return execute_logical_not(*unary_operator.operand, context);
    if (unary_operator.text == "-") return execute_minus_sign(*unary_operator.operand, context);
    if (unary_operator.text == "-") return execute_plus_sign(*unary_operator.operand, context);
    if (unary_operator.text == "#") return execute_address_operator(*unary_operator.operand, context);
    throw InternalCompilerError {
        "somehow a token was parsed as a unary-operator, even tough it cannot be recognized"
    };
}

ExpressionResult execute_binary_operator(const BinaryOperator& binary_operator,ExecutionContext& context){
    if (binary_operator.text == ".")  return dot_access_on_struct_member(binary_operator, context);
    if (binary_operator.text == "+")  return execute_math_binary_operator(binary_operator, context);
    if (binary_operator.text == "-")  return execute_math_binary_operator(binary_operator, context);
    if (binary_operator.text == "*")  return execute_math_binary_operator(binary_operator, context);
    if (binary_operator.text == "/")  return execute_math_binary_operator(binary_operator, context);
    if (binary_operator.text == "%")  return execute_math_binary_operator(binary_operator, context);
    if (binary_operator.text == "^")  return execute_math_binary_operator(binary_operator, context);
    if (binary_operator.text == "<")  return execute_logical_binary_operator(binary_operator, context);
    if (binary_operator.text == ">")  return execute_logical_binary_operator(binary_operator, context);
    if (binary_operator.text == "<=") return execute_logical_binary_operator(binary_operator, context);
    if (binary_operator.text == ">=") return execute_logical_binary_operator(binary_operator, context);
    if (binary_operator.text == "==") return execute_logical_binary_operator(binary_operator, context);
    if (binary_operator.text == "!=") return execute_logical_binary_operator(binary_operator, context);
    if (binary_operator.text == "&&") return execute_logical_binary_operator(binary_operator, context);
    if (binary_operator.text == "||") return execute_logical_binary_operator(binary_operator, context);
    if (binary_operator.text == "^^") return execute_logical_binary_operator(binary_operator, context);
    throw InternalCompilerError {
        "somehow a token was parsed as a binary-operator, even tough it cannot be recognized"
    };
}

ExpressionResult get_identifier(const Identifier& identifier, ExecutionContext& context){
    if (context.variable_values.find(identifier.name) != context.variable_values.end()){
        RuntimeValue& value = context.variable_values[identifier.name];
        TypeSignature& type = context.variable_types[identifier.name];
        return ExpressionResult { type, value };
    }
    if (context.constant_values.find(identifier.name) != context.constant_values.end()){
        RuntimeValue& value = context.constant_values[identifier.name];
        TypeSignature& type = context.constant_types[identifier.name];
        return ExpressionResult { type, value };
    }
    throw std::runtime_error {
        "no such identifier exists in the current scope, or, if it does, it doesn't in "
        "the form of a variable or a constant therefore it's not accessible "
    };
}

ExpressionResult get_literal(const Literal& literal){
    if (literal.pseudotype == "Int")     return { BaseType{ "Int" },    (IntegerValue) std::stoi(literal.value) };
    if (literal.pseudotype == "Float")   return { BaseType{ "Float" },  (FloatValue)   std::stod(literal.value) };
    if (literal.pseudotype == "Char")    return { BaseType{ "Char" },   (CharValue)    literal.value.back()     };
    if (literal.pseudotype == "String")  return { BaseType{ "String" }, (StringValue)  literal.value            };
    if (literal.pseudotype == "Bool")    return { BaseType{ "Bool" },   (BoolValue)   (literal.value == "true") };
    throw std::runtime_error {
        "attempt to evaluate a literal of unknown kind, it isn't an integer(int), nor a decimal (floating-point), "
        "nor a character(char), nor a boolean(bool) nor a text-string(string), doesn't know what to do"
    };
}

ExpressionResult execute_expression(const Instruction& expr, ExecutionContext& context){
    if (std::holds_alternative<Literal>(expr)) return get_literal(std::get<Literal>(expr));
    if (std::holds_alternative<Identifier>(expr)) return get_identifier(std::get<Identifier>(expr), context);
    if (std::holds_alternative<FunctionCall>(expr)) return execute_function_call(std::get<FunctionCall>(expr), context);
    if (std::holds_alternative<UnaryOperator>(expr)) return execute_unary_operator(std::get<UnaryOperator>(expr), context);
    if (std::holds_alternative<BinaryOperator>(expr)) return execute_binary_operator(std::get<BinaryOperator>(expr), context);
    throw std::runtime_error {
        "attempt to evaluate an expression of unknown king, it isn't recognized as a literal, nor an identifier, nor a function call, "
        "nor a unary-operator(prefix) nor a binary-operator(infix), doesn't know what to do"
    };
}