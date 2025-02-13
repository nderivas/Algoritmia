/* Algoritmia básica - Práctica 1
 * Nicolás de Rivas Morillo (843740)
 * Cristina Embid Martínez (842102)
 */

#include "huffEnco.hpp"
#include <cmath>
#include <iostream>
#include <vector>

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
    if (estaVacio) {
        if (L > 0) { // L es la longitud máxima de codificación
            ajustarFrecuencias();
            generarTrieLongitudes();
        } else {
            rellenarCola();
            generarTrieFrecuencias();
        }
        rellenarCodigos(raiz, "");
    }
    input.clear();            // Desactiva el aviso de final de archivo
    input.seekg(0, ios::beg); // Reinicia el cursor al comienzo del archivo
    ofstream output(outFile, ios::binary | ios::out | ios::trunc);
    if (estaVacio)
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
    unsigned i = 0;
    while (in.get(c)) {
        i++;
        frecuencias[static_cast<unsigned char>(c)]++;
    }
    estaVacio = i > 1;
}

/*
 * Calcula el valor de la desigualdad de Kraft-McMillan.
 * La fórmula utilizada es:
 *      Σr^(li) con r = 0.5
 *
 * @param  frecs Vector de pares donde cada par contiene un carácter y su
 * longitud
 * @return double Suma de la desigualdad
 */
inline double calcularKM(const vector<pair<char, unsigned>> &frecs) {
    double res = 0;
    for (auto e : frecs) {
        res += pow(0.5, e.second);
    }
    return res;
}

/*
 * Ordena los pares carácter-frecuencia de mayor a menor frecuencia
 */
inline void ordenar(vector<pair<char, unsigned>> &frecs) {
    unsigned auxunsigned;
    char auxchar;
    for (unsigned i = 0; i < frecs.size(); ++i)
        for (unsigned j = i + 1; j < frecs.size(); ++j)
            if (frecs[i].second < frecs[j].second) {
                auxunsigned = frecs[i].second;
                auxchar = frecs[i].first;
                frecs[i].second = frecs[j].second;
                frecs[i].first = frecs[j].first;
                frecs[j].second = auxunsigned;
                frecs[j].first = auxchar;
            }
}

/*
 * Ajusta las frecuencias de los caracteres para cumplir la desigualdad
 * de Kraft-McMillan
 */
void HuffEnco::ajustarFrecuencias() {
    // Crear el vector ordenado
    vector<pair<char, unsigned>> frecs;
    frecs.reserve(frecuencias.size());
    // Llenar vector con los caracteres que tienen frecuencias != 0
    for (unsigned i = 0; i < frecuencias.size(); ++i)
        if (frecuencias[i] != 0)
            frecs.push_back(pair<char, unsigned>(i, frecuencias[i]));
    // Ordenar los pares
    ordenar(frecs);
    // Paso 1: Ajustar las frecuencias que exceden la longitud máxima L
    unsigned i = 0;
    while (i < frecs.size() && frecs[i].second >= L) {
        // Si la frecuencia es mayor que L, se limita a L
        frecs[i].second = frecs[i].second > L ? L : frecs[i].second;
        i++;
    }
    // Paso 2: Reducir frecuencias hasta km <= 1
    double km = calcularKM(frecs); // Calcular valor actual
    while (i < frecs.size() && !(km <= 1)) {
        if (frecs[i].second == L)
            i++; // Si ya alcanzó longitud máxima, continuar con el
                 // siguiente
        else {
            double potenciaActual = pow(0.5, frecs[i].second);
            frecs[i].second++; // Aumentamos longitud
            km = km - potenciaActual + potenciaActual / 2;
        }
    }
    // Paso 3: Reducir longitudes si es posible
    unsigned j = 0;
    while (j < frecs.size()) {
        double potenciaActual = pow(0.5, frecs[j].second);
        auto tempkm = km - potenciaActual + potenciaActual * 2;
        if (tempkm <= 1) {
            km = tempkm;       // Actualizamos Kraft-McMillan
            frecs[j].second--; // Reducimos longitud
        } else
            j++; // Si no podemos reducir, pasamos al siguiente
    }
    for (auto e : frecs)
        colaLongitudes.push(new NodoHuff(e.first, e.second));
    numCods = colaLongitudes.size();
}

/*
 * Generación del árbol de Huffman a partir de la cola de prioridad se
 * guardará la raíz
 * @param ---
 */
void HuffEnco::generarTrieLongitudes() {
    while (colaLongitudes.size() > 1) {
        // Sacamos los 2 más altos de la lista
        NodoHuff *cero = colaLongitudes.top();
        colaLongitudes.pop();
        NodoHuff *uno = colaLongitudes.top();
        colaLongitudes.pop();
        // Lo unimos bajo un padre común
        unsigned frec = cero->frecuencia - 1;
        NodoHuff *padre = new NodoHuff(0, frec, cero, uno);
        // Los añadimos a la lista unidos
        colaLongitudes.push(padre);
    }
    raiz = colaLongitudes.top(); // El último nodo es la raíz
}

/*
 * Rellenado de la cola de prioridad con los nodos correspondientes a
 * cada carácter que aparece
 * @param ---
 */
void HuffEnco::rellenarCola() {
    for (unsigned i = 0; i < frecuencias.size(); ++i) {
        if (frecuencias[static_cast<unsigned char>(i)] != 0) {
            NodoHuff *nuevo =
                new NodoHuff(static_cast<char>(i), frecuencias[i]);
            colaFrecuencias.push(nuevo);
        }
    }
    numCods = colaFrecuencias.size();
}

/*
 * Generación del árbol de Huffman a partir de la cola de prioridad se
 * guardará la raíz
 * @param ---
 */
void HuffEnco::generarTrieFrecuencias() {
    while (colaFrecuencias.size() > 1) {
        // Sacamos los 2 más bajos de la lista
        NodoHuff *cero = colaFrecuencias.top();
        colaFrecuencias.pop();
        NodoHuff *uno = colaFrecuencias.top();
        colaFrecuencias.pop();
        // Lo unimos bajo un padre común
        unsigned frec = cero->frecuencia + uno->frecuencia;
        NodoHuff *padre = new NodoHuff(0, frec, cero, uno);
        // Los añadimos a la lista unidos
        colaFrecuencias.push(padre);
    }
    raiz = colaFrecuencias.top(); // El último nodo es la raíz
}

/*
 * Rellena recursivamente el array de códigos en función del árbol de
 * Huffman generado
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
    out.write(&numCods,
              1); // Primer byte del archivo número de hojas del árbol
    for (unsigned b = 0; b < codigos.size(); ++b) { // Para cada byte
        // Si no tiene el código vacío, es decir, aparece en el archivo
        if (!codigos[static_cast<unsigned char>(b)].empty()) {
            char temp = static_cast<char>(b);
            out.write(&temp, 1); // Byte original
            auto s = codigos[static_cast<unsigned char>(b)];
            char tam = s.size();
            // Tamaño del código, no puede ser más de 255 puesto que
            // codificamos bytes, |C| -1 = 256 - 1 = 255 => solo
            // necesitamos un byte
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
 * @param in flujo de datos del archivo de entrada, out flujo de datos
 * del archivo de salida
 */
void HuffEnco::escribir(std::ifstream &in, std::ofstream &out) {
    escribirArbol(out);
    char c = 0;
    string s = "";            // Buffer
    const unsigned max = 800; // Máximo antes del flush
    unsigned cursorExtras = static_cast<unsigned>(out.tellp());
    out.write(&c, 1); // Escribo un byte de "basura"
    while (in.get(c)) {
        s += codigos[static_cast<unsigned char>(c)]; // Se añaden códigos
        if (s.size() >= max) { // Si tenemos que hacer flush
            string buffAEscribir = s.substr(0, max);
            escribirString(buffAEscribir, out);
            s = s.substr(max); // Ajuste del buffer
        }
    }
    // Se escribe el resto
    escribirString(s, out);
    // Se añade el relleno del último byte al final para saber hasta
    // donde leer
    char relleno = static_cast<char>((8 - (s.size() % 8)) % 8);
    out.seekp(cursorExtras, ios::beg);
    out.write(&relleno, 1);
}
