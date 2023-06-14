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

build:
	@mkdir -p build
	@rm -f build/*.o
	${COMPILER} -c -std=${STD} src/main.cpp                                 -o build/main.o
	${COMPILER} -c -std=${STD} src/commandline/commandline_utils.cpp        -o build/commandline_utils.o
	${COMPILER} -c -std=${STD} src/commandline/commandline_calls.cpp        -o build/commandline_calls.o
	${COMPILER} -c -std=${STD} src/lexing/tokenization.cpp                  -o build/tokenization.o
	${COMPILER} -c -std=${STD} src/lexing/extraction.cpp                    -o build/extraction.o
	${COMPILER} -c -std=${STD} src/parsing/parsing_definitions.cpp          -o build/parsing_definitions.o
	${COMPILER} -c -std=${STD} src/parsing/parsing_expressions.cpp          -o build/parsing_expressions.o
	${COMPILER} -c -std=${STD} src/parsing/parsing_operators.cpp            -o build/parsing_operators.o
	${COMPILER} -c -std=${STD} src/parsing/parsing_statements.cpp           -o build/parsing_statements.o
	${COMPILER} -c -std=${STD} src/parsing/parsing_utils.cpp                -o build/parsing_utils.o
	${COMPILER} -c -std=${STD} src/serialization/serialize_definitions.cpp  -o build/serialize_definitions.o
	${COMPILER} -c -std=${STD} src/serialization/serialize_expressions.cpp  -o build/serialize_expression.o
	${COMPILER} -c -std=${STD} src/serialization/serialize_statements.cpp   -o build/serialize_statements.o
	${COMPILER} -c -std=${STD} src/serialization/serialize_utils.cpp        -o build/serialize_utils.o
	${COMPILER} -c -std=${STD} src/errors/errors.cpp                        -o build/errors.o
	${LINKER} build/*.o -o verse

test:
	@${PYTHON} test/test.py