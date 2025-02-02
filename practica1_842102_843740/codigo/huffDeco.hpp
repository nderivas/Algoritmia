/* Algoritmia básica - Práctica 1
 * Nicolás de Rivas Morillo (843740)
 * Cristina Embid Martínez (842102)
 */
#pragma once

#include "comun.hpp"
#include <fstream>

class HuffDeco {
    std::string inFile, outFile; // Archivo de entrada, salida
    NodoHuff *raiz;       // Puntero a la raíz del árbol

    void introducirCodigo(char byte, std::string cod);
    void leerArbol(std::ifstream& in);
    void decodificarContenidos(std::ifstream& in, std::ofstream& out);

  public:
    HuffDeco(std::string in, std::string out) : inFile(in), outFile(out), raiz(nullptr) {};
    void decodificar();
};
