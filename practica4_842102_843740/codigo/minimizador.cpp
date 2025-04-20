#include "minimizador.hpp"
#include <algorithm>

using namespace std;

Minimizador::Minimizador(const Tren& tren, std::vector<Pedido>& p) : U(0) {
    // Ordenar p de mayor a menor ingreso
    for (unsigned i = 0; i < p.size(); ++i) {
        for (unsigned j = i + 1; j < p.size(); ++j)
            if (p[i].ingreso < p[j].ingreso)
                std::swap(p[i], p[j]);
        U += p[i].ingreso;
    }
    cola.push(Nodo(p, tren));
}

unsigned Minimizador::minimizar() {
    const auto Uoriginal = U;
    while (!cola.empty() && cola.top().cgorro() < U) {
        auto nodoE = cola.top();
        cola.pop();
        auto hijos = nodoE.hijos();
        for (auto& hijo : hijos)
            if (hijo.cgorro() <= U) {
                if (hijo.esSolucion() && hijo.c() < U)
                    U = hijo.c();
                else
                    cola.push(hijo);
            }
    }
    return Uoriginal - U;
}
