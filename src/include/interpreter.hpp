#include "verse.hpp"

struct DefinitionsTable {
    std::unordered_map<std::string, std::vector<FunctionDefinition>> functions;
    std::unordered_map<std::string, std::vector<StructDefinition>> structs;
};

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
    ScopingData current_scope;
    std::unordered_map<std::string, TypeSignature> variable_types;
    std::unordered_map<std::string, RuntimeValue> variable_values;
    std::unordered_map<std::string, TypeSignature> constant_types;
    std::unordered_map<std::string, RuntimeValue> constant_values;
};

using ExpressionResult = std::pair<TypeSignature, RuntimeValue>;
using ArgumentValues = std::vector<RuntimeValue>;
using ArgumentTypes = std::vector<TypeSignature>;

using verselang_macro_procedure = std::function<ExpressionResult(const ArgumentValues&, ExecutionContext&)>;