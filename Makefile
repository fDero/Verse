build:
	g++ -std=c++17 -o verse code/main.cpp code/compilation/*.cpp code/interpreter/*.cpp code/parsing/*.cpp code/tokenization/*.cpp

run:
	./verse -c test/main.verse -o test/res.xml test/res.json
	cat test/res.xml
 
clean:
	rm verse

complete:
	make build
	make run
