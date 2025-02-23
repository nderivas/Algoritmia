#!/bin/sh
source .venv/bin/activate

echo "Comienzan las pruebas"
for file in pruebas/test[0-9]*N[0-9]*.bmp; do
    echo "--- Prueba: $file"
    N=$(echo "$file" | grep -o "N[0-9]*")
    ./codigo/costuras ${N:1} $file $file.out.bmp
done
