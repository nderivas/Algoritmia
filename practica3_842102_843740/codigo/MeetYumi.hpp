// Práctica 3 - Algoritmia básica
// Nicolás de Rivas Morillo (843740) y Cristina Embid Martínez (842102)
#include "Yumi.hpp"
#include "comun.hpp"
#include <memory>

// Clase MeetYumi
class MeetYumi {
    std::unique_ptr<Yumi> y1,
        y2; // Punteros para manejar dos instancias de Yumi

  public:
    unsigned nSol;
    // Constructor
    MeetYumi(const unsigned n, const unsigned m,
             const std::array<Punto, c_CHECKPOINTS + 1> &arr);
    unsigned resolver();
};
