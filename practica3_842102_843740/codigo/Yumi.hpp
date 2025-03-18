#pragma once

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

    inline void calcularGrado(Matriz &t, int i, int j);
    void calcularGradosIniciales();
    inline unsigned distanciaAChPt() const;
    inline bool inChPt() const;
    void recalcularGrados();
    inline bool casillaConGradoInvalido(const int i, const int j);
    bool hayGradoInvalido();
    inline void siguienteLlamada(unsigned &sol);
    void recResolver(unsigned &sol);

  public:
    Yumi(unsigned m, unsigned n, std::array<Punto, c_CHECKPOINTS + 1> arr);
    unsigned resolver();
};
