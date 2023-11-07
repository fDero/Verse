#include "../../include/verse.hpp"
#include "../../prototypes/procedures.hpp"
#include "../tests.hpp"

void get_instanciated_generics_test1(){
    perform_test("src/typesystem/structs_generics_utils.cpp/get_instanciated_generics[1]",[](){
        TypeSignature A = BaseType { "A", {BaseType{"S"}, BaseType{"U"}} };
        TypeSignature B = BaseType { "B", {BaseType{"K"}} };
        TypeSignature C = BaseType { "C", {} };
        NestedType BdotC = NestedType { std::make_shared<TypeSignature>(B), std::make_shared<TypeSignature>(C) };
        NestedType AdotBdotC = NestedType { std::make_shared<TypeSignature>(A), std::make_shared<TypeSignature>(BdotC) };    
        InstanciatedGenerics instaciated_generics = get_instanciated_generics(AdotBdotC);
        expect(instaciated_generics.size() == 3);
        expect(instaciated_generics.front().size() == 0);
        expect(instaciated_generics.back().size() == 2);
    });
}

void get_instanciated_generics_test2(){
    perform_test("src/typesystem/structs_generics_utils.cpp/get_instanciated_generics[2]",[](){
        TypeSignature A = BaseType { "A", {BaseType{"S"}} };
        TypeSignature B = BaseType { "B", {BaseType{"K"}} };
        TypeSignature C = BaseType { "C", {BaseType{"T"}} };
        NestedType BdotC = NestedType { std::make_shared<TypeSignature>(B), std::make_shared<TypeSignature>(C) };
        NestedType AdotBdotC = NestedType { std::make_shared<TypeSignature>(A), std::make_shared<TypeSignature>(BdotC) };    
        InstanciatedGenerics instaciated_generics = get_instanciated_generics(AdotBdotC);
        expect(instaciated_generics.size() == 3);
        expect(instaciated_generics.front().size() == 1);
        expect(instaciated_generics.back().size() == 1);
    });
}

void get_instanciated_generics_test3(){
    perform_test("src/typesystem/structs_generics_utils.cpp/get_instanciated_generics[3]",[](){
        TypeSignature A = BaseType { "A" };
        TypeSignature B = BaseType { "B" };
        TypeSignature C = BaseType { "C" };
        NestedType BdotC = NestedType { std::make_shared<TypeSignature>(B), std::make_shared<TypeSignature>(C) };
        NestedType AdotBdotC = NestedType { std::make_shared<TypeSignature>(A), std::make_shared<TypeSignature>(BdotC) };    
        InstanciatedGenerics instaciated_generics = get_instanciated_generics(AdotBdotC);
        expect(instaciated_generics.size() == 3);
        expect(instaciated_generics.front().size() == 0);
        expect(instaciated_generics.back().size() == 0);
    });
}

void get_instanciated_generics_test4(){
    perform_test("src/typesystem/structs_generics_utils.cpp/get_instanciated_generics[4]",[](){
        TypeSignature A = BaseType { "A" };    
        InstanciatedGenerics instaciated_generics = get_instanciated_generics(A);
        expect(instaciated_generics.size() == 1);
        expect(instaciated_generics.back().size() == 0);
    });
}


void get_instanciated_generics_test5(){
    perform_test("src/typesystem/structs_generics_utils.cpp/get_instanciated_generics[5]",[](){
        TypeSignature A = BaseType { "A", {BaseType{"T"}} };    
        InstanciatedGenerics instaciated_generics = get_instanciated_generics(A);
        expect(instaciated_generics.size() == 1);
        expect(instaciated_generics.back().size() == 1);
    });
}

void get_template_generics_test1(){
    perform_test("src/typesystem/structs_generics_utils.cpp/get_template_generics[1]",[](){
        StructDefinition A { "A", {BaseType{"T1"}, BaseType{"T2"}}, {}, nullptr };
        StructDefinition B { "B", {BaseType{"T3"}}, {}, std::make_shared<StructDefinition>(A) };
        StructDefinition C { "C", {}, {}, std::make_shared<StructDefinition>(B) };
        TemplateGenerics template_generics = get_template_generics(C);
        auto it = template_generics.begin();
        expect(template_generics.size() == 3);
        expect(it->size() == 0); ++it;
        expect(it->size() == 1); ++it;
        expect(it->size() == 2); ++it;
    });
}

void get_template_generics_test2(){
    perform_test("src/typesystem/structs_generics_utils.cpp/get_template_generics[2]",[](){
        StructDefinition A { "A", {BaseType{"T1"}}, {}, nullptr };
        StructDefinition B { "B", {BaseType{"T2"}, BaseType{"T3"}}, {}, std::make_shared<StructDefinition>(A) };
        StructDefinition C { "C", {}, {}, std::make_shared<StructDefinition>(B) };
        TemplateGenerics template_generics = get_template_generics(C);
        auto it = template_generics.begin();
        expect(template_generics.size() == 3);
        expect(it->size() == 0); ++it;
        expect(it->size() == 2); ++it;
        expect(it->size() == 1); ++it;
    });
}

void get_template_generics_test3(){
    perform_test("src/typesystem/structs_generics_utils.cpp/get_template_generics[3]",[](){
        StructDefinition A { "A", {}, {}, nullptr };
        StructDefinition B { "B", {}, {}, std::make_shared<StructDefinition>(A) };
        StructDefinition C { "C", {}, {}, std::make_shared<StructDefinition>(B) };
        TemplateGenerics template_generics = get_template_generics(C);
        auto it = template_generics.begin();
        expect(template_generics.size() == 3);
        expect(it->size() == 0); ++it;
        expect(it->size() == 0); ++it;
        expect(it->size() == 0); ++it;
    });
}

void get_template_generics_test4(){
    perform_test("src/typesystem/structs_generics_utils.cpp/get_template_generics[4]",[](){
        StructDefinition A { "A", {}, {}, nullptr };
        TemplateGenerics template_generics = get_template_generics(A);
        auto it = template_generics.begin();
        expect(template_generics.size() == 1);
        expect(it->size() == 0); ++it;
    });
}

void get_template_generics_test5(){
    perform_test("src/typesystem/structs_generics_utils.cpp/get_template_generics[5]",[](){
        StructDefinition A { "A", {BaseType{"T"}, BaseType{"U"}}, {}, nullptr };
        TemplateGenerics template_generics = get_template_generics(A);
        auto it = template_generics.begin();
        expect(template_generics.size() == 1);
        expect(it->size() == 2); ++it;
    });
}

void get_generics_lookup_table_test1(){
    perform_test("src/typesystem/structs_generics_utils.cpp/get_generics_lookup_table[1]",[](){
        TypeSignature A = BaseType { "A", {BaseType{"S"}, BaseType{"U"}} };
        TypeSignature B = BaseType { "B", {BaseType{"K"}} };
        TypeSignature C = BaseType { "C", {} };
        NestedType BdotC = NestedType { std::make_shared<TypeSignature>(B), std::make_shared<TypeSignature>(C) };
        NestedType AdotBdotC = NestedType { std::make_shared<TypeSignature>(A), std::make_shared<TypeSignature>(BdotC) };    
        InstanciatedGenerics instaciated_generics = get_instanciated_generics(AdotBdotC);
        StructDefinition Adef { "A", {BaseType{"T1"}, BaseType{"T2"}}, {}, nullptr };
        StructDefinition Bdef { "B", {BaseType{"T3"}}, {}, std::make_shared<StructDefinition>(Adef) };
        StructDefinition Cdef { "C", {}, {}, std::make_shared<StructDefinition>(Bdef) };
        TemplateGenerics template_generics = get_template_generics(Cdef);
        GenericsLookupTable generics_lookup_table = get_generics_lookup_table(template_generics, instaciated_generics);
        expect(generics_lookup_table.size() == 3);
        expect(typesignatures_are_equal(generics_lookup_table["T1"], BaseType{"S"}));
        expect(typesignatures_are_equal(generics_lookup_table["T2"], BaseType{"U"}));
        expect(typesignatures_are_equal(generics_lookup_table["T3"], BaseType{"K"}));
    });
}


void get_generics_lookup_table_test2(){
    perform_test("src/typesystem/structs_generics_utils.cpp/get_generics_lookup_table[2]",[](){
        TypeSignature A = BaseType { "A", {BaseType{"S"}} };
        TypeSignature B = BaseType { "B", {BaseType{"K"}} };
        TypeSignature C = BaseType { "C", {BaseType{"U"}} };
        NestedType BdotC = NestedType { std::make_shared<TypeSignature>(B), std::make_shared<TypeSignature>(C) };
        NestedType AdotBdotC = NestedType { std::make_shared<TypeSignature>(A), std::make_shared<TypeSignature>(BdotC) };    
        InstanciatedGenerics instaciated_generics = get_instanciated_generics(AdotBdotC);
        StructDefinition Adef { "A", {BaseType{"T1"}}, {}, nullptr };
        StructDefinition Bdef { "B", {BaseType{"T2"}}, {}, std::make_shared<StructDefinition>(Adef) };
        StructDefinition Cdef { "C", {BaseType{"T3"}}, {}, std::make_shared<StructDefinition>(Bdef) };
        TemplateGenerics template_generics = get_template_generics(Cdef);
        GenericsLookupTable generics_lookup_table = get_generics_lookup_table(template_generics, instaciated_generics);
        expect(generics_lookup_table.size() == 3);
        expect(typesignatures_are_equal(generics_lookup_table["T1"], BaseType{"S"}));
        expect(typesignatures_are_equal(generics_lookup_table["T2"], BaseType{"K"}));
        expect(typesignatures_are_equal(generics_lookup_table["T3"], BaseType{"U"}));
    });
}

void get_generics_lookup_table_test3(){
    perform_test("src/typesystem/structs_generics_utils.cpp/get_generics_lookup_table[3]",[](){
        TypeSignature A = BaseType { "A", {} };
        TypeSignature B = BaseType { "B", {} };
        TypeSignature C = BaseType { "C", {} };
        NestedType BdotC = NestedType { std::make_shared<TypeSignature>(B), std::make_shared<TypeSignature>(C) };
        NestedType AdotBdotC = NestedType { std::make_shared<TypeSignature>(A), std::make_shared<TypeSignature>(BdotC) };    
        InstanciatedGenerics instaciated_generics = get_instanciated_generics(AdotBdotC);
        StructDefinition Adef { "A", {}, {}, nullptr };
        StructDefinition Bdef { "B", {}, {}, std::make_shared<StructDefinition>(Adef) };
        StructDefinition Cdef { "C", {}, {}, std::make_shared<StructDefinition>(Bdef) };
        TemplateGenerics template_generics = get_template_generics(Cdef);
        GenericsLookupTable generics_lookup_table = get_generics_lookup_table(template_generics, instaciated_generics);
        expect(generics_lookup_table.size() == 0);
    });
}