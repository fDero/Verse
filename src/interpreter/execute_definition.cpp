#include "../include/verse.hpp"
#include "../include/procedures.hpp"

void execute_assignment(const Assignment& assignment, ExecutionContext& context){
    if (std::holds_alternative<Identifier>(*assignment.target)) {
        std::string identifier_name = std::get<Identifier>(*assignment.target).name;
        if (context.constant_values.find(identifier_name) != context.constant_values.end()) throw std::runtime_error { "target for assignment is a constant" };           
        if (context.variable_values.find(identifier_name) == context.variable_values.end()) throw std::runtime_error { "target for assignment does not exists" };       
        auto [type, value] = execute_expression(*assignment.value, context);
        const TypeSignature& expected_type =  context.variable_types.find(identifier_name)->second;
        if (not typesignatures_are_equal(type, expected_type)) throw std::runtime_error { "type mismatch (expected vs given) in variable assignment" };
        context.variable_values[identifier_name] = value;
        return;
    }
    throw std::runtime_error { "assignment with non-identifier destination are not yet implemented (work in progress)" };
}

void assert_variable_name_avialable(const Variable& vardef, ExecutionContext& context){
    bool name_taken = context.constant_values.find(vardef.name) != context.constant_values.end();
    name_taken |= context.variable_values.find(vardef.name) != context.variable_values.end();
    if (name_taken) {
        throw std::runtime_error{ 
            "cannot create a variable named: " + vardef.name + " because " 
            "that name is already taken"
        };
    }
}

void assert_variable_name_avialable(const Constant& constdef, ExecutionContext& context){
    bool name_taken = context.constant_values.find(constdef.name) != context.constant_values.end();
    name_taken |= context.variable_values.find(constdef.name) != context.variable_values.end();
    if (name_taken) {
        throw std::runtime_error{ 
            "cannot create a constant named: " + constdef.name + " because " 
            "that name is already taken"
        };
    }
}

RuntimeValue default_value(const TypeSignature& type){
    if (is_default_integral_type(type)){
        if (std::get<BaseType>(type).base_type == "Int")    return (IntegerValue)(0);
        if (std::get<BaseType>(type).base_type == "Float")  return (FloatValue)(0);
        if (std::get<BaseType>(type).base_type == "Char")   return (CharValue)('a');
        if (std::get<BaseType>(type).base_type == "String") return (StringValue)("");
        if (std::get<BaseType>(type).base_type == "Bool")   return (BoolValue)(false);
        throw InternalCompilerError { "somehow a non default-integral-types it's been identified as such" };
    }
    throw InternalCompilerError { "default values for non default-integral-types are not implemented yet (work in progress)" };
}

void define_variable(const Variable& vardef, ExecutionContext& context){
    assert_variable_name_avialable(vardef, context);
    context.variable_values[vardef.name] = default_value(vardef.typesignature);
    context.variable_types[vardef.name] = vardef.typesignature;
}

void define_constant(const Constant& constdef, ExecutionContext& context){
    assert_variable_name_avialable(constdef, context);
    auto [constant_type, constant_value] = execute_expression(*constdef.value, context);
    if (not typesignatures_are_equal(constant_type, constdef.typesignature)) {
        throw std::runtime_error { "type mismatch (expected vs given) in const declaration" };
    }
    context.constant_values[constdef.name] = constant_value;
    context.constant_types[constdef.name] = constant_type;
}