#pragma once

// Práctica 3 - Algoritmia básica
// Nicolás de Rivas Morillo (843740) y Cristina Embid Martínez (842102)
#include "comun.hpp"

class Tablero {
    int m_m, m_n;    // Dimensiones del tablero (filas, columnas)
    Matriz m_matriz; // Matriz que representa el tablero

  public:
    Tablero(int m, int n); // Constructor
    // Verificar si está dentro del tablero
    bool dentro(int fil, int col) const;
    unsigned getN() const; // Obtener número de columnas
    unsigned getM() const; // Obtener número de filas
    Matriz &getMatriz();   // Obtener matriz
};
