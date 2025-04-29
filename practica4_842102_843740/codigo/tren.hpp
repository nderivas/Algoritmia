#pragma once

// Práctica 4 - Algoritmia básica
// Cristina Embid Martínez (842102) y Nicolás de Rivas Morillo (843740)
#include "pedido.hpp"
#include <vector>

using Pasajeros = unsigned;

class Tren {
public:
  unsigned capacidad; // Capacidad total del tren
  std::vector<Pasajeros>
      pasajeros; // Vector que contiene el número de pasajeros en cada estacion

  // Constructor
  Tren(const unsigned cap, const unsigned fin)
      : capacidad(cap), pasajeros(fin, 0) {}

    // Devuelve true si los puede subir, false si no
    bool cabenPasajeros(const Pedido &pedido) const;
    // Sube a los pasajeros al tren
    bool subirPasajeros(const Pedido &pedido);
};
