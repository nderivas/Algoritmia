// Práctica 4 - Algoritmia básica
// Cristina Embid Martínez (842102) y Nicolás de Rivas Morillo (843740)
#include "nodo.hpp"

// Calcula la función de cota superior
unsigned Nodo::U() const {
  unsigned g = 0;
  auto trenCopia = tren; // Crear copia del tren actual
  for (unsigned i = nivel; i < pedidos.size(); ++i)
    // Si no se pueden subir pasajeros, agregar ingreso
    if (!trenCopia.subirPasajeros(pedidos[i]))
      g += pedidos[i].ingreso;
  return g + f;
}

unsigned Nodo::cgorro() const {
    if (gcgorro != -1)
        return gcgorro;
    unsigned g = 0;
    for (unsigned i = nivel; i < pedidos.size(); ++i)
      // Si no se pueden subir pasajeros, agregar ingreso
      if (!tren.cabenPasajeros(pedidos[i]))
        g += pedidos[i].ingreso;
    gcgorro = f + g;
    return gcgorro;
}

// Genera nodos hijos del nodo actual
// @return vector de nodos hijos generado
std::vector<Nodo> Nodo::hijos() const {
  std::vector<Nodo> hijos = {*this};
  hijos[0].f += hijos[0].pedidos[hijos[0].nivel].ingreso;
  hijos[0].nivel++; // Incrementar nivel del nodo
  hijos[0].gcgorro = -1; // Resetear gcgorro
  Nodo h = *this;   // Crea copia del nodo
  // Si es posible subir los pasajeros del pedido en el nivel actual
  if (h.tren.subirPasajeros(h.pedidos[h.nivel])) {
    h.tupla[h.nivel] = true; // Marcar pedido como aceptado
    h.nivel++;               // Incrementar nivel
    h.gcgorro = -1; // Resetear gcgorro
    hijos.push_back(h);      // Añadir el nodo como hijo
  }
  return hijos;
}

// Determina si el nodo actual es una solución válida
bool Nodo::esSolucion() const { return nivel == tupla.size(); }
