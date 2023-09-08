#include "../../src/include/verse.hpp"
#include "../../src/include/procedures.hpp"
#include "../tests.hpp"

void retrieve_struct_definition_test1(){
    global_structs_names_register.clear();
    global_structs_definitions.clear();   
    global_functions_definitions.clear(); 
    perform_test("src/scoping/structs_retrieval.cpp/retrieve_struct_definition[1]",[](){
        StructDefinition Outer { "Outer", {BaseType{"T"}}, {}, nullptr };
        StructDefinition Inner { "Inner", {}, {}, std::make_shared<StructDefinition>(Outer) };
        
        global_structs_names_register["Outer"].push_back("Outer<\\w+>");
        global_structs_definitions["Outer<\\w+>"] = Outer;

        global_structs_names_register["Inner"].push_back("Outer<\\w+>.Inner");
        global_structs_definitions["Outer<\\w+>.Inner"] = Inner;
        
        TypeSignature outer = BaseType{ "Outer", {BaseType{"Int"}} };
        TypeSignature inner = BaseType{ "Inner", {} };
        TypeSignature type = NestedType{ std::make_shared<TypeSignature>(outer), std::make_shared<TypeSignature>(inner) };
        StructDefinition retrieved = retrieve_struct_definition(type);
        expect(retrieved.struct_name == "Inner");
        expect(retrieved.parent_scope->struct_name == "Outer");
        expect(retrieved.generics.empty());
    });
}

void retrieve_struct_definition_test2(){
    global_structs_names_register.clear();
    global_structs_definitions.clear();   
    global_functions_definitions.clear(); 
    perform_test("src/scoping/structs_retrieval.cpp/retrieve_struct_definition[2]",[](){
        StructDefinition Outer { "Outer", {BaseType{"T"}}, {}, nullptr };
        StructDefinition Inner { "Inner", {}, {}, std::make_shared<StructDefinition>(Outer) };
        
        global_structs_names_register["Outer"].push_back("Outer<\\w+>");
        global_structs_definitions["Outer<\\w+>"] = Outer;

        global_structs_names_register["Inner"].push_back("Outer<\\w+>.Inner");
        global_structs_definitions["Outer<\\w+>.Inner"] = Inner;
        
        global_structs_definitions[get_qualified_struct_name(Inner)] = Inner;
        TypeSignature type = BaseType{ "Outer", {BaseType{"Int"}} };
        StructDefinition retrieved = retrieve_struct_definition(type);
        expect(retrieved.struct_name == "Outer");
        expect(retrieved.parent_scope == nullptr);
        expect(retrieved.generics.size() == 1);
    });
}

void retrieve_struct_definition_test3(){
    global_structs_names_register.clear();
    global_structs_definitions.clear();   
    global_functions_definitions.clear(); 
    perform_test("src/scoping/structs_retrieval.cpp/retrieve_struct_definition[3]",[](){
        StructDefinition List_of_T { "List", {BaseType{"T"}}, {}, nullptr };
        StructDefinition List_of_Int { "List<Int>", {}, {}, nullptr };
        StructDefinition List_of_String { "List<String>", {}, {}, nullptr };
        
        global_structs_names_register["List"].push_back("List<\\w+>");
        global_structs_definitions["List<\\w+>"] = List_of_T;
        
        global_structs_names_register["List"].push_back("List<Int>");
        global_structs_definitions["List<Int>"] = List_of_Int;
        
        global_structs_names_register["List"].push_back("List<String>");
        global_structs_definitions["List<String>"] = List_of_String;

        TypeSignature list_of_Int = BaseType{ "List", {BaseType{"Int"}} };
        TypeSignature list_of_Float = BaseType{ "List", {BaseType{"Float"}} };
        
        StructDefinition retrieved_int = retrieve_struct_definition(list_of_Int);
        StructDefinition retrieved_float = retrieve_struct_definition(list_of_Float);
                
        expect(retrieved_int.struct_name == "List<Int>");
        expect(retrieved_int.generics.empty());
        expect(retrieved_float.struct_name == "List");
        expect(retrieved_float.generics.size() == 1);
        
    });
}