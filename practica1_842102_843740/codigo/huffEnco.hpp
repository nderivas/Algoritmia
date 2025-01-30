#pragma once

#include "comun.hpp"
#include <fstream>

class HuffEnco {
  protected:
    std::string inFile, outFile;
    CountArr frecuencias;
    NodoHuff *raiz;
    ColaPrio cola;
    CodArr codigos;
    char numCods;

    void contarFrec(std::ifstream &in);
    void rellenarCola();
    void generarTrie();
    void rellenarCodigos(NodoHuff *ptr, const std::string &cod);
    void escribirArbol(std::ofstream &out);
    void escribirString(const std::string &s, std::ofstream &out);
    void escribir(std::ifstream &in, std::ofstream &out);

  public:
    HuffEnco(std::string in, std::string out)
        : inFile(in), outFile(out), raiz(nullptr), numCods(0) {
        std::fill(frecuencias.cbegin(), frecuencias.cend(), 0);
        std::fill(codigos.cbegin(), codigos.cend(), "");
    }
    void codificar();
};
