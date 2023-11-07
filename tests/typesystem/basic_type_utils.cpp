#include "../../include/verse.hpp"
#include "../../prototypes/procedures.hpp"
#include "../tests.hpp"

void compare_base_types_test1(){
    perform_test("src/typesystem/basic_type_util.cpp/compare_base_types[1]",[](){
        TypeSignature A = BaseType { "A", {BaseType{"S"}, BaseType{"U"}} };
        TypeSignature B = BaseType { "B", {BaseType{"K"}} };
        TypeSignature C = BaseType { "C", {} };
        NestedType BdotC = NestedType { std::make_shared<TypeSignature>(B), std::make_shared<TypeSignature>(C) };
        NestedType AdotBdotC = NestedType { std::make_shared<TypeSignature>(A), std::make_shared<TypeSignature>(BdotC) };    
        TypeSignature AA = BaseType { "AA", {BaseType{"S"}, BaseType{"U"}} };
        TypeSignature BB = BaseType { "BB", {BaseType{"K"}} };
        TypeSignature CC = BaseType { "CC", {} };
        NestedType BBdotCC = NestedType { std::make_shared<TypeSignature>(BB), std::make_shared<TypeSignature>(CC) };
        NestedType AAdotBBdotCC = NestedType { std::make_shared<TypeSignature>(AA), std::make_shared<TypeSignature>(BBdotCC) }; 
        expect(not typesignatures_are_equal(AAdotBBdotCC, AdotBdotC));
    });
}

void compare_base_types_test2(){
    perform_test("src/typesystem/basic_type_util.cpp/compare_base_types[2]",[](){
        TypeSignature A = BaseType { "A", {BaseType{"S"}, BaseType{"U"}} };
        TypeSignature B = BaseType { "B", {BaseType{"K"}} };
        TypeSignature C = BaseType { "C", {} };
        NestedType BdotC = NestedType { std::make_shared<TypeSignature>(B), std::make_shared<TypeSignature>(C) };
        NestedType AdotBdotC = NestedType { std::make_shared<TypeSignature>(A), std::make_shared<TypeSignature>(BdotC) };    
        TypeSignature AA = BaseType { "A", {BaseType{"M"}, BaseType{"U"}} };
        TypeSignature BB = BaseType { "B", {BaseType{"K"}} };
        TypeSignature CC = BaseType { "C", {} };
        NestedType BBdotCC = NestedType { std::make_shared<TypeSignature>(BB), std::make_shared<TypeSignature>(CC) };
        NestedType AAdotBBdotCC = NestedType { std::make_shared<TypeSignature>(AA), std::make_shared<TypeSignature>(BBdotCC) }; 
        expect(not typesignatures_are_equal(AAdotBBdotCC, AdotBdotC));
    });
}


void compare_base_types_test3(){
    perform_test("src/typesystem/basic_type_util.cpp/compare_base_types[3]",[](){
        TypeSignature A = BaseType { "A", {BaseType{"S"}, BaseType{"U"}} };
        TypeSignature B = BaseType { "B", {BaseType{"K"}} };
        TypeSignature C = BaseType { "C", {} };
        NestedType BdotC = NestedType { std::make_shared<TypeSignature>(B), std::make_shared<TypeSignature>(C) };
        NestedType AdotBdotC = NestedType { std::make_shared<TypeSignature>(A), std::make_shared<TypeSignature>(BdotC) };    
        TypeSignature AA = BaseType { "A", {BaseType{"S"}, BaseType{"U"}} };
        TypeSignature BB = BaseType { "B", {BaseType{"M"}} };
        TypeSignature CC = BaseType { "C", {} };
        NestedType BBdotCC = NestedType { std::make_shared<TypeSignature>(BB), std::make_shared<TypeSignature>(CC) };
        NestedType AAdotBBdotCC = NestedType { std::make_shared<TypeSignature>(AA), std::make_shared<TypeSignature>(BBdotCC) }; 
        expect(not typesignatures_are_equal(AAdotBBdotCC, AdotBdotC));
    });
}


void compare_base_types_test4(){
    perform_test("src/typesystem/basic_type_util.cpp/compare_base_types[4]",[](){
        TypeSignature A = BaseType { "A", {BaseType{"S"}, BaseType{"U"}} };
        TypeSignature B = BaseType { "B", {BaseType{"K"}} };
        TypeSignature C = BaseType { "C", {} };
        NestedType BdotC = NestedType { std::make_shared<TypeSignature>(B), std::make_shared<TypeSignature>(C) };
        NestedType AdotBdotC = NestedType { std::make_shared<TypeSignature>(A), std::make_shared<TypeSignature>(BdotC) };    
        TypeSignature AA = BaseType { "A", {BaseType{"S"}, BaseType{"U"}} };
        TypeSignature BB = BaseType { "B", {BaseType{"K"}} };
        TypeSignature CC = BaseType { "C", {} };
        NestedType BBdotCC = NestedType { std::make_shared<TypeSignature>(BB), std::make_shared<TypeSignature>(CC) };
        NestedType AAdotBBdotCC = NestedType { std::make_shared<TypeSignature>(AA), std::make_shared<TypeSignature>(BBdotCC) }; 
        expect(typesignatures_are_equal(AAdotBBdotCC, AdotBdotC));
    });
}

void compare_base_types_test5(){
    perform_test("src/typesystem/basic_type_util.cpp/compare_base_types[5]",[](){
        TypeSignature A = BaseType { "A", {BaseType{"S"}, BaseType{"U"}} };
        TypeSignature B = BaseType { "B", {BaseType{"K"}} };
        TypeSignature C = BaseType { "C", {} };
        NestedType BdotC = NestedType { std::make_shared<TypeSignature>(B), std::make_shared<TypeSignature>(C) };
        NestedType AdotBdotC = NestedType { std::make_shared<TypeSignature>(A), std::make_shared<TypeSignature>(BdotC) };    
        TypeSignature BB = BaseType { "B", {BaseType{"K"}} };
        TypeSignature CC = BaseType { "C", {} };
        NestedType BBdotCC = NestedType { std::make_shared<TypeSignature>(BB), std::make_shared<TypeSignature>(CC) };
        expect(not typesignatures_are_equal(BBdotCC, AdotBdotC));
    });
}

void compare_base_types_test6(){
    perform_test("src/typesystem/basic_type_util.cpp/compare_base_types[6]",[](){
        TypeSignature Aptr1 = Pointer { std::make_shared<TypeSignature>(BaseType{"A"}) };
        TypeSignature Aptr2 = Pointer { std::make_shared<TypeSignature>(BaseType{"A"}) };
        expect(typesignatures_are_equal(Aptr1, Aptr2));
    });
}


void compare_base_types_test7(){
    perform_test("src/typesystem/basic_type_util.cpp/compare_base_types[7]",[](){
        TypeSignature Aptr1 = Pointer { std::make_shared<TypeSignature>(BaseType{"A", {BaseType{"T"}}}) };
        TypeSignature Aptr2 = Pointer { std::make_shared<TypeSignature>(BaseType{"A"}) };
        expect(not typesignatures_are_equal(Aptr1, Aptr2));
    });
}


void compare_base_types_test8(){
    perform_test("src/typesystem/basic_type_util.cpp/compare_base_types[8]",[](){
        TypeSignature Aptr1 = Pointer { std::make_shared<TypeSignature>(BaseType{"A", {BaseType{"T"}}}) };
        TypeSignature Aptr2 = Pointer { std::make_shared<TypeSignature>(BaseType{"A", {BaseType{"T"}}}) };
        expect(typesignatures_are_equal(Aptr1, Aptr2));
    });
}


void compare_base_types_test9(){
    perform_test("src/typesystem/basic_type_util.cpp/compare_base_types[9]",[](){
        TypeSignature Aptr1 = Pointer { std::make_shared<TypeSignature>(BaseType{"A", {BaseType{"T"}}}) };
        TypeSignature Aptr2 = Pointer { std::make_shared<TypeSignature>(BaseType{"A", {BaseType{"K"}}}) };
        expect(not typesignatures_are_equal(Aptr1, Aptr2));
    });
}

void is_default_integral_type_test1(){
    perform_test("src/typesystem/basic_type_util.cpp/is_default_integral_type[1]",[](){
        TypeSignature A = BaseType { "A", {BaseType{"S"}, BaseType{"U"}} };
        TypeSignature B = BaseType { "B", {BaseType{"K"}} };
        TypeSignature C = BaseType { "C", {} };
        NestedType BdotC = NestedType { std::make_shared<TypeSignature>(B), std::make_shared<TypeSignature>(C) };
        NestedType AdotBdotC = NestedType { std::make_shared<TypeSignature>(A), std::make_shared<TypeSignature>(BdotC) };
        TypeSignature Aptr1 = Pointer { std::make_shared<TypeSignature>(BaseType{"A", {BaseType{"T"}}}) };
        TypeSignature Aptr2 = Pointer { std::make_shared<TypeSignature>(BaseType{"A"}) };
        TypeSignature Intptr = Pointer { std::make_shared<TypeSignature>(BaseType{"Int"}) };
        expect(not is_default_integral_type(A));
        expect(not is_default_integral_type(B));
        expect(not is_default_integral_type(C));
        expect(not is_default_integral_type(BdotC));
        expect(not is_default_integral_type(AdotBdotC));
        expect(not is_default_integral_type(Aptr1));
        expect(not is_default_integral_type(Aptr2));
        expect(not is_default_integral_type(Intptr));
    });
}

void is_default_integral_type_test2(){
    perform_test("src/typesystem/basic_type_util.cpp/is_default_integral_type[2]",[](){       
        expect(is_default_integral_type(BaseType{"Int"}));
        expect(is_default_integral_type(BaseType{"Float"}));
        expect(is_default_integral_type(BaseType{"Char"}));
        expect(is_default_integral_type(BaseType{"String"}));
        expect(is_default_integral_type(BaseType{"Bool"}));
    });
}