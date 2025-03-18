#pragma once

// Práctica 3 - Algoritmia básica
// Nicolás de Rivas Morillo (843740) y Cristina Embid Martínez (842102)
#include "comun.hpp"

class Tablero {
    unsigned m_m, m_n; // Dimensiones del tablero (filas, columnas)
    Matriz m_matriz;   // Matriz que representa el tablero

  public:
    Tablero(unsigned m, unsigned n); // Constructor
    bool dentro(unsigned fil,
                unsigned col) const; // Verificar si está dentro del tablero
    unsigned getN() const;           // Obtener número de columnas
    unsigned getM() const;           // Obtener número de filas
    Matriz &getMatriz();             // Obtener matriz
};
