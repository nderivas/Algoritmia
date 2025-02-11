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

for file in pruebas/prueba[0-9]*.txt; do
    cp $file $file.copia
    ./bin/huff -c $file.copia
    ./bin/huff -d $file.copia.huf
    if diff $file $file.copia > /dev/null; then
        echo "$file - SUPERADO"
    else
        echo "$file - FALLIDO"
    fi
done
