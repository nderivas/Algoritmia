#include "MeetYumi.hpp"
#include "comun.hpp"
#include <array>
#include <iostream>

using namespace std;

MeetYumi::MeetYumi(const unsigned n, const unsigned m,
                   const array<Punto, c_CHECKPOINTS + 1> &arr) {
    y1 = unique_ptr<Yumi>(new Yumi(n, m, arr, 1, 0));
    y2 = unique_ptr<Yumi>(new Yumi(n, m, arr, c_CHECKPOINTS, 1));
}

inline bool hayColision(Matriz &t1, Matriz &t2) {
    for (unsigned i = 0; i < t1.size(); ++i)
        for (unsigned j = i > 1 ? 0 : 1; j < t1[0].size(); ++j)
            if (t1[i][j].visitado && t2[i][j].visitado)
                return true;
    return false;
}

void printTablero(Tablero &t) {
    for (unsigned i = 0; i < t.getM(); ++i) {
        for (unsigned j = 0; j < t.getN(); ++j)
            cout << t.getMatriz()[i][j].visitado << ' ';
        cout << endl;
    }
    cout << endl;
}

unsigned MeetYumi::resolver() {
    auto solucionesIniMedio = y1->resolver();
    auto solucionesMedioFin = y2->resolver();
    unsigned sol = 0;
    for (auto &iniMedio : solucionesIniMedio)
        for (auto &medioFin : solucionesMedioFin) {
            sol += !hayColision(iniMedio, medioFin);
        }
    return sol;
}
