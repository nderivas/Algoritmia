gcc = g++
flags = -std=c++11
build = ./build
bin = ./bin
src = ./codigo

main: comun.o main.o
	$(gcc) $(flags) -o huff $(build)/comun.o $(build)/main.o

comun.o: $(src)/comun.cpp $(src)/comun.hpp
	$(gcc) $(flags) -c $(src)/comun.cpp -o $(build)/comun.o

main.o: $(src)/main.cpp
	$(gcc) $(flags) -c $(src)/main.cpp -o $(build)/main.o
