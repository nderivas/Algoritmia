#include "Tablero.hpp"

using namespace std;

Tablero::Tablero(unsigned m, unsigned n) : m_m(m), m_n(n) {
    m_matriz.reserve(m);
    vector<Casilla> v(n);
    for (auto &c : v)
        c = {0, 0, 0, false};
    for (unsigned i = 0; i < m; ++i)
        m_matriz.push_back(v);
}

bool Tablero::dentro(int fil, int col) const {
    return fil >= 0 && fil < m_m && col >= 0 && col < m_n;
}

unsigned Tablero::getM() const { return m_m; }
unsigned Tablero::getN() const { return m_n; }
Matriz &Tablero::getMatriz() { return m_matriz; }
