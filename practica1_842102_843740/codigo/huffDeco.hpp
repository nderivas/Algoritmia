/* Algoritmia básica - Práctica 1
 * Nicolás de Rivas Morillo (843740)
 * Cristina Embid Martínez (842102)
 */
#pragma once

#include "comun.hpp"
#include <fstream>

class HuffDeco {
    std::string inFile, outFile; // Archivo de entrada, salida
    NodoHuff *raiz;              // Puntero a la raíz del árbol
    bool estaVacio;

    // Funciones auxiliares
    void introducirCodigo(char byte, std::string cod);
    void leerArbol(std::ifstream &in);
    void avanzaYEscribe(NodoHuff *&nodo, const std::string pasos,
                        std::ofstream &out);
    void decodificarContenidos(std::ifstream &in, std::ofstream &out);

  public:
    // Constructor
    HuffDeco(std::string in, std::string out)
        : inFile(in), outFile(out), raiz(nullptr) {};
    // Función principal
    void decodificar();
};
