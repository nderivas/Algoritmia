#pragma once

// Práctica 3 - Algoritmia básica
// Nicolás de Rivas Morillo (843740) y Cristina Embid Martínez (842102)

// Representa información sobre una casilla
class Casilla {
  public:
    unsigned entradas, salidas, dobles; // Indican los grados de la casilla
    bool visitado;                      // Indica si la casilla ha sido visitada
};
