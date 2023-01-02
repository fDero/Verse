.PHONY: test build update
COMPILER=g++
STD=c++17
LINKER=g++

build:
	@mkdir -p build
	@rm -f build/*.o
	${COMPILER} -c -std=${STD} code/main.cpp                                 -o build/main.o
	${COMPILER} -c -std=${STD} code/commandline/commandline_utils.cpp        -o build/commandline_utils.o
	${COMPILER} -c -std=${STD} code/commandline/commandline_calls.cpp        -o build/commandline_calls.o
	${COMPILER} -c -std=${STD} code/lexing/tokenization.cpp                  -o build/tokenization.o
	${COMPILER} -c -std=${STD} code/lexing/extraction.cpp                    -o build/extraction.o
	${COMPILER} -c -std=${STD} code/parsing/parsing_definitions.cpp          -o build/parsing_definitions.o
	${COMPILER} -c -std=${STD} code/parsing/parsing_expressions.cpp          -o build/parsing_expressions.o
	${COMPILER} -c -std=${STD} code/parsing/parsing_operators.cpp            -o build/parsing_operators.o
	${COMPILER} -c -std=${STD} code/parsing/parsing_statements.cpp           -o build/parsing_statements.o
	${COMPILER} -c -std=${STD} code/parsing/parsing_utils.cpp                -o build/parsing_utils.o
	${COMPILER} -c -std=${STD} code/serialization/serialize_definitions.cpp  -o build/serialize_definitions.o
	${COMPILER} -c -std=${STD} code/serialization/serialize_expressions.cpp  -o build/serialize_expression.o
	${COMPILER} -c -std=${STD} code/serialization/serialize_statements.cpp   -o build/serialize_statements.o
	${COMPILER} -c -std=${STD} code/serialization/serialize_utils.cpp        -o build/serialize_utils.o
	${LINKER} build/*.o -o verse

test:
	./verse -c test/main.verse -o test/res.xml test/res.json
	@echo "\n --------------------------------------------------------------- \n"
	@echo ">> automated tests are not implemented yet\n"
	@echo ">> the way i currently test is by manually checking files generated in the test folder\n"
	@echo ">> in the future i will provide a python script that runs verse on many code snippets"
	@echo "-- and ensures they're compiled / interpreted correctly\n"

commit:
	git add code
	git add test
	git add TODO.md
	git add Makefile
	git commit -m "commit"
	git push -f