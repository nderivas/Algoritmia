// Práctica 3 - Algoritmia básica
// Nicolás de Rivas Morillo (843740) y Cristina Embid Martínez (842102)
#include "Tablero.hpp"

using namespace std;

// Constructor de la clase Tablero
Tablero::Tablero(unsigned m, unsigned n) : m_m(m), m_n(n) {
    m_matriz.reserve(m); // Reserva espacio para m filas
    vector<Casilla> v(n);
    for (auto &c : v) // Inicializa cada casilla
        c = {0, 0, 0, false, false};
    for (unsigned i = 0; i < m; ++i)
        m_matriz.push_back(v);
}

// Verificar si una casilla está dentro del Tablero
// @param fil indice que indica la fila
// @param col indice que indica la columna
// @return true si (fil, col) está dentro de los límites del tablero, false en
// caso contrario.
bool Tablero::dentro(unsigned fil, unsigned col) const {
    return fil >= 0 && fil < m_m && col >= 0 && col < m_n;
}

// Obtener número de filas del tablero
unsigned Tablero::getM() const { return m_m; }
// Obtener número de columnas del tablero
unsigned Tablero::getN() const { return m_n; }
// Obtener la matriz del tablero
Matriz &Tablero::getMatriz() { return m_matriz; }
