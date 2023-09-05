.PHONY: test build clean

COMPILER=clang++
STD=c++20
LINKER=clang++
PYTHON=python3

clean:
	@rm -f build/*.o
	@rm -f test/snippets/*/*.xml
	@rm -f test/snippets/*/*.json
	@rm -rf .vscode
	@rm -rf build
	@rm -f verse
	@rm -f *.verse
	@rm -f *.xml
	@rm -f *.json

build:
	@mkdir -p build
	@rm -f build/*.o
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
	${COMPILER} -c -std=${STD} src/preprocessing/definitions_table.cpp         -o build/definitions_table.o
	${COMPILER} -c -std=${STD} src/preprocessing/entry_point.cpp               -o build/entry_point.o

	${COMPILER} -c -std=${STD} src/main.cpp                                    -o build/main.o
	${COMPILER} -c -std=${STD} src/commandline/commandline_utils.cpp           -o build/commandline_utils.o
	${COMPILER} -c -std=${STD} src/commandline/commandline_calls.cpp           -o build/commandline_calls.o
	${COMPILER} -c -std=${STD} src/lexing/tokenization.cpp                     -o build/tokenization.o
	${COMPILER} -c -std=${STD} src/lexing/extraction.cpp                       -o build/extraction.o
	${COMPILER} -c -std=${STD} src/parsing/parsing_definitions.cpp             -o build/parsing_definitions.o
	${COMPILER} -c -std=${STD} src/parsing/parsing_expressions.cpp             -o build/parsing_expressions.o
	${COMPILER} -c -std=${STD} src/parsing/parsing_operators.cpp               -o build/parsing_operators.o
	${COMPILER} -c -std=${STD} src/parsing/parsing_statements.cpp              -o build/parsing_statements.o
	${COMPILER} -c -std=${STD} src/parsing/parsing_utils.cpp                   -o build/parsing_utils.o
	${COMPILER} -c -std=${STD} src/serialization/serialize_definitions.cpp     -o build/serialize_definitions.o
	${COMPILER} -c -std=${STD} src/serialization/serialize_expressions.cpp     -o build/serialize_expression.o
	${COMPILER} -c -std=${STD} src/serialization/serialize_statements.cpp      -o build/serialize_statements.o
	${COMPILER} -c -std=${STD} src/serialization/serialize_utils.cpp           -o build/serialize_utils.o
	${COMPILER} -c -std=${STD} src/errors/display_errors.cpp                   -o build/display_errors.o
	${LINKER} build/*.o -o verse
test:
	@${PYTHON} test/test.py