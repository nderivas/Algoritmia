#!/bin/sh

# Práctica 1 - Algoritmia básica
# Cristina Embid Martínez (842102) y Nicolás de Rivas Morillo (843740)

# Compilación del código
make clean
make

# Pruebas
# Limpiamos archivos de pruebas antiguos
rm -rf pruebas/prueba[0-9]*.txt.huf
rm -rf pruebas/prueba[0-9]*.txt.copia

clear

for file in pruebas/prueba[0-9]*L[0-9]*.txt; do
    L=$(echo "$file" | grep -o "L[0-9]*")
    cp $file $file.copia
    echo "\n-- PRUEBA $file"
    echo "\nTiempo de codificación:"
    time ./bin/huf -c $file.copia
    echo "Tiempo de decodificación:"
    time ./bin/huf -d $file.copia.huf
    echo "Bytes del archivo original:"
    wc -c $file.copia
    echo "Bytes del archivo codificado:"
    wc -c $file.copia.huf
    if diff $file $file.copia > /dev/null; then
        echo "$file - SUPERADO"
    else
        echo "$file - FALLIDO"
    fi
    echo "\n-- PRUEBA $file LONGITUD ${L:1}"
    echo "\nTiempo de codificación:"
    time ./bin/huf -l ${L:1} -c $file.copia
    echo "Tiempo de decodificación:"
    time ./bin/huf -l ${L:1} -d $file.copia.huf
    echo "Bytes del archivo original:"
    wc -c $file.copia
    echo "Bytes del archivo codificado:"
    wc -c $file.copia.huf
    if diff $file $file.copia > /dev/null; then
        echo "$file - SUPERADO"
    else
        echo "$file - FALLIDO"
    fi
done
