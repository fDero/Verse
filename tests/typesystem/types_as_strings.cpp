#include "../../src/include/verse.hpp"
#include "../../src/include/procedures.hpp"
#include "../tests.hpp"

void type_to_string_test1(){
    perform_test("src/typesystem/structs_generics_utils.cpp/type_to_string[1]",[](){
        TypeSignature A = BaseType { "A", {BaseType{"S"}, BaseType{"U"}} };
        TypeSignature B = BaseType { "B", {BaseType{"K"}} };
        TypeSignature C = BaseType { "C", {} };
        NestedType BdotC = NestedType { std::make_shared<TypeSignature>(B), std::make_shared<TypeSignature>(C) };
        NestedType AdotBdotC = NestedType { std::make_shared<TypeSignature>(A), std::make_shared<TypeSignature>(BdotC) };    
        expect(type_to_string(BdotC) == "B<K>.C");
        expect(type_to_string(AdotBdotC) == "A<S,U>.B<K>.C");
    });
}


void type_to_string_test2(){
    perform_test("src/typesystem/structs_generics_utils.cpp/type_to_string[2]",[](){
        TypeSignature A = BaseType { "A", {} };
        TypeSignature B = BaseType { "B", {} };
        TypeSignature C = BaseType { "C", {} };
        NestedType BdotC = NestedType { std::make_shared<TypeSignature>(B), std::make_shared<TypeSignature>(C) };
        NestedType AdotBdotC = NestedType { std::make_shared<TypeSignature>(A), std::make_shared<TypeSignature>(BdotC) };    
        expect(type_to_string(BdotC) == "B.C");
        expect(type_to_string(AdotBdotC) == "A.B.C");
    });
}


void type_to_string_test3(){
    perform_test("src/typesystem/structs_generics_utils.cpp/type_to_string[3]",[](){
        TypeSignature Int = BaseType { "Int" };
        TypeSignature Intptr = Pointer { std::make_shared<TypeSignature>(BaseType{"Int"}) };
        TypeSignature A = BaseType { "A", {BaseType{"S"}, BaseType{"U"}} };
        TypeSignature Aptr =  Pointer { std::make_shared<TypeSignature>(A) };
        expect(type_to_string(Int) == "Int");
        expect(type_to_string(Intptr) == "#Int");
        expect(type_to_string(A) == "A<S,U>");
        expect(type_to_string(Aptr) == "#A<S,U>");
    });
}


void type_to_string_test4(){
    perform_test("src/typesystem/structs_generics_utils.cpp/type_to_string[4]",[](){
        TypeSignature Int = BaseType { "Int" };
        TypeSignature Intptr = Pointer { std::make_shared<TypeSignature>(Int) };
        TypeSignature Intptrptr = Pointer { std::make_shared<TypeSignature>(Intptr) };
        expect(type_to_string(Int) == "Int");
        expect(type_to_string(Intptr) == "#Int");
        expect(type_to_string(Intptrptr) == "##Int");
    });
}

void type_to_string_without_generics_test1(){
    perform_test("src/typesystem/structs_generics_utils.cpp/type_to_string_without_generics[1]",[](){
        TypeSignature A = BaseType { "A", {BaseType{"S"}, BaseType{"U"}} };
        TypeSignature B = BaseType { "B", {BaseType{"K"}} };
        TypeSignature C = BaseType { "C", {} };
        NestedType BdotC = NestedType { std::make_shared<TypeSignature>(B), std::make_shared<TypeSignature>(C) };
        NestedType AdotBdotC = NestedType { std::make_shared<TypeSignature>(A), std::make_shared<TypeSignature>(BdotC) };    
        expect(type_to_string_without_generics(BdotC) == "B.C");
        expect(type_to_string_without_generics(AdotBdotC) == "A.B.C");
    });
}

void type_to_string_without_generics_test2(){
    perform_test("src/typesystem/structs_generics_utils.cpp/type_to_string_without_generics[2]",[](){
        TypeSignature A = BaseType { "A", {} };
        TypeSignature B = BaseType { "B", {} };
        TypeSignature C = BaseType { "C", {} };
        NestedType BdotC = NestedType { std::make_shared<TypeSignature>(B), std::make_shared<TypeSignature>(C) };
        NestedType AdotBdotC = NestedType { std::make_shared<TypeSignature>(A), std::make_shared<TypeSignature>(BdotC) };    
        expect(type_to_string_without_generics(BdotC) == "B.C");
        expect(type_to_string_without_generics(AdotBdotC) == "A.B.C");
    });
}


void type_to_string_without_generics_test3(){
    perform_test("src/typesystem/structs_generics_utils.cpp/type_to_string_without_generics[3]",[](){
        TypeSignature Int = BaseType { "Int" };
        TypeSignature Intptr = Pointer { std::make_shared<TypeSignature>(BaseType{"Int"}) };
        TypeSignature A = BaseType { "A", {BaseType{"S"}, BaseType{"U"}} };
        TypeSignature Aptr =  Pointer { std::make_shared<TypeSignature>(A) };
        expect(type_to_string_without_generics(Int) == "Int");
        expect(type_to_string_without_generics(Intptr) == "#Int");
        expect(type_to_string_without_generics(A) == "A");
        expect(type_to_string_without_generics(Aptr) == "#A");
    });
}


void type_to_string_without_generics_test4(){
    perform_test("src/typesystem/structs_generics_utils.cpp/type_to_string_without_generics[4]",[](){
        TypeSignature Int = BaseType { "Int" };
        TypeSignature Intptr = Pointer { std::make_shared<TypeSignature>(Int) };
        TypeSignature Intptrptr = Pointer { std::make_shared<TypeSignature>(Intptr) };
        expect(type_to_string_without_generics(Int) == "Int");
        expect(type_to_string_without_generics(Intptr) == "#Int");
        expect(type_to_string_without_generics(Intptrptr) == "##Int");
    });
}

void most_derived_type_test1(){
    perform_test("src/typesystem/structs_generics_utils.cpp/most_derived_type[1]",[](){
        TypeSignature A = BaseType { "A", {BaseType{"S"}, BaseType{"U"}} };
        TypeSignature B = BaseType { "B", {BaseType{"K"}} };
        TypeSignature C = BaseType { "C", {} };
        NestedType BdotC = NestedType { std::make_shared<TypeSignature>(B), std::make_shared<TypeSignature>(C) };
        NestedType AdotBdotC = NestedType { std::make_shared<TypeSignature>(A), std::make_shared<TypeSignature>(BdotC) };    
        expect(most_derived_type(A) == "A");
        expect(most_derived_type(BdotC) == "C");
        expect(most_derived_type(AdotBdotC) == "C");
    });
}

void most_derived_type_test2(){
    perform_test("src/typesystem/structs_generics_utils.cpp/most_derived_type[2]",[](){
        TypeSignature Int = BaseType { "Int" };
        TypeSignature Intptr = Pointer { std::make_shared<TypeSignature>(Int) };
        TypeSignature Intptrptr = Pointer { std::make_shared<TypeSignature>(Intptr) };
        expect(most_derived_type(Int) == "Int");
        expect(most_derived_type(Intptr) == "Int");
        expect(most_derived_type(Intptrptr) == "Int");
    });
}

void get_qualified_struct_name_test1(){
    perform_test("src/typesystem/structs_generics_utils.cpp/get_qualified_struct_name[1]",[](){
        StructDefinition A { "A", {BaseType{"T1"}}, {}, nullptr };
        StructDefinition B { "B", {BaseType{"T2"}, BaseType{"T3"}}, {}, std::make_shared<StructDefinition>(A) };
        StructDefinition C { "C", {}, {}, std::make_shared<StructDefinition>(B) };
        expect(get_qualified_struct_name(C) == "A<\\w+>.B<\\w+,\\w+>.C");
    });
}

void get_qualified_struct_name_test2(){
    perform_test("src/typesystem/structs_generics_utils.cpp/get_qualified_struct_name[2]",[](){
        StructDefinition A { "A", {BaseType{"T1"}, BaseType{"T2"}}, {}, nullptr };
        StructDefinition B { "B", {BaseType{"T3"}}, {}, std::make_shared<StructDefinition>(A) };
        StructDefinition C { "C", {}, {}, std::make_shared<StructDefinition>(B) };
        expect(get_qualified_struct_name(C) == "A<\\w+,\\w+>.B<\\w+>.C");
    });
}

void get_qualified_struct_name_test3(){
    perform_test("src/typesystem/structs_generics_utils.cpp/get_qualified_struct_name[3]",[](){
        StructDefinition A { "A", {BaseType{"T1"}}, {}, nullptr };
        StructDefinition B { "B", {BaseType{"T2"}}, {}, std::make_shared<StructDefinition>(A) };
        StructDefinition C { "C", {BaseType{"T3"}}, {}, std::make_shared<StructDefinition>(B) };
        expect(get_qualified_struct_name(C) == "A<\\w+>.B<\\w+>.C<\\w+>");
    });
}


void get_qualified_struct_name_test4(){
    perform_test("src/typesystem/structs_generics_utils.cpp/get_qualified_struct_name[4]",[](){
        StructDefinition A { "A", {}, {}, nullptr };
        StructDefinition B { "B", {}, {}, std::make_shared<StructDefinition>(A) };
        StructDefinition C { "C", {}, {}, std::make_shared<StructDefinition>(B) };
        expect(get_qualified_struct_name(C) == "A.B.C");
    });
}