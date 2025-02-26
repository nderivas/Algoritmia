#!/bin/sh

# Instalar dependencias si no estan ya
[[ -e .venv ]] || ./dependencias.sh

# Activar el entorno virtual
source .venv/bin/activate

# Limpiar datos de pruebas anteriores
rm -rf /tmp/pruebas tiempos.log
[[ -e /tmp/pruebas ]] || mkdir /tmp/pruebas

# Código de pruebas
clear
echo "Comienzan las pruebas"
for file in pruebas/test[0-9]*N[0-9]*.bmp; do
    echo "--- Prueba: $file"
    echo "--- Prueba: $file" >> tiempos.log
    N=$(echo "$file" | grep -o "N[0-9]*")
    ./codigo/costuras ${N:1} $file /tmp
done
echo "Pruebas terminadas los resultados estan en /tmp/pruebas"
