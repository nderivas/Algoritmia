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
    NodoHuff(char c, unsigned f = 0, NodoHuff *z = nullptr, NodoHuff *u = nullptr)
        : byte(c), frecuencia(f), cero(z), uno(u) {}
};

// Comparador para la cola de prioridades.
struct CompararHuff {
    bool operator()(const NodoHuff *uno, const NodoHuff *dos) {
        return uno->frecuencia > dos->frecuencia;
    }
};

// Cola de prioridades para la construcción del árbol.
using ColaPrio =
    std::priority_queue<NodoHuff *, std::vector<NodoHuff *>, CompararHuff>;

namespace trad {
std::string binToStr(char c);
char strToBin(std::string s);
} // namespace trad
