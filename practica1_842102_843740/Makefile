gcc = g++
flags = -std=c++11 -Wall -Wextra
build = ./build
bin = ./bin
src = ./codigo

main: enco.o deco.o comun.o main.o
	$(gcc) $(flags) $(build)/enco.o $(build)/deco.o $(build)/comun.o $(build)/main.o -o $(bin)/huff

deco.o: $(src)/huffDeco.cpp $(src)/huffDeco.hpp
	$(gcc) $(flags) -c $(src)/huffDeco.cpp -o $(build)/deco.o

enco.o: $(src)/huffEnco.cpp $(src)/huffEnco.hpp
	$(gcc) $(flags) -c $(src)/huffEnco.cpp -o $(build)/enco.o

comun.o: $(src)/comun.cpp $(src)/comun.hpp
	$(gcc) $(flags) -c $(src)/comun.cpp -o $(build)/comun.o

main.o: $(src)/main.cpp
	$(gcc) $(flags) -c $(src)/main.cpp -o $(build)/main.o

clean:
	rm -rf $(bin)/* $(build)/*
