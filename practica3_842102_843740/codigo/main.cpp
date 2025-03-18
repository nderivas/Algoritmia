// Práctica 3 - Algoritmia básica
// Nicolás de Rivas Morillo (843740) y Cristina Embid Martínez (842102)
#include "Yumi.hpp"
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>

using namespace std;

// Escribe resultados en el archivo de salida
void escribirInforme(std::ostream &out, unsigned sol, double tiempo) {
    out << sol << ' ' << fixed << setprecision(6) << tiempo << endl;
}

int main(int argc, char **argv) {
    if (argc != 3) { // Comprobación de argumentos introducidos
        cerr << "USO: ./recorridosYumi <pruebas.txt> <resultados.txt>" << endl;
        exit(1);
    }
    ifstream in(argv[1]);  // Archivo de pruebas
    ofstream out(argv[2]); // Archivo de resultados
    if (!in.is_open() || !out.is_open()) {
        cerr << "Alguno de los archivos no existe." << endl;
        exit(1);
    }
    int n, m;
    array<Punto, c_CHECKPOINTS + 1> arr;
    arr[c_CHECKPOINTS] = c_FIN; // Checkpoint final (0,1)
    while (!in.eof()) {
        in >> m >> n; // Lee valores m y n
        if (in.eof())
            break;
        for (unsigned i = 0; i < c_CHECKPOINTS; ++i)
            in >> arr[i].first >>
                arr[i].second; // Coordenadas de los checkpoints

        Yumi yumi(m, n, arr);
        // Start timer
        auto tIni = clock();
        unsigned soluciones = yumi.resolver();
        clock_t tFin = clock();
        double tot = static_cast<double>(tFin - tIni) / CLOCKS_PER_SEC;
        escribirInforme(out, soluciones, tot);
    }
    return 0;
}
