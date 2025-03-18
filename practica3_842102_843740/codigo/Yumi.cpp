// Práctica 3 - Algoritmia básica
// Nicolás de Rivas Morillo (843740) y Cristina Embid Martínez (842102)
#include "Yumi.hpp"
#include <cmath>
#include <iostream>

using namespace std;

// Calcula la distancia entre dos puntos
inline unsigned distancia(Punto a, Punto b) {
    return abs(a.first - b.first) + abs(a.second - b.second);
}

// Calcula el grado de una casilla en la Matriz, actualizando las entradas,
// salidas y dobles de la casilla en la matriz
// @param t Matriz en la que se calcula el grado
// @param i Indice de fila de la casilla
// @param j Indice de columna de la casilla
inline void Yumi::calcularGrado(Matriz &t, int i, int j) {
    // Inicialización de la casilla
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

// Calcular grados iniciales de la matriz
void Yumi::calcularGradosIniciales() {
    auto &t = m_tablero.getMatriz();
    t[0][0].salidas = 2;  // Salidas de la casilla de inicio
    t[0][1].entradas = 3; // Entradas de la casilla de inicio
    // Recorre todas las casillas de la matriz (excepto las ya inicializadas)
    for (unsigned i = 0; i < m_tablero.getM(); ++i)
        for (unsigned j = i == 0 ? 2 : 0; j < m_tablero.getN(); ++j)
            calcularGrado(t, i, j); // Calcula el grado de la casilla
}

// Constructor de Yumi
Yumi::Yumi(unsigned n, unsigned m, array<Punto, c_CHECKPOINTS + 1> arr)
    : m_chPts(arr), m_sigChPt(0), m_pasos(1), m_fil(0), m_col(0),
      m_tablero(n, m) {
    // Calcula los pasos requeridos para cada checkpoint
    for (unsigned i = 1; i <= c_CHECKPOINTS + 1; ++i)
        m_pasosChPt[i - 1] = (n * m * i) / (c_CHECKPOINTS + 1);
    calcularGradosIniciales(); // Calculo de grados iniciales
}

// Calcula la distancia al siguiente checkpoint
inline unsigned Yumi::distanciaAChPt() const {
    return distancia({m_fil, m_col}, m_chPts[m_sigChPt]);
}

// Recalcula los grados en la matriz, reiniciando entradas, salidas y dobles
void Yumi::recalcularGrados() { calcularGradosIniciales(); }

// Verifica si la casilla en las coordenadas i,j tiene un grado inválido
inline bool Yumi::casillaConGradoInvalido(const int i, const int j) {
    Casilla &c = m_tablero.getMatriz()[i][j];
    bool caso1 = c.entradas > 0 && c.dobles > 0;  // Hay entradas y dobles
    bool caso2 = c.dobles >= 2;                   // Hay al menos dos dobles
    bool caso3 = c.entradas > 0 && c.salidas > 0; // Hay entradas y salidas
    bool caso4 = c.dobles > 0 && c.salidas > 0;   // Hay dobles y salidas
    // Estoy en la casilla y puedo salir -> hay dobles o salidas
    bool caso5 = m_fil == i && m_col == j && (c.dobles > 0 || c.salidas > 0);
    return !caso1 && !caso2 && !caso3 && !caso4 && !caso5 && !c.visitado;
}

// Verifica si hay alguna casilla con grado inválido en la matriz
// @return Devuelve true si existe al menos una casilla con grado inválido
bool Yumi::hayGradoInvalido() {
    for (unsigned i = 0; i < m_tablero.getM(); ++i)
        for (unsigned j = i == 0 ? 2 : 0; j < m_tablero.getN(); ++j)
            if (casillaConGradoInvalido(i, j))
                return true;
    return false;
}

// Verifica si la posición actual está en algún checkpoint
inline bool Yumi::inChPt() const {
    for (const Punto &p : m_chPts)
        if (p.first == m_fil && p.second == m_col)
            return true;
    return false;
}

// Función recursiva para resolver el problema
inline void Yumi::siguienteLlamada(unsigned &sol) {
    // Llamada recursiva y predicados 1 y 4
    if (inChPt())
        m_sigChPt++; // Avanza el siguiente checkpoint si la posición está en un
                     // checkpoint
    m_tablero.getMatriz()[m_fil][m_col].visitado =
        true;  // Marca casilla como visitada
    m_pasos++; // Incrementa contador de pasos
    // Verifica si se puede mover hacia las casillas vecinas
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
    m_pasos--; // Decrementa contador de pasos
    m_tablero.getMatriz()[m_fil][m_col].visitado = false;
    if (inChPt())
        m_sigChPt--; // Retrocede al checkpoint anterior
}

// Realiza la búsqueda recursiva de soluciones, comprobando los predicados
// acotadores
// @param sol número de soluciones
void Yumi::recResolver(unsigned &sol) {
    // Predicados acotadores
    // --- Comprobación de llegada temprana (Pred 2)
    for (unsigned i = m_sigChPt + 1; i < m_chPts.size(); ++i)
        if (m_fil == m_chPts[i].first && m_col == m_chPts[i].second) {
            return;
        }
    // --- Comprobación de llegada a tiempo al checkpoint (Pred 5)
    if (distanciaAChPt() > m_pasosChPt[m_sigChPt] - m_pasos) {
        return;
    }
    // --- Comprobación de llegada temprana a checkpoint actual (Pred 7)
    if (m_fil == m_chPts[m_sigChPt].first &&
        m_col == m_chPts[m_sigChPt].second &&
        m_pasos != m_pasosChPt[m_sigChPt]) {
        return;
    }
    // --- Comprobación de grados
    // Recalcula grados de la matriz y verifica si alguna casilla tiene un grado
    // inválido
    recalcularGrados();
    if (hayGradoInvalido()) {
        return;
    }
    // Caso base y predicado 3
    // Se verifica si la posición actual es la casilla final.
    if (m_fil == c_FIN.first && m_col == c_FIN.second) {
        // cout << "SOLUCIÓN" << endl;
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
    // Se verifica que todos los checkpoints estén dentro de los límites de la
    // matriz
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
    return soluciones; // Retorna el número total de soluciones
}
