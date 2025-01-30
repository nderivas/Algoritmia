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
string trad::binToStr(char c) {
    std::string temp = "", res = "";
    while (c != 0) {
        temp += c % 2 == 0 ? '0' : '1';
        c /= 2;
    }
    // Invierte el orden de los bits almacenados en 'temp'
    for (auto it = temp.rbegin(); it != temp.rend(); ++it) {
        res += *it;
    }
    return res;
}

/*
 * Convierte una cadena de bits en un carácter
 * @param s cadena binaria a convertir.
 * @return carácter correspondiente al valor binario de la cadena.
 */
char trad::strToBin(std::string s) {
    char res = 0;
    for (auto it = s.cbegin(); it != s.cend(); ++it) {
        res = res << 1;
        res += *it - '0';
    }
    return res;
}
