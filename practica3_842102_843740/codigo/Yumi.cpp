#include "Yumi.hpp"
#include <cmath>
#include <iostream>

using namespace std;

inline unsigned distancia(Punto a, Punto b) {
    return abs(a.first - b.first) + abs(a.second - b.second);
}

inline void Yumi::calcularGrado(Matriz &t, int i, int j) {
    t[i][j].entradas = 0;
    t[i][j].salidas = 0;
    t[i][j].dobles = 0;
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
    for (unsigned i = 0; i < m_tablero.getM(); ++i)
        for (unsigned j = i == 0 ? 2 : 0; j < m_tablero.getN(); ++j)
            calcularGrado(t, i, j);
}

Yumi::Yumi(unsigned n, unsigned m, array<Punto, c_CHECKPOINTS + 1> arr)
    : m_chPts(arr), m_sigChPt(0), m_pasos(1), m_fil(0), m_col(0),
      m_tablero(n, m) {
    for (unsigned i = 1; i <= c_CHECKPOINTS + 1; ++i)
        m_pasosChPt[i - 1] = (n * m * i) / (c_CHECKPOINTS + 1);
    calcularGradosIniciales();
}

inline unsigned Yumi::distanciaAChPt() const {
    return distancia({m_fil, m_col}, m_chPts[m_sigChPt]);
}

void Yumi::recalcularGrados() { calcularGradosIniciales(); }

inline bool Yumi::casillaConGradoInvalido(const int i, const int j) {
    Casilla &c = m_tablero.getMatriz()[i][j];
    bool caso1 = c.entradas > 0 && c.dobles > 0;
    bool caso2 = c.dobles >= 2;
    bool caso3 = c.entradas > 0 && c.salidas > 0;
    bool caso4 = c.dobles > 0 && c.salidas > 0;
    bool caso5 = m_fil == i && m_col == j && (c.dobles > 0 || c.salidas > 0);
    // bool hayEntradas = c.entradas > 0 || c.dobles > 0;
    // bool haySalidas = c.salidas > 0 || c.dobles > 0;
    // bool caso1 = hayEntradas && haySalidas && c.dobles != 1;
    // bool caso2 = c.dobles >= 2;
    // bool caso3 = haySalidas && m_fil == i && m_col == j;
    return !caso1 && !caso2 && !caso3 && !caso4 && !caso5 && !c.visitado;
}

bool Yumi::hayGradoInvalido() {
    for (unsigned i = 0; i < m_tablero.getM(); ++i)
        for (unsigned j = i == 0 ? 2 : 0; j < m_tablero.getN(); ++j)
            if (casillaConGradoInvalido(i, j))
                return true;
    return false;
}

inline bool Yumi::inChPt() const {
    for (const Punto &p : m_chPts)
        if (p.first == m_fil && p.second == m_col)
            return true;
    return false;
}

inline void Yumi::siguienteLlamada(unsigned &sol) {
    // Llamada recursiva y predicados 1 y 4
    if (inChPt())
        m_sigChPt++;
    m_tablero.getMatriz()[m_fil][m_col].visitado = true;
    m_pasos++;
    if (m_tablero.dentro(m_fil, m_col - 1) &&
        !m_tablero.getMatriz()[m_fil][m_col - 1].visitado) {
        m_col--;
        recResolver(sol);
        m_col++;
    }
    if (m_tablero.dentro(m_fil + 1, m_col) &&
        !m_tablero.getMatriz()[m_fil + 1][m_col].visitado) {
        m_fil++;
        recResolver(sol);
        m_fil--;
    }
    if (m_tablero.dentro(m_fil, m_col + 1) &&
        !m_tablero.getMatriz()[m_fil][m_col + 1].visitado) {
        m_col++;
        recResolver(sol);
        m_col--;
    }
    if (m_tablero.dentro(m_fil - 1, m_col) &&
        !m_tablero.getMatriz()[m_fil - 1][m_col].visitado) {
        m_fil--;
        recResolver(sol);
        m_fil++;
    }
    m_pasos--;
    m_tablero.getMatriz()[m_fil][m_col].visitado = false;
    if (inChPt())
        m_sigChPt--;
}

void Yumi::recResolver(unsigned &sol) {
    // Predicados acotadores
    // --- Comprobación de llegada temprana (Pred 2)
    // cout << "PASO: " << m_pasos << endl;
    // cout << m_fil << "," << m_col << endl;
    for (unsigned i = m_sigChPt + 1; i < m_chPts.size(); ++i)
        if (m_fil == m_chPts[i].first && m_col == m_chPts[i].second) {
            // cout << "Descarto por llegada a otro checkpoint" << endl;
            return;
        }
    // --- Comprobación de llegada a tiempo al checkpoint (Pred 7)
    if (distanciaAChPt() > m_pasosChPt[m_sigChPt] - m_pasos) {
        // cout << "Descarto por llegada a checkpoint actual" << endl;
        // cout << distanciaAChPt() << ">" << m_pasosChPt[m_sigChPt] << '-'
        //      << m_pasos << endl;
        return;
    }
    // --- Comprobación de llegada temprana a checkpoint actual (Pred 5)
    if (m_fil == m_chPts[m_sigChPt].first &&
        m_col == m_chPts[m_sigChPt].second &&
        m_pasos != m_pasosChPt[m_sigChPt]) {
        // cout << "Descarto por llegada temprana a checkpoint actual" << endl;
        return;
    }
    // --- Comprobación de grados
    recalcularGrados();
    if (hayGradoInvalido()) {
        // cout << "Descarto por grado invalido" << endl;
        // for (auto &p : m_tablero.getMatriz()) {
        //     for (auto &c : p)
        //         cout << c.entradas << "," << c.salidas << "," << c.dobles
        //              << " - ";
        //     cout << endl;
        // }
        return;
    }
    // Caso base y predicado 3
    if (m_fil == c_FIN.first && m_col == c_FIN.second) {
        // cout << "SOLUCIÓN" << endl;
        sol++;
        return;
    }
    // Llamada recursiva
    // cout << "Llamada recursiva" << endl;
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
    for (unsigned i = 0; i < c_CHECKPOINTS; ++i)
        if (distancia(m_chPts[i], m_chPts[i + 1]) >
            m_pasosChPt[i] - m_pasosChPt[i + 1])
            return 0;
    // Llamada recursiva
    unsigned soluciones = 0;
    recResolver(soluciones);
    return soluciones;
}
