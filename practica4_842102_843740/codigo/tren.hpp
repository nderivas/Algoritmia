#pragma once

#include "pedido.hpp"
#include <vector>

using Pasajeros = unsigned;

class Tren {
public:
    unsigned capacidad;
    std::vector<Pasajeros> pasajeros;

    Tren(const unsigned cap, const unsigned fin) : capacidad(cap), pasajeros(fin, 0) {}
    bool subirPasajeros(const Pedido& pedido); // Devuelve true si los puede subir, false si no
};
