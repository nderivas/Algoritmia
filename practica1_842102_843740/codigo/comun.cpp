/* Algoritmia básica - Práctica 1
 * Nicolás de Rivas Morillo (843740)
 * Cristina Embid Martínez (842102)
 */

#include "comun.hpp"

using namespace std;

/*
 * Convierte un carácter en su representación binaria como string
 * @param c carácter a convertir.
 * @return String representando los bits de 'c'.
 */
string trad::binToStr(const char c) {
    std::string res = "";
    unsigned char aux = c;
    while (aux != 0) {
        res = (aux % 2 ? '1' : '0') + res;
        aux /= 2;
    }
    return res;
}

/*
 * Convierte una cadena de bits en un carácter
 * @param s cadena binaria a convertir.
 * @return carácter correspondiente al valor binario de la cadena.
 */
char trad::strToBin(const std::string s) {
    unsigned char res = 0;
    for (auto e : s) {
        res = res << 1;
        res += e - '0';
    }
    return res;
}
