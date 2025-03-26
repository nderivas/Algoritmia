// Práctica 3 - Algoritmia básica
// Nicolás de Rivas Morillo (843740) y Cristina Embid Martínez (842102)
#include "Yumi.hpp"

using namespace std;

// Constructor de Yumi
Yumi::Yumi(unsigned n, unsigned m, array<Punto, c_CHECKPOINTS + 1> arr,
           const unsigned llegada, const unsigned inicio)
    : m_chPts(arr), m_sigChPt(inicio), m_pasos(1), m_fil(0), m_col(0),
      m_tablero(n, m), hayGradoInvalido(false), llegada(llegada),
      segundaYumi(inicio > 0), mirarDesconexion(false) {
    if (segundaYumi) {
        m_tablero.getMatriz()[0][0].visitado = true;
        m_tablero.getMatriz()[1][0].visitado = true;
        m_tablero.getMatriz()[m_fil][m_col].visitado = true;
        m_fil = m_chPts[inicio].first;
        m_col = m_chPts[inicio].second;
        m_pasos = n * m / 2;
    }
    // Calcula los pasos requeridos para cada checkpoint
    for (unsigned i = 1; i <= c_CHECKPOINTS + 1; ++i)
        m_pasosChPt[i - 1] = (n * m * i) / (c_CHECKPOINTS + 1);
    calcularGradosIniciales(); // Calculo de grados iniciales
}

inline int abs(const int n) { return n < 0 ? -n : n; }

// Calcula la distancia entre dos puntos
inline unsigned d(Punto a, Punto b) {
    return abs(a.first - b.first) + abs(a.second - b.second);
}

void Yumi::dfs(const int i, const int j, Tablero &t, unsigned &marcadas) {
    auto &m = t.getMatriz();
    marcadas++;
    m[i][j].marca = true;
    if (t.dentro(i - 1, j) && !m[i - 1][j].marca && !m[i - 1][j].visitado &&
        d({i - 1, j}, {m_fil, m_col}) != 0)
        dfs(i - 1, j, t, marcadas);
    if (t.dentro(i + 1, j) && !m[i + 1][j].marca && !m[i + 1][j].visitado &&
        d({i + 1, j}, {m_fil, m_col}) != 0)
        dfs(i + 1, j, t, marcadas);
    if (t.dentro(i, j - 1) && !m[i][j - 1].marca && !m[i][j - 1].visitado &&
        d({i, j - 1}, {m_fil, m_col}) != 0)
        dfs(i, j - 1, t, marcadas);
    if (t.dentro(i, j + 1) && !m[i][j + 1].marca && !m[i][j + 1].visitado &&
        d({i, j + 1}, {m_fil, m_col}) != 0)
        dfs(i, j + 1, t, marcadas);
}

bool Yumi::hayDesconexion() {
    for (auto &v : m_tablero.getMatriz())
        for (auto &c : v)
            c.marca = false;
    unsigned marcadas = 0;
    dfs(0, 1, m_tablero, marcadas);
    return marcadas < m_tablero.getM() * m_tablero.getN() - m_pasos;
}

// Calcula el grado de una casilla en la Matriz, actualizando las entradas,
// salidas y dobles de la casilla en la matriz
// @param t Matriz en la que se calcula el grado
// @param i Indice de fila de la casilla
// @param j Indice de columna de la casilla
inline void Yumi::calcularGrado(const int i, const int j) {
    auto &t = m_tablero.getMatriz();
    // Inicialización de la casilla
    t[i][j].entradas = 0;
    t[i][j].salidas = 0;
    t[i][j].dobles = 0;
    for (int off = -1; off <= 1; off = off + 2) {
        if (m_tablero.dentro(i + off, j) && !t[i + off][j].visitado) {
            if (d(c_INI, {i + off, j}) == 0)
                t[i][j].entradas++;
            else if (d(c_FIN, {i + off, j}) == 0)
                t[i][j].salidas++;
            else
                t[i][j].dobles++;
        }
        if (m_tablero.dentro(i, j + off) && !t[i][j + off].visitado) {
            if (d(c_INI, {i, j + off}) == 0)
                t[i][j].entradas++;
            else if (d(c_FIN, {i, j + off}) == 0)
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
    t[0][1].entradas = 3; // Entradas de la casilla final
    // Recorre todas las casillas de la matriz (excepto las ya inicializadas)
    for (unsigned i = 0; i < m_tablero.getM(); ++i)
        for (unsigned j = i == 0 ? 2 : 0; j < m_tablero.getN(); ++j)
            calcularGrado(i, j); // Calcula el grado de la casilla
}

// Calcula la distancia al siguiente checkpoint
inline unsigned Yumi::distanciaAChPt() const {
    return d({m_fil, m_col}, m_chPts[m_sigChPt]);
}

// Recalcula los grados en la matriz, reiniciando entradas, salidas y dobles
bool Yumi::recalcularGrados(const int i, const int j) {
    auto &t = m_tablero.getMatriz();
    for (int off = -1; off <= 1; off = off + 2) {
        if (m_tablero.dentro(i + off, j) && !t[i + off][j].visitado) {
            calcularGrado(i + off, j);
            if (casillaConGradoInvalido(i + off, j))
                return true;
        }
        if (m_tablero.dentro(i, j + off) && !t[i][j + off].visitado) {
            calcularGrado(i, j + off);
            if (casillaConGradoInvalido(i, j + off))
                return true;
        }
    }
    return false;
}

// Verifica si la casilla en las coordenadas i,j tiene un grado inválido
inline bool Yumi::casillaConGradoInvalido(const int i, const int j) {
    Casilla &c = m_tablero.getMatriz()[i][j];
    bool caso1 = c.entradas > 0 && c.dobles > 0;  // Hay entradas y dobles
    bool caso2 = c.dobles >= 2;                   // Hay al menos dos dobles
    bool caso3 = c.entradas > 0 && c.salidas > 0; // Hay entradas y salidas
    bool caso4 = c.dobles > 0 && c.salidas > 0;   // Hay dobles y salidas
    // Estoy en la casilla y puedo salir -> hay dobles o salidas
    bool caso5 =
        d({i, j}, {m_fil, m_col}) == 0 && (c.dobles > 0 || c.salidas > 0);
    // Estoy al final y puedo entrar
    bool caso6 = d(c_FIN, {i, j}) == 0 && (c.dobles > 0 || c.entradas > 0);
    // Yumi está en el final
    bool caso7 = d(c_FIN, {m_fil, m_col}) == 0 && d(c_FIN, {i, j}) == 0;
    return !caso1 && !caso2 && !caso3 && !caso4 && !caso5 && !caso6 && !caso7 &&
           !c.visitado;
}

// Verifica si la posición actual está en algún checkpoint
inline bool Yumi::inChPt() const {
    for (const Punto &p : m_chPts)
        if (d(p, {m_fil, m_col}) == 0)
            return true;
    return false;
}

// Función recursiva para resolver el problema
inline void Yumi::siguienteLlamada(vector<Matriz> &sol) {
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
        mirarDesconexion = m_col == 0;
        hayGradoInvalido = recalcularGrados(m_fil, m_col + 1);
        recResolver(sol);
        m_col++;
    }
    if (m_tablero.dentro(m_fil + 1, m_col) &&
        !m_tablero.getMatriz()[m_fil + 1][m_col].visitado) {
        m_fil++;
        mirarDesconexion = m_fil == m_tablero.getM() - 1;
        hayGradoInvalido = recalcularGrados(m_fil - 1, m_col);
        recResolver(sol);
        m_fil--;
    }
    if (m_tablero.dentro(m_fil, m_col + 1) &&
        !m_tablero.getMatriz()[m_fil][m_col + 1].visitado) {
        m_col++;
        mirarDesconexion = m_col == m_tablero.getN() - 1;
        hayGradoInvalido = recalcularGrados(m_fil, m_col - 1);
        recResolver(sol);
        m_col--;
    }
    if (m_tablero.dentro(m_fil - 1, m_col) &&
        !m_tablero.getMatriz()[m_fil - 1][m_col].visitado) {
        m_fil--;
        mirarDesconexion = m_fil == 0;
        hayGradoInvalido = recalcularGrados(m_fil + 1, m_col);
        recResolver(sol);
        m_fil++;
    }
    hayGradoInvalido = false;
    m_pasos--; // Decrementa contador de pasos
    m_tablero.getMatriz()[m_fil][m_col].visitado = false;
    if (inChPt())
        m_sigChPt--; // Retrocede al checkpoint anterior
}

// Realiza la búsqueda recursiva de soluciones, comprobando los predicados
// acotadores
// @param sol número de soluciones
void Yumi::recResolver(vector<Matriz> &sol) {
    // Predicados acotadores
    // --- Comprobación de grados
    // Recalcula grados de la matriz y verifica si alguna casilla tiene
    // un grado inválido
    if (hayGradoInvalido && !segundaYumi)
        return;
    // --- Comprobación de llegada a tiempo al checkpoint (Pred 5)
    if (distanciaAChPt() > m_pasosChPt[m_sigChPt] - m_pasos)
        return;
    // --- Comprobación de llegada temprana a checkpoint actual (Pred 7)
    if (d({m_fil, m_col}, m_chPts[m_sigChPt]) == 0 &&
        m_pasos != m_pasosChPt[m_sigChPt])
        return;
    // --- Comprobación de llegada temprana (Pred 2)
    for (unsigned i = 0; i < m_chPts.size(); ++i) {
        if (i == m_sigChPt)
            continue;
        if (d({m_fil, m_col}, m_chPts[i]) == 0)
            return;
    }
    // --- Comprobación de desconexión (Pred 8)
    if (mirarDesconexion && d(c_FIN, {m_fil, m_col}) && hayDesconexion())
        return;
    // Caso base y predicado 3
    // Se verifica si la posición actual es la casilla final.
    if (d({m_fil, m_col}, m_chPts[llegada]) == 0) {
        sol.push_back(m_tablero.getMatriz());
        return;
    }
    // Llamada recursiva
    siguienteLlamada(sol);
}

// Wrapper de la llamada recursiva
vector<Matriz> Yumi::resolver() {
    // Comprobaciones
    // --- Checkpoints dentro del tablero
    // Se verifica que todos los checkpoints estén dentro de los límites de
    // la matriz
    for (auto &p : m_chPts)
        if (!m_tablero.dentro(p.first, p.second))
            return {};
    // Llego de un checkpoint a otro
    for (unsigned i = 0; i < c_CHECKPOINTS; ++i)
        if (d(m_chPts[i], m_chPts[i + 1]) > m_pasosChPt[i] - m_pasosChPt[i + 1])
            return {};
    // Llamada recursiva
    vector<Matriz> soluciones;
    recResolver(soluciones);
    return soluciones; // Retorna el número total de soluciones
}
