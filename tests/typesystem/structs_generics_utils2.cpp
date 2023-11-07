#include "../../include/verse.hpp"
#include "../../prototypes/procedures.hpp"
#include "../tests.hpp"

void apply_generics_to_struct_definition_test1(){
    global_structs_names_register.clear();
    global_structs_definitions.clear();   
    global_functions_definitions.clear(); 
    perform_test("src/typesystem/structs_generics_utils.cpp.cpp/apply_generics_to_struct_definition[1]",[](){
        StructDefinition Pair = {
            "Pair", {BaseType{"T"}}, {
                Instance{"first",BaseType{"T"}}, 
                Instance{"second",BaseType{"T"}}
            }, 
            nullptr
        };
        GenericsLookupTable generics_lookup_table;
        generics_lookup_table["T"] = BaseType{"Int"};
        StructDefinition instanciated = apply_generics_to_struct_definition(Pair, generics_lookup_table);
        expect(instanciated.internal_state.size() == 2);
        expect(type_to_string(instanciated.internal_state[0].typesignature) == "Int");
        expect(type_to_string(instanciated.internal_state[1].typesignature) == "Int");
    });
}

void apply_generics_to_struct_definition_test2(){
    global_structs_names_register.clear();
    global_structs_definitions.clear();   
    global_functions_definitions.clear(); 
    perform_test("src/typesystem/structs_generics_utils.cpp.cpp/apply_generics_to_struct_definition[2]",[](){
        StructDefinition Struct = {
            "Struct", {BaseType{"T"}, BaseType{"U"}}, {
                Instance{"pair", BaseType{"Pair", {BaseType{"T"}, BaseType{"U"}}}}, 
                Instance{"ptr",Pointer{ std::make_shared<TypeSignature>(BaseType{"U"})}}
            }, 
            nullptr
        };
        GenericsLookupTable generics_lookup_table;
        generics_lookup_table["T"] = BaseType{"Int"};
        generics_lookup_table["U"] = BaseType{"List", {BaseType{"String"}}};
        StructDefinition instanciated = apply_generics_to_struct_definition(Struct, generics_lookup_table);
        expect(instanciated.internal_state.size() == 2);
        expect(type_to_string(instanciated.internal_state[0].typesignature) == "Pair<Int,List<String>>");
        expect(type_to_string(instanciated.internal_state[1].typesignature) == "#List<String>");
    });
}
