#include "Tablero.hpp"

using namespace std;

Tablero::Tablero(unsigned n, unsigned m) : m_n(n), m_m(m) {
    m_matriz.reserve(n);
    vector<Casilla> v(m);
    for (auto &c : v)
        c = {0, 0, 0, false};
    for (unsigned i = 0; i < n; ++i)
        m_matriz.push_back(v);
}

inline bool Tablero::dentro(int x, int y) const {
    return x >= 0 && x < m_m && y >= 0 && y < m_n;
}

unsigned Tablero::getM() const { return m_m; }
unsigned Tablero::getN() const { return m_n; }
Matriz &Tablero::getMatriz() { return m_matriz; }
