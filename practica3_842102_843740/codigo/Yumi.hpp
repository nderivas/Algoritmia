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

    inline void calcularGrado(const int i, const int j);
    void calcularGradosIniciales();
    inline unsigned distanciaAChPt() const;
    inline bool inChPt() const;
    bool recalcularGrados(const int i, const int j);
    inline bool casillaConGradoInvalido(const int i, const int j);
    inline void siguienteLlamada(unsigned &sol);
    void recResolver(unsigned &sol);

  public:
    // Constructor
    Yumi(unsigned m, unsigned n, std::array<Punto, c_CHECKPOINTS + 1> arr);
    unsigned resolver();
};
