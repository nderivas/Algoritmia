/* Algoritmia básica - Práctica 1
 * Nicolás de Rivas Morillo (843740)
 * Cristina Embid Martínez (842102)
 */

#pragma once

#include <array>
#include <queue>
#include <string>
#include <vector>

using CountArr = std::array<unsigned, 256>;
using CodArr = std::array<std::string, 256>;

// Representa un nodo en el árbol.
class NodoHuff {
  public:
    char byte;           // carácter almacenado en el nodo
    unsigned frecuencia; // frecuencia del carácter
    NodoHuff *cero,
        *uno; // puntero al hijo izquierdo (cero), al hijo derecho (uno)

    // Constructor de la clase NodoHuff
    NodoHuff(char c, unsigned f = 0, NodoHuff *z = nullptr,
             NodoHuff *u = nullptr)
        : byte(c), frecuencia(f), cero(z), uno(u) {}
};

// Comparador para la cola de prioridades.
struct CompararHuffFrec {
    bool operator()(const NodoHuff *uno, const NodoHuff *dos) {
        return uno->frecuencia > dos->frecuencia;
    }
};

// Comparador de longitud
struct CompararHuffLong {
    bool operator()(const NodoHuff *uno, const NodoHuff *dos) {
        return uno->frecuencia < dos->frecuencia;
    }
};

// Colas de prioridades para la construcción del árbol.
using ColaFrec =
    std::priority_queue<NodoHuff *, std::vector<NodoHuff *>, CompararHuffFrec>;
using ColaLong =
    std::priority_queue<NodoHuff *, std::vector<NodoHuff *>, CompararHuffLong>;

namespace trad {
std::string binToStr(const char c);
char strToBin(const std::string s);
} // namespace trad
