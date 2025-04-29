#include "minimizador.hpp"
#include <algorithm>

// Práctica 4 - Algoritmia básica
// Cristina Embid Martínez (842102) y Nicolás de Rivas Morillo (843740)

using namespace std;

// Constructor
Minimizador::Minimizador(const Tren &tren, std::vector<Pedido> &p) : U(0) {
  // Ordenar los pedidos de mayor a menor ingreso, este es el orden
  // para calcular la cgorro luego
  for (unsigned i = 0; i < p.size(); ++i) {
    for (unsigned j = i + 1; j < p.size(); ++j)
      if (p[i].ingreso < p[j].ingreso)
        std::swap(p[i], p[j]);
    U += p[i].ingreso; // Calculamos la U de la raíz
  }
  cola.push(Nodo(p, tren)); // Añadimos la raíz a la cola
}

// Función de minimización por ramificación y poda
unsigned Minimizador::minimizar() {
  const auto Uoriginal = U; // Nos piden Uoriginal - U como resultado
  // Mientras haya ramas (interesantes) que explorar
  while (!cola.empty() && cola.top().cgorro() < U) {
    // Cogemos la de menor coste
    auto nodoE = cola.top();
    cola.pop();
    // Calculamos sus hijos
    auto hijos = nodoE.hijos(); // Ramificación
    // Para cada hijo vemos si nos interesa
    for (auto &hijo : hijos)
      if (hijo.cgorro() <= U) { // Poda
        /*if (hijo.esSolucion() && hijo.c() < U)
          U = hijo.c();
        else if (hijo.U() < U) {
          U = hijo.U();
          cola.push(hijo);
        } else
          cola.push(hijo);*/
        if (hijo.U() < U)
            // Notese que si hijo.esSolucion() => hijo.cgorro() = hijo.c() = hijo.U()
            U = hijo.U(); // Actualizamos la U
        if (!hijo.esSolucion())
            cola.push(hijo);
      }
  }
  return Uoriginal - U;
}
