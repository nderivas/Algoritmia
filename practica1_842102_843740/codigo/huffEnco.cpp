/* Algoritmia básica - Práctica 1
 * Nicolás de Rivas Morillo (843740)
 * Cristina Embid Martínez (842102)
 */
#include "huffEnco.hpp"

using namespace std;

/*
 * Conteo de la frecuencia de cada carácter en un archivo de entrada
 * @param in archivo de entrada 
 */
void HuffEnco::contarFrec(std::ifstream &in) {
    char c;
    while (in.get(c)) {
        frecuencias[c]++;
    }
}
 

void HuffEnco::rellenarCola() {
    for (char i = 0; i < frecuencias.size(); ++i) {
        if (frecuencias[i] != 0) {
            NodoHuff *nuevo = new NodoHuff(i, frecuencias[i]);
            cola.push(nuevo);
        }
    }
    numCods = cola.size();
}


void HuffEnco::generarTrie() {
    while (cola.size() > 1) {
        NodoHuff *cero = cola.top();
        cola.pop();
        NodoHuff *uno = cola.top();
        cola.pop();
        unsigned frec = cero->frecuencia + uno->frecuencia;
        NodoHuff *padre = new NodoHuff(0, frec, cero, uno);
        cola.push(padre);
    }
    raiz = cola.top();
}

void HuffEnco::rellenarCodigos(NodoHuff *ptr, const string &cod) {
    if (ptr->cero == nullptr && ptr->uno == nullptr)
        codigos[ptr->byte] = cod;
    else {
        if (ptr->cero != nullptr)
            rellenarCodigos(ptr->cero, cod + '0');
        else
            rellenarCodigos(ptr->uno, cod + '1');
    }
}

void HuffEnco::escribirArbol(std::ofstream &out) {
    out << numCods;
    for (char b = 0; b < codigos.size(); ++b) {
        char relleno = 8 - (codigos[b].size() % 8);
        out << b << relleno;
        auto s = codigos[b];
        s.append(relleno, '0');
        out << trad::strToBin(s);
    }
}

void HuffEnco::escribirString(const std::string &s, std::ofstream &out) {
    for (unsigned i = 0; i < s.size(); ++i) {
        auto substr = s.substr(i, 8);
        int dif = 8 - substr.size();
        char c = trad::strToBin(substr);
        // Lo que se ponga al final da igual, llegará un punto que nos
        // quedaremos sin árbol, ahí sabemos que ha acabado el archivo,
        // rellanamos con lo que sea
        // NUEVO:
        c = c << dif;
        // ANTIGUO:
        // for (int j = 0; j < dif; ++j) {
        //     c = c << 1;
        //     c -= substr[substr.size() - 1] - '1';
        // }
        out << c;
    }
}

void HuffEnco::escribir(std::ifstream &in, std::ofstream &out) {
    escribirArbol(out);
    char c;
    string s = "";
    const unsigned max = 800;
    while (in.get(c)) {
        s += codigos[c];
        if (s.size() >= max) {
            escribirString(s.substr(0, max), out);
            if (s.size() != max)
                s = s.substr(max);
        }
    }
    escribirString(s, out);
}
