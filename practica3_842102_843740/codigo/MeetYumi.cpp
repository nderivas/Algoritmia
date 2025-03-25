#include "MeetYumi.hpp"
#include "comun.hpp"
#include <array>
#include <iostream>

using namespace std;

MeetYumi::MeetYumi(const unsigned n, const unsigned m, const array<Punto, c_CHECKPOINTS + 1>& arr) {
    y1 = unique_ptr<Yumi>(new Yumi(n, m, arr, 1, 0));
    y2 = unique_ptr<Yumi>(new Yumi(n, m, arr, c_CHECKPOINTS, 1));
}

inline bool hayColision(Tablero& t1, Tablero& t2) {
    for (unsigned i = 0; i < t1.getM(); ++i)
        for (unsigned j = i > 1 ? 0 : 1; j < t1.getN(); ++j)
            if (t1.getMatriz()[i][j].visitado && t2.getMatriz()[i][j].visitado)
                return true;
    return false;
}

void printTablero(Tablero& t) {
    for (unsigned i = 0; i < t.getM(); ++i) {
        for (unsigned j = 0; j < t.getN(); ++j)
            cout << t.getMatriz()[i][j].visitado << ' ';
        cout << endl;
    }
    cout << endl;
}

unsigned MeetYumi::resolver() {
    // cout << "Yumi2" << endl;
    auto solucionesIniMedio = y1->resolver();
    // for (auto& t : solucionesIniMedio)
    //     printTablero(t);
    // cout << "Yumi2" << endl;
    auto solucionesMedioFin = y2->resolver();
    // for (auto& t : solucionesMedioFin)
    //     printTablero(t);
    unsigned sol = 0;
    for (auto& iniMedio : solucionesIniMedio)
        for (auto& medioFin : solucionesMedioFin) {
            // if (!hayColision(iniMedio, medioFin)) {
            //     cout << "SOL" << endl;
            //     printTablero(iniMedio);
            //     printTablero(medioFin);
            // }
            sol += !hayColision(iniMedio, medioFin);
        }
    return sol;
}
