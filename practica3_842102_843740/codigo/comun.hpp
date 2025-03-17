#pragma once

#include "Casilla.hpp"
#include <vector>

using Matriz = std::vector<std::vector<Casilla>>;
using Punto = std::pair<int, int>;

const static Punto c_INI(0, 0);
const static Punto c_FIN(0, 1);

static const unsigned c_CHECKPOINTS = 3;
