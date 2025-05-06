#!/bin/sh
[[ -d bin ]] || mkdir bin
[[ -f bin/transporte ]] || make

/bin/rm -rf ./pruebas/*_resultados.txt
clear

for f in ./pruebas/prueba*.txt; do
    echo "--- Prueba: $f"
    bin/transporte "$f" "${f}_resultados.txt"
done
for f in ./pruebas/prueba*.dat; do
    echo "--- Prueba: $f"
    time glpsol --model programacionLinealPr4.mod --data "$f" -o "${f}_resultados.dat" > /dev/null
done
echo "Pruebas terminadas"

read -p "¿Enseñar resultados por pantalla? (s/n) " respuesta
[[ $respuesta != "s" ]] && exit 0

for f in ./pruebas/*_resultados.txt; do
    echo "--- Salida: $f"
    cat "$f"
done
for f in ./pruebas/*_resultados.dat; do
    echo "--- Salida: $f"
    cat "$f" | grep "Objective:"
done
