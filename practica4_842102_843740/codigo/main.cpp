#include "minimizador.hpp"
#include <vector>
#include <iostream>
#include <fstream>
#include <ctime>
#include <iomanip>

using namespace std;

struct Entrada {
    unsigned capacidadTren, final;
    std::vector<Pedido> Pedidos;
};

vector<Entrada> leerEntrada(const string& nombreArchivo) {
    auto in = ifstream(nombreArchivo);
    vector<Entrada> v = {};
    while (!in.eof()) {
        Entrada entrada;
        unsigned n;
        in >> entrada.capacidadTren >> entrada.final >> n;
        if (in.eof()) break;
        for (unsigned i = 0; i < n; ++i) {
            unsigned ini, fin, pasajeros;
            in >> ini >> fin >> pasajeros;
            entrada.Pedidos.push_back(Pedido(ini, fin, pasajeros));
        }
        v.push_back(entrada);
    }
    return v;
}

inline void escribirSalida(ofstream& out, unsigned resultado, double tiempo) {
    out << resultado << ' ' /*<< fixed << setprecision(3)*/ << tiempo << endl;
}

int main(int argc, char** argv) {
    // Parse arguments
    if (argc < 3) {
        cerr << "Uso: " << argv[0] << " <archivo_entrada> <archivo_salida>" << endl;
        return 1;
    }
    auto problemas = leerEntrada(argv[1]);
    // Solve problem
    auto out = ofstream(argv[2]);
    for (auto& problema : problemas) {
        // TODO: Empezar crono
        auto tIni = clock();
        Minimizador minimizador(Tren(problema.capacidadTren, problema.final), problema.Pedidos);
        unsigned resultado = minimizador.minimizar();
        // TODO: Terminar crono
        auto tFin = clock();
        auto t = static_cast<double>(tFin - tIni) / CLOCKS_PER_SEC;
        escribirSalida(out, resultado, t);
    }
    return 0;
}
