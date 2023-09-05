#include "verse.hpp"

struct StructValue;
struct ArrayValue;
struct PointerValue;
struct VoidValue;

using StringValue = std::string;
using IntegerValue = int; 
using FloatValue = double;
using CharValue = char;   
using BoolValue = bool;

using RuntimeValue = std::variant<
    IntegerValue, FloatValue, CharValue, BoolValue, VoidValue,
    StringValue, StructValue, PointerValue, ArrayValue
>; 

using ScopingData = std::vector<std::string>;

struct StructValue  { std::vector<RuntimeValue> fields; };
struct ArrayValue   { std::vector<RuntimeValue> values; };
struct PointerValue { RuntimeValue* pointer; };
struct VoidValue    { /*nothing*/ };

struct ExecutionContext {
    std::shared_ptr<FunctionDefinition> current_scope;
    std::unordered_map<std::string, TypeSignature> variable_types;
    std::unordered_map<std::string, RuntimeValue> variable_values;
    std::unordered_map<std::string, TypeSignature> constant_types;
    std::unordered_map<std::string, RuntimeValue> constant_values;
};

using ExpressionResult = std::pair<TypeSignature, RuntimeValue>;
using ArgumentValues = std::vector<RuntimeValue>;
using ArgumentTypes = std::vector<TypeSignature>;
using OverloadSet = std::vector<FunctionDefinition>;
using BinaryOperatorData = std::tuple<TypeSignature, RuntimeValue, RuntimeValue>;

using verselang_macro_procedure = std::function<
    ExpressionResult(const ArgumentTypes&, const ArgumentValues&, ExecutionContext&)>;