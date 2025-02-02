/* Algoritmia básica - Práctica 1
 * Nicolás de Rivas Morillo (843740)
 * Cristina Embid Martínez (842102)
 */
#include "huffDeco.hpp"
#include "comun.hpp"
#include <__config>
#include <iostream>
using namespace std;

// TODO: Fichero vacío
// TODO: Fichero con un solo carácter

void HuffDeco::introducirCodigo(char c, string cod) {
    NodoHuff *nodo = raiz;
    for (char i : cod) {
        if (i == '0') {
            if (nodo->cero == nullptr)
                nodo->cero = new NodoHuff(c);
            nodo = nodo->cero;
        } else {
            if (nodo->uno == nullptr)
                nodo->uno = new NodoHuff(c);
            nodo = nodo->uno;
        }
    }
}

void HuffDeco::leerArbol(ifstream& in) {
    char numCods, byte, tam, temp, numBytes;
    string buff;
    raiz = new NodoHuff(0);
    in.read(&numCods, 1);
    if (numCods == 1) {
        in.read(&byte, 1);
        raiz->byte = byte;
        in.read(&tam, 1);
        in.read(&byte, 1);
    }
    for (char i = 0; i < numCods; ++i) {
        buff = "";
        in.read(&byte, 1);
        in.read(&tam, 1);
        numBytes = ((8 - tam % 8) + tam) / 8;
        for (char j = 0; j < numBytes; ++j) {
            in.read(&temp, 1);
            buff = buff + trad::binToStr(temp);
        }
        buff = string(tam - buff.size(), '0') + buff;
        introducirCodigo(byte, buff);
    }
}

void HuffDeco::decodificarContenidos(ifstream& in, ofstream& out) {
    char c, extras;
    string cad;
    NodoHuff *nodo = raiz;
    unsigned inicioDatos = static_cast<unsigned>(in.tellg());
    in.seekg(-1, ios::end);
    unsigned fin = static_cast<unsigned>(in.tellg());
    in.read(&extras, 1);
    in.seekg(inicioDatos, ios::beg);
    while(static_cast<unsigned>(in.tellg()) < fin - 1) {
        in.read(&c, 1);
        cad = trad::binToStr(c);
        cad = string(8 - cad.size(), '0') + cad;
        for(char i : cad) {
            if (i == '0' && nodo->cero != nullptr)
                nodo = nodo->cero;
            else if (nodo->uno != nullptr)
                nodo = nodo->uno;
            if (nodo->cero == nullptr && nodo->uno == nullptr) {
                out.write(&nodo->byte, 1);
                nodo = raiz;
            }
        }
    }
    in.read(&c, 1);
    cad = trad::binToStr(c);
    cad = string(8 - cad.size(), '0') + cad;
    cad = cad.substr(0, 8 - extras);
    for(char i : cad) {
        if (i == '0' && nodo->cero != nullptr)
            nodo = nodo->cero;
        else if (nodo->uno != nullptr)
            nodo = nodo->uno;
        if(nodo->cero == nullptr && nodo->uno == nullptr) {
            out.write(&nodo->byte, 1);
            nodo = raiz;
        }
    }
}

void HuffDeco::decodificar() {
    // Abrir los dos
    ifstream input(inFile, ios::binary | ios::in);
    if (!input.is_open()) {
        cout << "¡No he conseguido abrir el archivo codificado!" << endl;
        return;
    }
    // leerArbol
    leerArbol(input);
    // leerFichero
    ofstream output(outFile, ios::out | ios::trunc);
    decodificarContenidos(input, output);
    input.close();
    output.close();
}
