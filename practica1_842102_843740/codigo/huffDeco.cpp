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

/*
 * Decodifica los contenido de inFile y los escribe en outFile.
 * @param ---
 */
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

/*
 * Introduce el byte c en el árbol de decodificación
 * con el código cod.
 * @param c es el byte a introducir en el árbol, cod
 * es el código correspondiente a c.
 */
void HuffDeco::introducirCodigo(char c, string cod) {
    NodoHuff *nodo = raiz;
    for (char i : cod) { // Recorremos el árbol
        // En cuanto no encontramos uno lo creamos
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

/*
 * Lee el árbol codificado en el fichero y lo construye.
 * @param in es el flujo de datos del fichero de entrada.
 */
void HuffDeco::leerArbol(ifstream &in) {
    char numCods, byte, tam, temp, numBytes;
    string buff;
    raiz = new NodoHuff(0); // Creamos la raíz
    in.read(&numCods, 1);   // Leemos el número de códigos
    if (numCods == 1) {     // TODO: Revisar
        in.read(&byte, 1);
        raiz->byte = byte;
        in.read(&tam, 1);
        in.read(&byte, 1);
    }
    for (char i = 0; i < numCods; ++i) {
        buff = "";
        in.read(&byte, 1); // Byte original
        in.read(&tam, 1);  // Longitud del código
        // Bytes que ocupa el código
        numBytes = ((8 - tam % 8) + tam) / 8; // TODO: Esto se puede simplificar
        for (char j = 0; j < numBytes; ++j) { // Leer bytes
            in.read(&temp, 1);
            string nuevoByte = trad::binToStr(temp);
            buff = buff + string(8 - nuevoByte.size(), '0') + nuevoByte;
        }
        // Quitar ceros iniciales
        buff = buff.substr(8 - tam % 8);
        introducirCodigo(byte, buff); // Introducir en el árbol
    }
}

/*
 * Avanza por el árbol según los pasos desde nodo y escribe los bytes
 * que encuentra si llega a alguna hoja.
 * @param nodo es el nodo desde el que partimos, pasos es un string con
 * las direcciones que tenemos que tomar, out es el flujo de datos de salida.
 */
void HuffDeco::avanzaYEscribe(NodoHuff *&nodo, const string pasos,
                              ofstream &out) {
    for (char i : pasos) { // Para cada paso
        // Avanzo por la rama correpondiente
        if (i == '0' && nodo->cero != nullptr)
            nodo = nodo->cero;
        else if (nodo->uno != nullptr)
            nodo = nodo->uno;
        // Si he llegado el final escribo el byte original y reinicio
        if (nodo->cero == nullptr && nodo->uno == nullptr) {
            out.write(&nodo->byte, 1);
            nodo = raiz;
        }
    }
}

/*
 * Decodifica los contenidos internos (no el árbol) del fichero.
 * Asume que in está en la posición correcta de los datos.
 * @param in es el flujo de datos de entrada, de donde decodificamos
 * out es el flujo de datos de salida, donde escribimos
 */
void HuffDeco::decodificarContenidos(ifstream &in, ofstream &out) {
    char c, extras;
    string cad = "", nuevoByte;
    NodoHuff *nodo = raiz;
    in.read(&extras, 1);
    while (in.read(&c, 1)) { // TODO: Hacer magia
        if (c != EOF) {
            avanzaYEscribe(nodo, cad, out);
            cad = "";
        }
        nuevoByte = trad::binToStr(c); // Pasamos a string
        // Ajustamos 0s iniciales
        nuevoByte = string(8 - nuevoByte.size(), '0') + nuevoByte;
        cad = cad + nuevoByte;
    }
    cad = cad.substr(0, cad.size() - extras);
    avanzaYEscribe(nodo, cad, out);
}
