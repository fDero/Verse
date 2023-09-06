#include "../../src/include/verse.hpp"
#include "../../src/include/procedures.hpp"
#include "../tests.hpp"


int main(){

    //testing procedure: src/scoping/retrieve_struct_definition_from_function_body
    void retrieve_struct_definition_from_function_body_test1();    retrieve_struct_definition_from_function_body_test1();
    void retrieve_struct_definition_from_function_body_test2();    retrieve_struct_definition_from_function_body_test2();
    void retrieve_struct_definition_from_function_body_test3();    retrieve_struct_definition_from_function_body_test3();

    //testing procedure: src/scoping/retrieve_struct_definition_from_struct_scope
    void retrieve_struct_definition_from_struct_scope_test1();     retrieve_struct_definition_from_struct_scope_test1();
    void retrieve_struct_definition_from_struct_scope_test2();     retrieve_struct_definition_from_struct_scope_test2();
    void retrieve_struct_definition_from_struct_scope_test3();     retrieve_struct_definition_from_struct_scope_test3();
   
    show_test_recap();
}