.PHONY: test build clean

COMPILER=clang++
STD=c++20
LINKER=clang++

MKDIR := mkdir -p
RM := rm -rf
EXECUTABLE_EXTENSION := out
TARGET := verse

clean:
	@$(RM) build
	@$(RM) test/snippets/*/*.xml
	@$(RM) test/snippets/*/*.json
	@$(RM) .vscode
	@$(RM) .idea
	@$(RM) verse
	@$(RM) *.verse
	@$(RM) *.xml
	@$(RM) *.json
	@$(RM) *.out

build:
	@$(RM) build
	@$(MKDIR) build
	
	
	${COMPILER} -c -std=${STD} src/typesystem/generic_type_utils.cpp           -o build/generic_type_utils.o
	${COMPILER} -c -std=${STD} src/typesystem/structs_generics_utils.cpp       -o build/structs_generics_utils.o
	${COMPILER} -c -std=${STD} src/verselang_macros/print_macros.cpp           -o build/print_macros.o
	${COMPILER} -c -std=${STD} src/verselang_macros/type_macros.cpp            -o build/type_macros.o
	${COMPILER} -c -std=${STD} src/interpreter/execute_function.cpp            -o build/execute_function.o
	${COMPILER} -c -std=${STD} src/interpreter/execute_expression.cpp          -o build/execute_expression.o
	${COMPILER} -c -std=${STD} src/interpreter/execute_definition.cpp          -o build/execute_definition.o
	${COMPILER} -c -std=${STD} src/interpreter/execute_math_operators.cpp      -o build/execute_math_operators.o
	${COMPILER} -c -std=${STD} src/interpreter/execute_logical_operators.cpp   -o build/execute_logical_operators.o
	${COMPILER} -c -std=${STD} src/interpreter/execute_statement.cpp           -o build/execute_statement.o
	${COMPILER} -c -std=${STD} src/interpreter/pointers_arithmetic.cpp         -o build/pointers_arithmetic.o
	${COMPILER} -c -std=${STD} src/scoping/functions_retrieval.cpp             -o build/functions_retrieval.o
	${COMPILER} -c -std=${STD} src/scoping/structs_retrieval.cpp               -o build/structs_retrieval.o
	${COMPILER} -c -std=${STD} src/scoping/struct_members.cpp                  -o build/struct_members.o
	${COMPILER} -c -std=${STD} src/typesystem/basic_type_utils.cpp             -o build/basic_type_utils.o
	${COMPILER} -c -std=${STD} src/typesystem/types_as_strings.cpp             -o build/types_as_strings.o
	${COMPILER} -c -std=${STD} src/typesystem/structs_generics_utils.cpp       -o build/structs_generics_utils.o
	${COMPILER} -c -std=${STD} src/preprocessing/definitions_table.cpp         -o build/definitions_table.o
	${COMPILER} -c -std=${STD} src/preprocessing/entry_point.cpp               -o build/entry_point.o
	${COMPILER} -c -std=${STD} src/preprocessing/structs_fields_correction.cpp -o build/structs_fields_correction.o

	${COMPILER} -c -std=${STD} src/main.cpp                                    -o build/main.o
	${COMPILER} -c -std=${STD} src/commandline/commandline_utils.cpp           -o build/commandline_utils.o
	${COMPILER} -c -std=${STD} src/commandline/commandline_calls.cpp           -o build/commandline_calls.o
	${COMPILER} -c -std=${STD} src/lexing/tokenization.cpp                     -o build/tokenization.o
	${COMPILER} -c -std=${STD} src/lexing/extraction.cpp                       -o build/extraction.o
	${COMPILER} -c -std=${STD} src/parsing/parsing_definitions.cpp             -o build/parsing_definitions.o
	${COMPILER} -c -std=${STD} src/parsing/parsing_expressions.cpp             -o build/parsing_expressions.o
	${COMPILER} -c -std=${STD} src/parsing/parsing_operators.cpp               -o build/parsing_operators.o
	${COMPILER} -c -std=${STD} src/parsing/parsing_statements.cpp              -o build/parsing_statements.o
	${COMPILER} -c -std=${STD} src/parsing/acquire_instructions.cpp            -o build/acquire_instructions.o
	${COMPILER} -c -std=${STD} src/parsing/acquire_sections.cpp                -o build/acquire_sections.o
	${COMPILER} -c -std=${STD} src/parsing/acquire_terminals.cpp               -o build/acquire_terminals.o
	${COMPILER} -c -std=${STD} src/parsing/acquire_typesignatures.cpp          -o build/acquire_typesignatures.o
	${COMPILER} -c -std=${STD} src/serialization/serialize_definitions.cpp     -o build/serialize_definitions.o
	${COMPILER} -c -std=${STD} src/serialization/serialize_expressions.cpp     -o build/serialize_expression.o
	${COMPILER} -c -std=${STD} src/serialization/serialize_statements.cpp      -o build/serialize_statements.o
	${COMPILER} -c -std=${STD} src/serialization/serialize_utils.cpp           -o build/serialize_utils.o
	${COMPILER} -c -std=${STD} src/errors/display_errors.cpp                   -o build/display_errors.o
	${LINKER} build/*.o -o ${TARGET}

typesystem_unit_testing:
	@${COMPILER} -std=${STD} tests/typesystem/*.cpp src/typesystem/*.cpp src/scoping/*.cpp -o tests/typesystem/typesystem_unit_testing.out
	@tests/typesystem/typesystem_unit_testing.${EXECUTABLE_EXTENSION}
	@$(RM) tests/typesystem/typesystem_unit_testing.out
	@$(RM) tests/typesystem/typesystem_unit_testing.exe

scoping_unit_testing:
	@${COMPILER} -std=${STD} tests/scoping/*.cpp src/scoping/*.cpp src/typesystem/*.cpp -o tests/scoping/scoping_unit_testing.out
	@tests/scoping/scoping_unit_testing.${EXECUTABLE_EXTENSION}
	@$(RM) tests/scoping/scoping_unit_testing.out
	@$(RM) tests/scoping/scoping_unit_testing.exe