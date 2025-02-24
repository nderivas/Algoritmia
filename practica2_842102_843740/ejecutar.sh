#!/bin/sh
source .venv/bin/activate

rm -rf /tmp/pruebas
[[ -e /tmp/pruebas ]] || mkdir /tmp/pruebas

echo "Comienzan las pruebas"
for file in pruebas/test[0-9]*N[0-9]*.bmp; do
    echo "--- Prueba: $file"
    N=$(echo "$file" | grep -o "N[0-9]*")
    ./codigo/costuras ${N:1} $file /tmp
done
