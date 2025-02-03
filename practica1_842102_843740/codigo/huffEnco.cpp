/* Algoritmia básica - Práctica 1
 * Nicolás de Rivas Morillo (843740)
 * Cristina Embid Martínez (842102)
 */

#include "huffEnco.hpp"
#include <iostream>

using namespace std;

/*
 * Función principal para codificar el archivo <inFile> en el archivo <outFile>
 * @param ---
 */
void HuffEnco::codificar() {
    ifstream input(inFile, ios::binary | ios::in); // Abrir archivo
    if (!input.is_open()) {
        cout << "¡No he conseguido abrir el archivo original!" << endl;
        return;
    }
    contarFrec(input); // LLega al final del archivo: eof = verdad
    rellenarCola();
    generarTrie();
    rellenarCodigos(raiz, "");
    input.clear();            // Desactiva el aviso de final de archivo
    input.seekg(0, ios::beg); // Reinicia el cursor al comienzo del archivo
    ofstream output(outFile, ios::binary | ios::out | ios::trunc);
    escribir(input, output); // Codificación
    // Cierre de archivos abiertos
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
        frecuencias[static_cast<unsigned char>(c)]++;
}

/*
 * Rellenado de la cola de prioridad con los nodos correspondientes a cada
 * carácter que aparece
 * @param ---
 */
void HuffEnco::rellenarCola() {
    for (int i = 0; i < frecuencias.size(); ++i) {
        if (frecuencias[static_cast<unsigned char>(i)] != 0) {
            NodoHuff *nuevo =
                new NodoHuff(static_cast<char>(i), frecuencias[i]);
            cola.push(nuevo);
        }
    }
    numCods = cola.size();
}

/*
 * Generación del árbol de Huffman a partir de la cola de prioridad se guardará
 * la raíz
 * @param ---
 */
void HuffEnco::generarTrie() {
    while (cola.size() > 1) {
        // Sacamos los 2 más bajos de la lista
        NodoHuff *cero = cola.top();
        cola.pop();
        NodoHuff *uno = cola.top();
        cola.pop();
        // Lo unimos bajo un padre común
        unsigned frec = cero->frecuencia + uno->frecuencia;
        NodoHuff *padre = new NodoHuff(0, frec, cero, uno);
        // Los añadimos a la lista unidos
        cola.push(padre);
    }
    raiz = cola.top(); // El último nodo es la raíz
}

/*
 * Rellena recursivamente el array de códigos en función del árbol de Huffman
 * generado
 * @param ptr puntero a nodo actual, cod código del nodo actual
 */
void HuffEnco::rellenarCodigos(NodoHuff *ptr, const string &cod) {
    if (ptr->cero == nullptr && ptr->uno == nullptr) // Si estoy en una hoja
        codigos[static_cast<unsigned char>(ptr->byte)] =
            ptr == raiz ? "0" : cod;
    else { // Si no, llamadas recursivas añadiendo al código
        rellenarCodigos(ptr->cero, cod + '0');
        rellenarCodigos(ptr->uno, cod + '1');
    }
}

/*
 * Codifica y escribe el árbol de Huffman al archivo comprimido
 * @param out flujo de datos del archivo de salida
 */
void HuffEnco::escribirArbol(std::ofstream &out) {
    out.write(&numCods, 1); // Primer byte del archivo número de hojas del árbol
    for (int b = 0; b < codigos.size(); ++b) { // Para cada byte
        char relleno = 8 - (codigos[static_cast<unsigned char>(b)].size() % 8);
        // Si no tiene el código vacío, es decir, aparece en el archivo
        if (!codigos[static_cast<unsigned char>(b)].empty()) {
            char temp = static_cast<char>(b);
            out.write(&temp, 1); // Byte original
            auto s = codigos[static_cast<unsigned char>(b)];
            char tam = s.size();
            // Tamaño del código, no puede ser más de 255 puesto que codificamos
            // bytes, |C| -1 = 256 - 1 = 255 => solo necesitamos un byte
            out.write(&tam, 1);
            // Escritura del código
            escribirString(string(8 - tam % 8, '0') + s, out);
        }
    }
}

/*
 * Codifica y escribe un string en el archivo comprimido
 * @param s string a codificar, out flujo de datos del archivo de salida
 */
void HuffEnco::escribirString(const std::string &s, std::ofstream &out) {
    char dif; // Bits de relleno (para el final del archivo)
    // Mientras tenga bits, se toman de byte en byte (menos el último)
    for (unsigned i = 0; i < s.size(); i = i + 8) {
        // Se toma el byte y se pasa a binario
        auto substr = s.substr(i, 8);
        char c = trad::strToBin(substr);
        dif = 8 - substr.size();
        // Se añade el relleno necesario
        c = c << dif;
        // Se escribe el bit
        out.write(&c, 1);
    }
}

/*
 * Codifica y escribe los datos del archivo de entrada en el de salida
 * @param in flujo de datos del archivo de entrada, out flujo de datos del
 *        archivo de salida
 */
void HuffEnco::escribir(std::ifstream &in, std::ofstream &out) {
    escribirArbol(out);
    char c;
    string s = "";            // Buffer
    const unsigned max = 800; // Máximo antes del flush
    while (in.get(c)) {
        s += codigos[static_cast<unsigned char>(c)]; // Se añaden códigos
        if (s.size() >= max) { // Si tenemos que hacer flush
            escribirString(s.substr(0, max), out);
            if (s.size() != max)
                s = s.substr(max); // Ajuste del buffer
        }
    }
    // Se escribe el resto
    escribirString(s, out);
    // Se añade el relleno del último byte al final para saber hasta donde leer
    char relleno = static_cast<char>((8 - (s.size() % 8)) % 8);
    out.write(&relleno, 1);
}
