#include "Yumi.hpp"
#include <fstream>
#include <iostream>

using namespace std;

void escribirInforme(std::ostream &out, unsigned sol, time_t tiempo) {
    // TODO: Hacer
}

int main(int argc, char **argv) {
    if (argc != 2) {
        cerr << "USO: ./recorridosYumi <pruebas.txt> <resultados.txt>" << endl;
        exit(1);
    }
    ifstream in(argv[0]);
    ofstream out(argv[1]);
    if (!in.is_open() || !out.is_open()) {
        cerr << "Alguno de los archivos no existe." << endl;
        exit(1);
    }
    int n, m;
    array<Punto, c_CHECKPOINTS + 1> arr;
    arr[c_CHECKPOINTS] = c_FIN;
    while (!in.eof()) {
        in >> n >> m;
        for (int i = 0; i < c_CHECKPOINTS; ++i)
            in >> arr[i].first >> arr[i].second;
        Yumi yumi(n, m, arr);
        // Start timer
        unsigned soluciones = yumi.resolver();
        // End timer
        escribirInforme(out, soluciones, 0);
    }
    return 0;
}
