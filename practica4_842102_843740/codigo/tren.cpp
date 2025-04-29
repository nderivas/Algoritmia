// Práctica 4 - Algoritmia básica
// Cristina Embid Martínez (842102) y Nicolás de Rivas Morillo (843740)
#include "tren.hpp"

bool Tren::cabenPasajeros(const Pedido& pedido) const {
    for (unsigned i = pedido.inicio; i < pedido.fin; ++i) {
      // Verifica si la cantidad de pasajeros actuales más los nuevos excede la
      // capacidad
      if (pasajeros[i] + pedido.numPasajeros > capacidad)
        return false; // No se pueden subir los pasajeros
    }
    return true;
}

// Funcion que intenta subir pasajeros en un rango de estaciones
bool Tren::subirPasajeros(const Pedido &pedido) {
    if (!cabenPasajeros(pedido))
        return false;
    // Si la capacidad no ha sido superada en ninguna estación, se suben pasajeros
    for (unsigned i = pedido.inicio; i < pedido.fin; ++i)
        pasajeros[i] = pasajeros[i] + pedido.numPasajeros;
    return true;
}
