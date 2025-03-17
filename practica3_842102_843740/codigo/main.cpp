#include "Yumi.hpp"
#include <fstream>
#include <iostream>

using namespace std;

void escribirInforme(std::ostream &out, unsigned sol, time_t tiempo) {
    out << sol << endl;
}

int main(int argc, char **argv) {
    if (argc != 3) {
        cerr << "USO: ./recorridosYumi <pruebas.txt> <resultados.txt>" << endl;
        exit(1);
    }
    ifstream in(argv[1]);
    ofstream out(argv[2]);
    if (!in.is_open() || !out.is_open()) {
        cerr << "Alguno de los archivos no existe." << endl;
        exit(1);
    }
    int n, m;
    array<Punto, c_CHECKPOINTS + 1> arr;
    arr[c_CHECKPOINTS] = c_FIN;
    while (!in.eof()) {
        in >> m >> n;
        for (unsigned i = 0; i < c_CHECKPOINTS; ++i)
            in >> arr[i].first >> arr[i].second;
        cout << "m: " << m << ", n: " << n << endl;
        for (unsigned i = 0; i < c_CHECKPOINTS + 1; ++i)
            cout << arr[i].first << "," << arr[i].second << " ";
        cout << endl;
        Yumi yumi(m, n, arr);
        // Start timer
        unsigned soluciones = yumi.resolver();
        // End timer
        escribirInforme(out, soluciones, 0);
    }
    return 0;
}
