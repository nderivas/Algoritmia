// Práctica 3 - Algoritmia básica
// Nicolás de Rivas Morillo (843740) y Cristina Embid Martínez (842102)
#include "MeetYumi.hpp"
#include "Yumi.hpp"
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>

using namespace std;

// Escribe resultados en el archivo de salida
void escribirInforme(std::ostream &out, unsigned sol, double tiempo,
                     unsigned solMeet = 0, double tiempoMeet = 0) {
    if (solMeet == 0 && tiempoMeet == 0)
        out << sol << ' ' << fixed << setprecision(6) << tiempo << '\n';
    else
        out << sol << ' ' << fixed << setprecision(6) << tiempo << '\n'
            << "MeetInTheMiddle: " << solMeet << ' ' << fixed << setprecision(6)
            << tiempoMeet << endl;
}

int main(int argc, char **argv) {
    if (argc != 3 && argc != 4) { // Comprobación de argumentos introducidos
        cerr << "USO: ./recorridosYumi <pruebas.txt> <resultados.txt> [-mitm]"
             << endl;
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

        // Start timer
        auto tIni = clock();
        Yumi yumi(m, n, arr);
        unsigned soluciones = yumi.resolver().size();
        clock_t tFin = clock();
        double tot = static_cast<double>(tFin - tIni) / CLOCKS_PER_SEC;

        if (argc == 4 && static_cast<string>(argv[3]) == "-mitm") {
            // Start timer
            tIni = clock();
            MeetYumi meetYumi(m, n, arr);
            unsigned solucionesMeet = meetYumi.resolver();
            tFin = clock();
            double totMeet = static_cast<double>(tFin - tIni) / CLOCKS_PER_SEC;
            escribirInforme(out, soluciones, tot, solucionesMeet, totMeet);
        } else
            escribirInforme(out, soluciones, tot);
    }
    return 0;
}
