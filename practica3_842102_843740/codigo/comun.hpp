#pragma once

#include "Casilla.hpp"
#include <cmath>
#include <vector>

using Matriz = std::vector<std::vector<Casilla>>;
using Punto = std::pair<int, int>;

static const unsigned c_CHECKPOINTS = 3;

static int distancia(Punto a, Punto b) {
    return abs(a.first - b.first) + abs(a.second - b.second);
}
