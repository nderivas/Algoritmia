#!/bin/sh
[[ -f bin/recorridosYumi ]] || make

clear
for f in pruebas/prueba*.txt; do
    echo "--- Prueba: $f"
    time bin/recorridosYumi "$f" $f"_resultados.txt"
done
echo "Pruebas terminadas"
