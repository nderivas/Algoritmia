gcc = g++
flags = -std=c++11 -Wall -Wextra -o3
#-o3
build = ./build
bin = ./bin
src = ./codigo

main: minimizador.o nodo.o tren.o main.o
	$(gcc) $(flags) $(build)/minimizador.o $(build)/nodo.o $(build)/tren.o $(build)/main.o -o $(bin)/transporte

minimizador.o: $(src)/minimizador.cpp $(src)/minimizador.hpp
	$(gcc) $(flags) -c $(src)/minimizador.cpp -o $(build)/minimizador.o

nodo.o: $(src)/nodo.cpp $(src)/nodo.hpp
	$(gcc) $(flags) -c $(src)/nodo.cpp -o $(build)/nodo.o

tren.o: $(src)/tren.cpp $(src)/tren.hpp
	$(gcc) $(flags) -c $(src)/tren.cpp -o $(build)/tren.o

main.o: $(src)/main.cpp
	$(gcc) $(flags) -c $(src)/main.cpp -o $(build)/main.o

clean:
	rm -rf $(bin)/* $(build)/*
