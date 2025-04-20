#pragma once

#include "tren.hpp"
#include "pedido.hpp"
#include "nodo.hpp"
#include <vector>
#include <queue>

struct Comparador {
    bool operator()(const Nodo uno, const Nodo dos) {
        return uno.cgorro() > dos.cgorro();
    }
};

class Minimizador {
    std::priority_queue<Nodo, std::vector<Nodo>, Comparador> cola;
    unsigned U;
public:
    Minimizador(const Tren& tren, std::vector<Pedido>& p);
    unsigned minimizar();
    unsigned limiteSuperior();
};
