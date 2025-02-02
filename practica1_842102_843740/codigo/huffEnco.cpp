/* Algoritmia básica - Práctica 1
 * Nicolás de Rivas Morillo (843740)
 * Cristina Embid Martínez (842102)
 */

#include "huffEnco.hpp"
#include <iostream>

using namespace std;

void HuffEnco::codificar() {
    ifstream input(inFile, ios::binary | ios::in);
    if (!input.is_open()) {
        cout << "¡No he conseguido abrir el archivo original!" << endl;
        return;
    }
    contarFrec(input);
    rellenarCola();
    generarTrie();
    rellenarCodigos(raiz, "");
    input.clear();
    input.seekg(0, ios::beg);
    ofstream output(outFile, ios::binary | ios::out | ios::trunc);
    escribir(input, output);
    input.close();
    output.close();
}

/*
 * Conteo de la frecuencia de cada carácter en un archivo de entrada
 * @param in archivo de entrada
 */
void HuffEnco::contarFrec(std::ifstream &in) {
    char c;
    while (in.get(c))
        frecuencias[c]++;
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
        rellenarCodigos(ptr->cero, cod + '0');
        rellenarCodigos(ptr->uno, cod + '1');
    }
}

void HuffEnco::escribirArbol(std::ofstream &out) {
    out.write(&numCods, 1);
    for (char b = 0; b < codigos.size(); ++b) {
        char relleno = 8 - (codigos[b].size() % 8);
        if (!codigos[b].empty()) {
            out.write(&b, 1);
            auto s = codigos[b];
            char tam = s.size();
            out.write(&tam, 1);
            escribirString(string(8 - tam % 8, '0') + s, out);
        }
    }
}

void HuffEnco::escribirString(const std::string &s, std::ofstream &out) {
    char dif;
    for (unsigned i = 0; i < s.size(); i = i + 8) {
        auto substr = s.substr(i, 8);
        char c = trad::strToBin(substr);
        dif = 8 - substr.size();
        c = c << dif;
        out.write(&c, 1);
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
    char relleno = static_cast<char>(8 - (s.size() % 8));
    out.write(&relleno, 1);
}
