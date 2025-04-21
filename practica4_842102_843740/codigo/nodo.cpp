// Práctica 4 - Algoritmia básica
// Cristina Embid Martínez (842102) y Nicolás de Rivas Morillo (843740)
#include "nodo.hpp"

// Calcula la función de estimación
unsigned Nodo::cgorro() const {
  unsigned g = 0;
  auto trenCopia = tren; // Crear copia del tren actual
  for (unsigned i = nivel; i < pedidos.size(); ++i)
    if (!trenCopia.subirPasajeros(
            pedidos[i])) // Si no se pueden subir pasajeros, agregar ingreso
      g += pedidos[i].ingreso;
  return f + g;
}

// Genera nodos hijos del nodo actual
// @return vector de nodos hijos generado
std::vector<Nodo> Nodo::hijos() const {
  std::vector<Nodo> hijos = {*this};
  hijos[0].f += hijos[0].pedidos[hijos[0].nivel].ingreso;
  hijos[0].nivel++; // Incrementar nivel del nodo
  Nodo h = *this;   // Crea copia del nodo

  // Si es posible subir los pasajeros del pedido en el nivel actual
  if (h.tren.subirPasajeros(h.pedidos[h.nivel])) {
    h.tupla[h.nivel] = true; // Marcar pedido como aceptado
    h.nivel++;               // Incrementar nivel
    hijos.push_back(h);      // Añadir el nodo como hijo
  }
  return hijos;
}

// Pre: El nodo es solución
unsigned Nodo::c() const { return f; }

// Determina si el nodo actual es una solución válida
bool Nodo::esSolucion() const { return nivel == tupla.size(); }
