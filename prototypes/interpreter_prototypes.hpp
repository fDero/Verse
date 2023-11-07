#pragma once
#include "../include/verse.hpp"

Instruction execute_instruction(const Instruction&,ExecutionContext&);
Instruction execute_conditional(const Conditional&, ExecutionContext&);
Instruction execute_until_loop(const UntilLoop&, ExecutionContext&);
Instruction execute_while_loop(const WhileLoop&, ExecutionContext&);
BinaryOperatorData execute_standard_binary_operator(const BinaryOperator&,ExecutionContext&);
ExpressionResult dot_access_on_struct_member(const Instruction&,ExecutionContext&);
ExpressionResult execute_function_call(const FunctionCall&,ExecutionContext&);
ExpressionResult execute_function_body(const FunctionDefinition&,ExecutionContext&);
ExpressionResult execute_math_binary_operator(const BinaryOperator&,ExecutionContext&);
ExpressionResult execute_logical_binary_operator(const BinaryOperator&,ExecutionContext&);
ExpressionResult execute_logical_unary_operator(const UnaryOperator&,ExecutionContext&);
ExpressionResult execute_math_unary_operator(const UnaryOperator&,ExecutionContext&);
ExpressionResult execute_expression(const Instruction&,ExecutionContext&);
ExpressionResult execute_logical_not(const Instruction&,ExecutionContext&);
ExpressionResult execute_minus_sign(const Instruction&,ExecutionContext&);
ExpressionResult execute_plus_sign(const Instruction&,ExecutionContext&);
ExpressionResult execute_address_operator(const Instruction&,ExecutionContext&);
ExpressionResult verselang_print_macro(const std::vector<RuntimeValue>&);
RuntimeValue default_value(const TypeSignature&);
void execute_assignment(const Assignment&, ExecutionContext&);
void define_variable(const Variable&, ExecutionContext&);
void define_constant(const Constant&, ExecutionContext&);
void initialize_print_macros();
void initialize_type_macros();