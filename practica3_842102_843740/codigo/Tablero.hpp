#pragma once

#include "comun.hpp"

class Tablero {
    unsigned m_n, m_m;
    Matriz m_matriz;

  public:
    Tablero(unsigned n, unsigned m);
    inline bool dentro(int x, int y) const;
    unsigned getN() const;
    unsigned getM() const;
    Matriz &getMatriz();
};
