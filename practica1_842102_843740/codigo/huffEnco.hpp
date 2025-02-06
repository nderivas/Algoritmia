/* Algoritmia básica - Práctica 1
 * Nicolás de Rivas Morillo (843740)
 * Cristina Embid Martínez (842102)
 */

#pragma once

#include "comun.hpp"
#include <fstream>
#include <utility>

// Comparador para la cola de prioridades.
struct CompararPares {
    bool operator()(const std::pair<char, unsigned> uno,
                    const std::pair<char, unsigned> dos) {
        return uno.second > dos.second;
    }
};

class HuffEnco {
    std::string inFile, outFile; // Archivo de entrada, salida
    CountArr frecuencias; // Array que almacena la frecuencia de cada carácter
    NodoHuff *raiz;       // Puntero a la raíz del árbol
    ColaFrec colaFrecuencias; // Cola de prioridad para construir el árbol
    ColaLong colaLongitudes;  // Cola de prioridad para construir el árbol
    CodArr codigos;           // Array que almacena códigos binarios
    char numCods;             // Número total de códigos
    unsigned char L;          // Parámetro L

    // Funciones auziliares
    void contarFrec(std::ifstream &in);
    void ajustarFrecuencias();
    void generarTrieLongitudes();
    void rellenarCola();
    void generarTrieFrecuencias();
    void rellenarCodigos(NodoHuff *ptr, const std::string &cod);
    void escribirArbol(std::ofstream &out);
    void escribirString(const std::string &s, std::ofstream &out);
    void escribir(std::ifstream &in, std::ofstream &out);

  public:
    // Constructor
    HuffEnco(std::string in, std::string out, unsigned char l = 0)
        : inFile(in), outFile(out), raiz(nullptr), numCods(0), L(l) {
        std::fill(frecuencias.begin(), frecuencias.end(), 0);
        std::fill(codigos.begin(), codigos.end(), "");
    }
    // Función principal
    void codificar();
};
