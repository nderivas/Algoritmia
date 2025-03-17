#pragma once

#include "comun.hpp"

class Tablero {
    unsigned m_n, m_m;
    Matriz m_matriz;

  public:
    Tablero(unsigned n, unsigned m);
    bool dentro(int fil, int col) const;
    unsigned getN() const;
    unsigned getM() const;
    Matriz &getMatriz();
};
