#include "Yumi.hpp"

using namespace std;

inline unsigned distancia(Punto a, Punto b) {
    return abs(a.first - b.first) + abs(a.second - b.second);
}

inline void Yumi::calcularGrado(Matriz &t, int i, int j) {
    for (int off = -1; off <= 1; off = off + 2) {
        if (m_tablero.dentro(i + off, j) && !t[i + off][j].visitado) {
            if (i + off == c_INI.first && j == c_INI.second)
                t[i][j].entradas++;
            else if (i + off == c_FIN.first && j == c_FIN.second)
                t[i][j].salidas++;
            else
                t[i][j].dobles++;
        }
        if (m_tablero.dentro(i, j + off) && !t[i][j + off].visitado) {
            if (i == c_INI.first && j + off == c_INI.second)
                t[i][j].entradas++;
            else if (i == c_FIN.first && j + off == c_FIN.second)
                t[i][j].salidas++;
            else
                t[i][j].dobles++;
        }
    }
}

void Yumi::calcularGradosIniciales() {
    auto &t = m_tablero.getMatriz();
    t[0][0].salidas = 2;
    t[0][1].entradas = 3;
    for (unsigned i = 0; i < m_tablero.getN(); ++i)
        for (unsigned j = 2; i < m_tablero.getM(); ++j)
            if (m_tablero.dentro(i, j))
                calcularGrado(t, i, j);
}

Yumi::Yumi(unsigned n, unsigned m, array<Punto, c_CHECKPOINTS + 1> arr)
    : m_chPts(arr), m_sigChPt(0), m_pasos(1), m_x(0), m_y(0), m_tablero(n, m) {
    for (unsigned i = 1; i <= c_CHECKPOINTS + 1; ++i)
        m_pasosChPt[i - 1] = (n * m * i) / (c_CHECKPOINTS + 1);
    calcularGradosIniciales();
}

inline unsigned Yumi::distanciaAChPt() const {
    return distancia({m_x, m_y}, m_chPts[m_sigChPt]);
}

void Yumi::recalcularGrados() { calcularGradosIniciales(); }

inline bool Yumi::casillaConGradoInvalido(Casilla &c) {
    bool hayEntradas = c.entradas > 0 || c.dobles > 0;
    bool haySalidas = c.salidas > 0 || c.dobles > 0;
    bool caso1 = hayEntradas && haySalidas && c.dobles != 1;
    bool caso2 = c.dobles >= 2;
    return !caso1 && !caso2;
}

bool Yumi::hayGradoInvalido() {
    for (auto &v : m_tablero.getMatriz())
        for (auto &c : v)
            if (casillaConGradoInvalido(c))
                return true;
    return false;
}

inline bool Yumi::inChPt() const {
    for (const Punto &p : m_chPts)
        if (p.first == m_x && p.second == m_y)
            return true;
    return false;
}

inline void Yumi::siguienteLlamada(unsigned &sol) {
    // Llamada recursiva y predicados 1 y 4
    m_tablero.getMatriz()[m_x][m_y].visitado = true;
    m_pasos++;
    if (m_tablero.dentro(m_x - 1, m_y) &&
        !m_tablero.getMatriz()[m_x - 1][m_y].visitado) {
        m_x--;
        if (inChPt())
            m_sigChPt++;
        recResolver(sol);
        m_x++;
    }
    if (m_tablero.dentro(m_x, m_y + 1) &&
        !m_tablero.getMatriz()[m_x][m_y + 1].visitado) {
        m_y++;
        if (inChPt())
            m_sigChPt++;
        recResolver(sol);
        m_y--;
    }
    if (m_tablero.dentro(m_x, m_y - 1) &&
        !m_tablero.getMatriz()[m_x][m_y - 1].visitado) {
        m_y--;
        if (inChPt())
            m_sigChPt++;
        recResolver(sol);
        m_y++;
    }
    if (m_tablero.dentro(m_x + 1, m_y) &&
        !m_tablero.getMatriz()[m_x + 1][m_y].visitado) {
        m_x++;
        if (inChPt())
            m_sigChPt++;
        recResolver(sol);
        m_x--;
    }
    m_tablero.getMatriz()[m_x][m_y].visitado = false;
}

void Yumi::recResolver(unsigned &sol) {
    // Predicados acotadores
    // --- Comporbación de llegada temprana (Pred 2)
    for (unsigned i = m_sigChPt + 1; i < m_chPts.size(); ++i)
        if (m_x == m_chPts[i].first && m_y == m_chPts[i].second)
            return;
    // --- Comprobación de llegada a tiempo al checkpoint (Pred 5 y 7)
    if (distanciaAChPt() != m_pasosChPt[m_sigChPt] - m_pasos)
        return;
    recalcularGrados();
    if (hayGradoInvalido())
        return;
    // Caso base y predicado 3
    if (m_x == c_FIN.first && m_y == c_FIN.second) {
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
    for (unsigned i = 0; i < c_CHECKPOINTS - 1; ++i)
        if (distancia(m_chPts[i], m_chPts[i + 1]) > m_pasosChPt[i])
            return 0;
    // Llamada recursiva
    unsigned soluciones = 0;
    recResolver(soluciones);
    return soluciones;
}
