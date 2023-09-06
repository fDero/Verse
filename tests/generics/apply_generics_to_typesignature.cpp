#include "../../src/include/verse.hpp"
#include "../../src/include/procedures.hpp"
#include "../tests.hpp"

void apply_generics_to_typesignature_test1(){
    perform_test("src/scoping/apply_generics_to_typesignature.cpp/apply_generics_to_typesignature[1]",[](){
        TypeSignature T = BaseType{"T"};
        GenericsLookupTable generics_lookup_table;
        generics_lookup_table["T"] = BaseType{"List", {BaseType{"Int"}}};
        TypeSignature instanciated_T = apply_generics_to_typesignature(T, generics_lookup_table); 
        expect(type_to_string(instanciated_T) == "List<Int>");
    });
}

void apply_generics_to_typesignature_test2(){
    perform_test("src/scoping/apply_generics_to_typesignature.cpp/apply_generics_to_typesignature[2]",[](){
        TypeSignature T = BaseType{"Pair", {BaseType{"T"}, BaseType{"U"}}};
        GenericsLookupTable generics_lookup_table;
        generics_lookup_table["T"] = BaseType{"Int"};
        generics_lookup_table["U"] = BaseType{"List", {BaseType{"Int"}}};
        TypeSignature instanciated_T = apply_generics_to_typesignature(T, generics_lookup_table); 
        expect(type_to_string(instanciated_T) == "Pair<Int,List<Int>>");
    });
}

void apply_generics_to_typesignature_test3(){
    perform_test("src/scoping/apply_generics_to_typesignature.cpp/apply_generics_to_typesignature[3]",[](){
        TypeSignature T = BaseType{"Pair", {BaseType{"T"}, BaseType{"U"}}};
        TypeSignature Tptr = Pointer { std::make_shared<TypeSignature>(T) };
        GenericsLookupTable generics_lookup_table;
        generics_lookup_table["T"] = BaseType{"Int"};
        generics_lookup_table["U"] = BaseType{"List", {BaseType{"Int"}}};
        TypeSignature instanciated_Tptr = apply_generics_to_typesignature(Tptr, generics_lookup_table); 
        expect(type_to_string(instanciated_Tptr) == "#Pair<Int,List<Int>>");
    });
}

void apply_generics_to_typesignature_test4(){
    perform_test("src/scoping/apply_generics_to_typesignature.cpp/apply_generics_to_typesignature[4]",[](){
        TypeSignature T = BaseType{"Pair", {BaseType{"T"}, BaseType{"U"}}};
        TypeSignature Tptr = Pointer { std::make_shared<TypeSignature>(T) };
        GenericsLookupTable generics_lookup_table;
        generics_lookup_table["T"] = Pointer { std::make_shared<TypeSignature>(BaseType{"Int"}) };
        generics_lookup_table["U"] = BaseType{"List", {BaseType{"Int"}}};
        TypeSignature instanciated_Tptr = apply_generics_to_typesignature(Tptr, generics_lookup_table); 
        expect(type_to_string(instanciated_Tptr) == "#Pair<#Int,List<Int>>");
    });
}

void apply_generics_to_typesignature_test5(){
    perform_test("src/scoping/apply_generics_to_typesignature.cpp/apply_generics_to_typesignature[5]",[](){
        TypeSignature HashMap_of_T = BaseType{"HashMap", {BaseType{"T"}, BaseType{"T"}}};
        TypeSignature HashMapEntry = BaseType{"HashMapEntry"};
        TypeSignature HashMap_of_T_dot_HashMapEntry = NestedType { 
            std::make_shared<TypeSignature>(HashMap_of_T), 
            std::make_shared<TypeSignature>(HashMapEntry) 
        };
        GenericsLookupTable generics_lookup_table;
        generics_lookup_table["T"] = BaseType{"Int"};
        TypeSignature instanciated_HashMap_of_T_dot_HashMapEntry = apply_generics_to_typesignature(
            HashMap_of_T_dot_HashMapEntry, 
            generics_lookup_table
        ); 
        expect(type_to_string(instanciated_HashMap_of_T_dot_HashMapEntry) == "HashMap<Int,Int>.HashMapEntry");
    });
}


void apply_generics_to_typesignature_test6(){
    perform_test("src/scoping/apply_generics_to_typesignature.cpp/apply_generics_to_typesignature[6]",[](){
        TypeSignature A = BaseType{"A", {BaseType{"T"}}};
        TypeSignature B = BaseType{"B", {BaseType{"U"}}};
        TypeSignature C = BaseType{"C", {BaseType{"T"}}};
        TypeSignature D = BaseType{"D", {BaseType{"S"}}};
        TypeSignature CdotD = NestedType {std::make_shared<TypeSignature>(C), std::make_shared<TypeSignature>(D) };
        TypeSignature BdotCdotD = NestedType {std::make_shared<TypeSignature>(B), std::make_shared<TypeSignature>(CdotD) };
        TypeSignature AdotBdotCdotD = NestedType {std::make_shared<TypeSignature>(A), std::make_shared<TypeSignature>(BdotCdotD) };
        GenericsLookupTable generics_lookup_table;
        generics_lookup_table["T"] = BaseType{"Int"};
        generics_lookup_table["U"] = BaseType{"List", {BaseType{"Float"}}};
        generics_lookup_table["S"] = BaseType{"String"};
        TypeSignature instanciated = apply_generics_to_typesignature(AdotBdotCdotD, generics_lookup_table); 
        expect(type_to_string(instanciated) == "A<Int>.B<List<Float>>.C<Int>.D<String>");
    });
}