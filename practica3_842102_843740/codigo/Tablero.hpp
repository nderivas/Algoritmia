#pragma once

#include "comun.hpp"

class Tablero {
    unsigned m_m, m_n;
    Matriz m_matriz;

  public:
    Tablero(unsigned m, unsigned n);
    bool dentro(int fil, int col) const;
    unsigned getN() const;
    unsigned getM() const;
    Matriz &getMatriz();
};
