gcc = g++
flags = -std=c++11 -Wall -Wextra
build = ./build
bin = ./bin
src = ./codigo

temp:
	$(gcc) $(flags) $(src)/Yumi.cpp $(src)/Tablero.cpp $(src)/main.cpp -o $(bin)/recorridosYumi

main: Yumi.o Tablero.o main.o
	$(gcc) $(flags) $(build)/Yumi.o $(build)/Tablero.o $(build)/main.o -o $(bin)/recorridosYumi

Yumi.o: $(src)/Yumi.cpp $(src)/Yumi.hpp
	$(gcc) $(flags) -c $(src)/Yumi.cpp -o $(build)/Yumi.o

Tablero.o: $(src)/Tablero.cpp $(src)/Tablero.hpp
	$(gcc) $(flags) -c $(src)/Tablero.cpp -o $(build)/Tablero.o

main.o: $(src)/main.cpp
	$(gcc) $(flags) -c $(src)/main.cpp -o $(build)/main.o

clean:
	rm -rf $(bin)/* $(build)/*
