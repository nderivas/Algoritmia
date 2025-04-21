#pragma once

// Práctica 4 - Algoritmia básica
// Cristina Embid Martínez (842102) y Nicolás de Rivas Morillo (843740)

class Pedido {
public:
  // inicio: estación de salida
  // fin: estacion de llegada
  // numPasajeros: numero de pasajeros
  // ingreso: (fin - inicio)*numPasajeros
  unsigned inicio, fin, numPasajeros, ingreso;
  // Constructor
  Pedido(const unsigned ini, const unsigned fin, const unsigned n)
      : inicio(ini), fin(fin), numPasajeros(n), ingreso((fin - ini) * n) {}
};
