#pragma once

#include <array>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

using CountArr = std::array<unsigned, 256>;
using CodArr = std::array<std::string, 256>;
using DecodArr = std::unordered_map<std::string, char>;

class NodoHuff {
  public:
    char byte;
    unsigned frecuencia;
    NodoHuff *cero, *uno;

    NodoHuff(char c, unsigned f, NodoHuff *z = nullptr, NodoHuff *u = nullptr)
        : byte(c), frecuencia(f), cero(z), uno(u) {}
};

class CompararHuff {
  public:
    bool comp(const NodoHuff *uno, const NodoHuff *dos) {
        return uno->frecuencia < dos->frecuencia;
    }
};

using ColaPrio =
    std::priority_queue<NodoHuff *, std::vector<NodoHuff *>, CompararHuff>;

namespace trad {
std::string binToStr(char c);
char strToBin(std::string s);
} // namespace trad
