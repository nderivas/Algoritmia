/* Algoritmia básica - Práctica 1
 * Nicolás de Rivas Morillo (843740)
 * Cristina Embid Martínez (842102)
 */

#pragma once

#include "comun.hpp"
#include <fstream>

class HuffEnco {
    std::string inFile, outFile; // Archivo de entrada, salida
    CountArr frecuencias; // Array que almacena la frecuencia de cada carácter
    NodoHuff *raiz;       // Puntero a la raíz del árbol
    ColaPrio cola;        // Cola de prioridad para construir el árbol
    CodArr codigos;       // Array que almacena códigos binarios
    char numCods;         // Número total de códigos

    // Funciones auziliares
    void contarFrec(std::ifstream &in);
    void rellenarCola();
    void generarTrie();
    void rellenarCodigos(NodoHuff *ptr, const std::string &cod);
    void escribirArbol(std::ofstream &out);
    void escribirString(const std::string &s, std::ofstream &out);
    void escribir(std::ifstream &in, std::ofstream &out);

  public:
    // Constructor
    HuffEnco(std::string in, std::string out)
        : inFile(in), outFile(out), raiz(nullptr), numCods(0) {
        std::fill(frecuencias.begin(), frecuencias.end(), 0);
        std::fill(codigos.begin(), codigos.end(), "");
    }
    // Función principal
    void codificar();
};
