#pragma once

class Pedido {
public:
    unsigned inicio, fin, numPasajeros, ingreso;
    Pedido(const unsigned ini, const unsigned fin, const unsigned n)
        : inicio(ini), fin(fin), numPasajeros(n), ingreso((fin-ini)*n) {}
};
