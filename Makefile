.PHONY: test build
COMPILER=g++
STD=c++17
LINKER=g++

build:
	mkdir -p build
	${COMPILER} -c -std=${STD} code/main.cpp                         -o build/main.o
	${COMPILER} -c -std=${STD} code/lexing/tokenization.cpp          -o build/tokenization.o
	${COMPILER} -c -std=${STD} code/parsing/parsing_definitions.cpp  -o build/parsing_definitions.o
	${COMPILER} -c -std=${STD} code/parsing/parsing_expressions.cpp  -o build/parsing_expressions.o
	${COMPILER} -c -std=${STD} code/parsing/parsing_operators.cpp    -o build/parsing_operators.o
	${COMPILER} -c -std=${STD} code/parsing/parsing_statements.cpp   -o build/parsing_statements.o
	${COMPILER} -c -std=${STD} code/parsing/parsing_utils.cpp        -o build/parsing_utils.o
	${COMPILER} -c -std=${STD} code/serialization/serialize_xml.cpp  -o build/serialize_xml.o
	${COMPILER} -c -std=${STD} code/serialization/serialize_json.cpp -o build/serialize_json.o
	${LINKER} build/*.o -o verse

run:
	./verse -c test/main.verse -o test/res.xml test/res.json
 