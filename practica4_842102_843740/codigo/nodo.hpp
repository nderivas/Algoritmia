#pragma once

#include "pedido.hpp"
#include "tren.hpp"
#include <vector>

using Tupla = std::vector<bool>;

class Nodo {
public:
  std::vector<Pedido> pedidos;
  Tren tren;
  Tupla tupla;
  unsigned nivel, f;

  Nodo(const std::vector<Pedido> p, const Tren &t, unsigned nivel = 0)
      : pedidos(p), tren(t), tupla(p.size(), false), nivel(nivel), f(0) {}
  unsigned cgorro() const;
  // unsigned U() const;
  std::vector<Nodo> hijos() const;
  unsigned c() const;
  bool esSolucion() const;
};
