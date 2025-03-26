#!/bin/sh
[[ -f bin/recorridosYumi ]] || make

/bin/rm -rf ./pruebas/*_resultados.txt
clear

[[ $1 == "-n" ]] || flag="-mitm"

for f in ./pruebas/prueba*.txt; do
    echo "--- Prueba: $f"
    time bin/recorridosYumi "$f" $f"_resultados.txt" $flag
done
echo "Pruebas terminadas\n"

read -p "¿Enseñar resultados por pantalla? (s/n) " respuesta
[[ $respuesta != "s" ]] && exit 0

for f in ./pruebas/*_resultados.txt; do
    echo "--- Salida: $f"
    cat "$f"
done
