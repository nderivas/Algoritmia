#pragma once

#include "Tablero.hpp"
#include "comun.hpp"
#include <array>
#include <fstream>

class Yumi {
    std::array<Punto, c_CHECKPOINTS + 2> m_chPts; // Array de checkpoints
    // Pasos hasta checkpoint
    std::array<unsigned, c_CHECKPOINTS + 2> m_pasosChPt;
    unsigned m_sigChPt, m_pasos;
    int m_x, m_y;
    Tablero m_tablero;

    inline unsigned distanciaAChPt() const;
    void recalcularGrados();
    inline bool hayGradoInvalido();
    inline void siguienteLlamada(unsigned &sol);
    void recResolver(unsigned &sol);

  public:
    Yumi(unsigned m, unsigned n, std::array<Punto, c_CHECKPOINTS + 2> arr);
    unsigned resolver();
    void escribirInforme(std::ofstream &salida) const;
};
