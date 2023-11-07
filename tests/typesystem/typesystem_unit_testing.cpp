#include "../../include/verse.hpp"
#include "../../prototypes/procedures.hpp"
#include "../tests.hpp"

int main(){

    //testing procedures from: src/typesystem/basic_type_utils.cpp
    void compare_base_types_test1();               compare_base_types_test1();
    void compare_base_types_test2();               compare_base_types_test2();
    void compare_base_types_test3();               compare_base_types_test3();
    void compare_base_types_test4();               compare_base_types_test4();  
    void compare_base_types_test5();               compare_base_types_test5();
    void compare_base_types_test6();               compare_base_types_test6();
    void compare_base_types_test7();               compare_base_types_test7();
    void compare_base_types_test8();               compare_base_types_test8();  
    void compare_base_types_test9();               compare_base_types_test9();  
    void is_default_integral_type_test1();         is_default_integral_type_test1();
    void is_default_integral_type_test2();         is_default_integral_type_test2();

    //testing procedures from: src/typesystem/types_as_strings.cpp
    void type_to_string_test1();                   type_to_string_test1();
    void type_to_string_test2();                   type_to_string_test2();
    void type_to_string_test3();                   type_to_string_test3();
    void type_to_string_test4();                   type_to_string_test4();
    void type_to_string_without_generics_test1();  type_to_string_without_generics_test1();
    void type_to_string_without_generics_test2();  type_to_string_without_generics_test2();
    void type_to_string_without_generics_test3();  type_to_string_without_generics_test3();
    void type_to_string_without_generics_test4();  type_to_string_without_generics_test4();
    void most_derived_type_test1();                most_derived_type_test1();
    void most_derived_type_test2();                most_derived_type_test2();
    void get_qualified_struct_name_test1();        get_qualified_struct_name_test1();
    void get_qualified_struct_name_test2();        get_qualified_struct_name_test2();
    void get_qualified_struct_name_test3();        get_qualified_struct_name_test3();
    void get_qualified_struct_name_test4();        get_qualified_struct_name_test4();

    //testing procedures from: src/typesystem/structs_generics_utils.cpp
    void get_instanciated_generics_test1();        get_instanciated_generics_test1();
    void get_instanciated_generics_test2();        get_instanciated_generics_test2();
    void get_instanciated_generics_test3();        get_instanciated_generics_test3();
    void get_instanciated_generics_test4();        get_instanciated_generics_test4();
    void get_instanciated_generics_test5();        get_instanciated_generics_test5();
    void get_template_generics_test1();            get_template_generics_test1();
    void get_template_generics_test2();            get_template_generics_test2();
    void get_template_generics_test3();            get_template_generics_test3();
    void get_template_generics_test4();            get_template_generics_test4();
    void get_template_generics_test5();            get_template_generics_test5();
    void get_generics_lookup_table_test1();        get_generics_lookup_table_test1();
    void get_generics_lookup_table_test2();        get_generics_lookup_table_test2();
    void get_generics_lookup_table_test3();        get_generics_lookup_table_test3();

    //testing procedures from: src/generics/apply_generics_to_typesignature.cpp
    void apply_generics_to_typesignature_test1();      apply_generics_to_typesignature_test1();
    void apply_generics_to_typesignature_test2();      apply_generics_to_typesignature_test2();
    void apply_generics_to_typesignature_test3();      apply_generics_to_typesignature_test3();
    void apply_generics_to_typesignature_test4();      apply_generics_to_typesignature_test4();
    void apply_generics_to_typesignature_test5();      apply_generics_to_typesignature_test5();
    void apply_generics_to_typesignature_test6();      apply_generics_to_typesignature_test6();

    //testing procedures from: src/generics/apply_generics_to_struct_definition.cpp
    void apply_generics_to_struct_definition_test1(); apply_generics_to_struct_definition_test1();
    void apply_generics_to_struct_definition_test2(); apply_generics_to_struct_definition_test2();
   
    show_test_recap();
}