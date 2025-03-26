#pragma once

// Práctica 3 - Algoritmia básica
// Nicolás de Rivas Morillo (843740) y Cristina Embid Martínez (842102)
#include "Tablero.hpp"
#include "comun.hpp"
#include <array>

class Yumi {
    std::array<Punto, c_CHECKPOINTS + 1> m_chPts; // Array de checkpoints
    // Pasos hasta checkpoint
    std::array<unsigned, c_CHECKPOINTS + 1> m_pasosChPt;
    unsigned m_sigChPt, m_pasos;
    int m_fil, m_col;
    Tablero m_tablero;
    bool hayGradoInvalido;
    unsigned llegada;
    bool segundaYumi, mirarDesconexion;

    void dfs(const int i, const int j, Tablero &t, unsigned &marcadas);
    bool hayDesconexion();
    inline void calcularGrado(const int i, const int j);
    void calcularGradosIniciales();
    inline unsigned distanciaAChPt() const;
    inline bool inChPt() const;
    bool recalcularGrados(const int i, const int j);
    inline bool casillaConGradoInvalido(const int i, const int j);
    inline void siguienteLlamada(std::vector<Matriz> &sol);
    void recResolver(std::vector<Matriz> &sol);

  public:
    // Constructor
    Yumi(unsigned m, unsigned n, std::array<Punto, c_CHECKPOINTS + 1> arr,
         const unsigned llegada = c_CHECKPOINTS, const unsigned inicio = 0);
    std::vector<Matriz> resolver();
};
