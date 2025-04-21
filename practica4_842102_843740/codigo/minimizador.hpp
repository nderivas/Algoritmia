#pragma once

// Práctica 4 - Algoritmia básica
// Cristina Embid Martínez (842102) y Nicolás de Rivas Morillo (843740)

#include "nodo.hpp"
#include "pedido.hpp"
#include "tren.hpp"
#include <queue>
#include <vector>

// Estructura comparadora para la cola de prioridades
struct Comparador {
  bool operator()(const Nodo &uno, const Nodo &dos) {
    return uno.cgorro() > dos.cgorro();
  }
};

// Clase de Minimizador
class Minimizador {
  // Atributos
  std::priority_queue<Nodo, std::vector<Nodo>, Comparador> cola;
  unsigned U;

public:
  // Métodos
  Minimizador(const Tren &tren, std::vector<Pedido> &p);
  unsigned minimizar();
};
