#include "nodo.hpp"

unsigned Nodo::cgorro() const {
    unsigned g = 0;
    auto trenCopia = tren;
    for (unsigned i = nivel; i < pedidos.size(); ++i)
        if (!trenCopia.subirPasajeros(pedidos[i]))
            g += pedidos[i].ingreso;
    return f + g;
}

std::vector<Nodo> Nodo::hijos() const {
    std::vector<Nodo> hijos = { *this };
    hijos[0].f += hijos[0].pedidos[hijos[0].nivel].ingreso;
    hijos[0].nivel++;
    Nodo h = *this;
    if (h.tren.subirPasajeros(h.pedidos[h.nivel])) {
        h.tupla[h.nivel] = true;
        h.nivel++;
        hijos.push_back(h);
    }
    return hijos;
}

// Pre: El nodo es solución
unsigned Nodo::c() const {
    return f;
}

bool Nodo::esSolucion() const {
    return nivel == tupla.size();
}
