#include "tren.hpp"

bool Tren::subirPasajeros(const Pedido& pedido) {
    for (unsigned i = pedido.inicio; i < pedido.fin; ++i) {
        if (pasajeros[i] + pedido.numPasajeros > capacidad)
            return false; // No se pueden subir los pasajeros
    }
    for (unsigned i = pedido.inicio; i < pedido.fin; ++i)
        pasajeros[i] = pasajeros[i] + pedido.numPasajeros;
    return true;
}
