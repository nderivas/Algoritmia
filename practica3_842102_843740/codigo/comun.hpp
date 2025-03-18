#pragma once

// Práctica 3 - Algoritmia básica
// Nicolás de Rivas Morillo (843740) y Cristina Embid Martínez (842102)
#include "Casilla.hpp"
#include <vector>

using Matriz = std::vector<std::vector<Casilla>>;
using Punto = std::pair<int, int>;

const static Punto c_INI(0, 0); // Casilla de inicio
const static Punto c_FIN(0, 1); // Casilla de final

static const unsigned c_CHECKPOINTS = 3; // Número de checkpoints
