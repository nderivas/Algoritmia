#include "minimizador.hpp"
#include <ctime>
#include <fstream>
#include <iostream>
#include <vector>

// Práctica 4 - Algoritmia básica
// Cristina Embid Martínez (842102) y Nicolás de Rivas Morillo (843740)

using namespace std;

// Representa la entrada de un problema
struct Entrada {
  unsigned capacidadTren, final;
  std::vector<Pedido> Pedidos;
};

// Lee todas las entradas del archivo provisto
vector<Entrada> leerEntrada(const string &nombreArchivo) {
  auto in = ifstream(nombreArchivo);
  vector<Entrada> v = {};
  while (!in.eof()) {
    Entrada entrada;
    unsigned n;
    in >> entrada.capacidadTren >> entrada.final >> n;
    if (in.eof())
      break;
    for (unsigned i = 0; i < n; ++i) {
      unsigned ini, fin, pasajeros;
      in >> ini >> fin >> pasajeros;
      entrada.Pedidos.push_back(Pedido(ini, fin, pasajeros));
    }
    v.push_back(entrada);
  }
  return v;
}

// Escribe la salida por el flujo de datos out "resultado tiempo"
inline void escribirSalida(ofstream &out, unsigned resultado, double tiempo) {
  out << resultado << ' ' /*<< fixed << setprecision(3)*/ << tiempo << endl;
}

// Función principal
int main(int argc, char **argv) {
  // Comprobaciones de argumentos
  if (argc < 3) {
    cerr << "Uso: " << argv[0] << " <archivo_entrada> <archivo_salida>" << endl;
    return 1;
  }

  // I/O
  auto problemas = leerEntrada(argv[1]);
  auto out = ofstream(argv[2]);

  // Para cada problema...
  for (auto &problema : problemas) {
    // Lo solucionamos
    auto tIni = clock(); // Inicio del reloj
    // Constructor del minimizador
    Minimizador minimizador(Tren(problema.capacidadTren, problema.final),
                            problema.Pedidos);
    // Minimizar
    unsigned resultado = minimizador.minimizar();
    auto tFin = clock(); // Final del reloj
    // Tiempo final
    auto t = static_cast<double>(tFin - tIni) / CLOCKS_PER_SEC;
    escribirSalida(out, resultado, t); // Escribimos la salida
  }

  return 0;
}
