#include "Yumi.hpp"

using namespace std;

Yumi::Yumi(unsigned n, unsigned m, array<Punto, c_CHECKPOINTS + 2> arr)
    : m_tablero(n, m), m_chPts(arr), m_x(0), m_y(0), m_sigChPt(0), m_pasos(1) {
    unsigned pasos = n * m / (c_CHECKPOINTS + 1);
    for (int i = 0; i <= c_CHECKPOINTS + 1; ++i)
        m_pasosChPt[i] = pasos * i;
}

inline unsigned Yumi::distanciaAChPt() const {
    return distancia({m_x, m_y}, m_chPts[m_sigChPt]);
}

void Yumi::recalcularGrados() {}

inline bool Yumi::hayGradoInvalido() {
    for (auto &v : m_tablero.getMatriz())
        for (auto &c : v)
            if (c.grado == 0 || c.grado == 1)
                return true;
    return false;
}

inline void Yumi::siguienteLlamada(unsigned &sol) {
    // Llamada recursiva y predicados 1 y 4
    m_pasos++;
    if (m_tablero.dentro(m_x + 1, m_y) &&
        !m_tablero.getMatriz()[m_x + 1][m_y].visitado) {
        m_x++;
        recResolver(sol);
        m_x--;
    }
    if (m_tablero.dentro(m_x, m_y - 1) &&
        !m_tablero.getMatriz()[m_x][m_y - 1].visitado) {
        m_y--;
        recResolver(sol);
        m_y++;
    }
    if (m_tablero.dentro(m_x - 1, m_y) &&
        !m_tablero.getMatriz()[m_x - 1][m_y].visitado) {
        m_x--;
        recResolver(sol);
        m_x++;
    }
    if (m_tablero.dentro(m_x, m_y + 1) &&
        !m_tablero.getMatriz()[m_x][m_y + 1].visitado) {
        m_y++;
        recResolver(sol);
        m_y--;
    }
}

void Yumi::recResolver(unsigned &sol) {
    // Predicados acotadores
    // --- Comprobación de llegada a tiempo al checkpoint (Pred 2, 5 y 7)
    if (distanciaAChPt() > m_pasosChPt[m_sigChPt] - m_pasos)
        return;
    recalcularGrados();
    if (hayGradoInvalido())
        return;
    // Caso base y predicado 3
    if (m_x == m_chPts[c_CHECKPOINTS + 1].first &&
        m_y == m_chPts[c_CHECKPOINTS + 1].second) {
        sol++;
        return;
    }
    // Llamada recursiva
    siguienteLlamada(sol);
}

// Wrapper de la llamada recursiva
unsigned Yumi::resolver() {
    // Comprobaciones
    // --- Checkpoints dentro del tablero
    for (auto &p : m_chPts)
        if (!m_tablero.dentro(p.first, p.second))
            return 0;
    // Llego de un checkpoint a otro
    for (int i = 0; i <= c_CHECKPOINTS; ++i)
        if (distancia(m_chPts[i], m_chPts[i + 1]) > m_pasosChPt[i + 1])
            return 0;
    // Llamada recursiva
    unsigned soluciones = 0;
    recResolver(soluciones);
}

void Yumi::escribirInforme(std::ofstream &salida) const {}
