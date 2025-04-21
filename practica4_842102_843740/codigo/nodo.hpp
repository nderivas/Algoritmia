#pragma once

// Práctica 4 - Algoritmia básica
// Cristina Embid Martínez (842102) y Nicolás de Rivas Morillo (843740)
#include "pedido.hpp"
#include "tren.hpp"
#include <vector>

using Tupla =
    std::vector<bool>; // Vector de booleanos que representa la solucion

class Nodo {
public:
  std::vector<Pedido> pedidos; // Almacena todos los pedidos asociado a un nodo
  Tren tren;                   // Tren asociado a un nodo
  Tupla tupla;                 // Tupla de solución
  unsigned nivel, f;           // Nivel asociado al nodo

  // Constructor
  Nodo(const std::vector<Pedido> p, const Tren &t, unsigned nivel = 0)
      : pedidos(p), tren(t), tupla(p.size(), false), nivel(nivel), f(0) {}
  // Funcion de estimacion
  unsigned cgorro() const;
  // Devuelve vector de hijos sucesores del nodo
  std::vector<Nodo> hijos() const;
  // Funcion de coste
  unsigned c() const;
  // Funcion que determina si el nodo es solucion
  bool esSolucion() const;
};
