gcc = g++
flags = -std=c++11 -Wall -Wextra -o3
build = ./build
bin = ./bin
src = ./codigo

main: Yumi.o Tablero.o MeetYumi.o main.o
	$(gcc) $(flags) $(build)/Yumi.o $(build)/Tablero.o $(build)/MeetYumi.o $(build)/main.o -o $(bin)/recorridosYumi

Yumi.o: $(src)/Yumi.cpp $(src)/Yumi.hpp
	$(gcc) $(flags) -c $(src)/Yumi.cpp -o $(build)/Yumi.o

Tablero.o: $(src)/Tablero.cpp $(src)/Tablero.hpp
	$(gcc) $(flags) -c $(src)/Tablero.cpp -o $(build)/Tablero.o

MeetYumi.o: $(src)/MeetYumi.cpp $(src)/MeetYumi.hpp
	$(gcc) $(flags) -c $(src)/MeetYumi.cpp -o $(build)/MeetYumi.o

main.o: $(src)/main.cpp
	$(gcc) $(flags) -c $(src)/main.cpp -o $(build)/main.o

clean:
	rm -rf $(bin)/* $(build)/*
