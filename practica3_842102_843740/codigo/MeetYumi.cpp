// Práctica 3 - Algoritmia básica
// Nicolás de Rivas Morillo (843740) y Cristina Embid Martínez (842102)
#include "MeetYumi.hpp"
#include "comun.hpp"
#include <array>
#include <iostream>

using namespace std;

// Implementación del constructor
MeetYumi::MeetYumi(const unsigned n, const unsigned m,
                   const array<Punto, c_CHECKPOINTS + 1> &arr) {
    // Yumi desde el inicio hasta el punto medio
    y1 = unique_ptr<Yumi>(new Yumi(n, m, arr, 1, 0));
    // Yumi desde el punto medio hasta el final
    y2 = unique_ptr<Yumi>(new Yumi(n, m, arr, c_CHECKPOINTS, 1));
}

// Verifica si hay colisión entre dos tableros
// @param  Tablero del primer Yumi
// @param  Tablero del segundo Yumi
// @return Devuelve true si ambos han visitado la misma celda
inline bool hayColision(Matriz &t1, Matriz &t2) {
    for (unsigned i = 0; i < t1.size(); ++i)
        for (unsigned j = i > 1 ? 0 : 1; j < t1[0].size(); ++j)
            if (t1[i][j].visitado && t2[i][j].visitado)
                return true; // Se detecta una colisión en la misma celda
    return false;
}

// Devuelve el número de soluciones sin colisión
unsigned MeetYumi::resolver() {
    // Calcula caminos desde el inicio al medio
    auto solucionesIniMedio = y1->resolver();
    // Calcula caminos desde el medio al final
    auto solucionesMedioFin = y2->resolver();
    unsigned sol = 0;
    for (auto &iniMedio : solucionesIniMedio)
        for (auto &medioFin : solucionesMedioFin) {
            sol += !hayColision(iniMedio, medioFin);
        }
    return sol;
}
