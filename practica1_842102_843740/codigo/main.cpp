/* Algoritmia básica - Práctica 1
 * Nicolás de Rivas Morillo (843740)
 * Cristina Embid Martínez (842102)
 */

#include "huffDeco.hpp"
#include "huffEnco.hpp"
#include <iostream>

using namespace std;

int main(int argc, char *argv[]) {
    if (argc != 3) { // Comprobación de llamada
        cout << "Uso:\n\thuf -[cd] <fichero>" << endl;
        return 1;
    }
    if (static_cast<string>(argv[1]) == "-c") { // Enco
        HuffEnco enco(argv[2], static_cast<string>(argv[2]) + ".huf");
        enco.codificar();
    } else if (static_cast<string>(argv[1]) == "-d") { // Deco
        auto s = static_cast<string>(argv[2]);
        HuffDeco deco(argv[2], s.substr(0, s.size() - 4));
        deco.decodificar();
    } else { // Error
        cout << "Opción incorrecta. Uso:\n\thuf -[cd] <fichero>" << endl;
        return 1;
    }
    return 0;
}
