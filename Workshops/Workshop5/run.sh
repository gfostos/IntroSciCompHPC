#!/bin/bash

# Asegurarse de que las variables de entorno de TBB estén cargadas
# Esto es CRUCIAL si no las tienes configuradas globalmente en .bashrc y has iniciado una nueva sesión.
# Si ya las tienes en .bashrc y has hecho 'source ~/.bashrc', puedes omitir esta sección.
# De lo contrario, asegúrate de que $HOME/tbb_local sea la ruta correcta donde instalaste TBB.
# --- INICIO DE CONFIGURACIÓN DE ENTORNOS TBB ---
export TBB_ROOT="/home/gostos/Downloads/oneTBB"
export CPATH=$TBB_ROOT/include:$CPATH
export LIBRARY_PATH=$TBB_ROOT/lib:$LIBRARY_PATH
export LD_LIBRARY_PATH=$TBB_ROOT/lib:$LD_LIBRARY_PATH
# --- FIN DE CONFIGURACIÓN DE ENTORNOS TBB ---

# Nombre del ejecutable y fuente
EXEC=parallel_metrics_algs
SRC=${EXEC}.cpp

# Compilación
echo "Compilando..."
# Añadir -I para los includes y -L para las librerías, y enlazar con -ltbb y -ltbbbind_2_0
# El '_2_0' al final de tbbbind puede variar, verifica en $TBB_ROOT/lib si es tbbbind.so o tbbbind_2_0.so
g++ -std=c++17 -O3 $SRC -o $EXEC -I$TBB_ROOT/include -L$TBB_ROOT/lib -ltbb -ltbbbind_2_0
if [ $? -ne 0 ]; then
    echo "Error de compilación."
    exit 1
fi

# Configuración
VECTOR_SIZE=200000000
POLICIES=("seq" 0 "par" 1 "par_unseq" 2)
MAX_THREADS=$(nproc)   # Detecta número total de hilos disponibles

# Crear carpeta y archivo de resultados
mkdir -p resultados
OUTPUT="resultados/datos.txt"
echo "policy threads time result" > $OUTPUT   # Encabezado

# Ejecutar todas las combinaciones
for (( i=0; i<${#POLICIES[@]}; i+=2 )); do
    POLICY_NAME=${POLICIES[i]}
    POLICY_VAL=${POLICIES[i+1]}

    # La política secuencial (0) siempre se ejecuta con un "número de hilos" de 1 para fines de reporte
    if [ "$POLICY_VAL" -eq 0 ]; then
        echo "Ejecutando: $POLICY_NAME (id=$POLICY_VAL), Threads=16"
        ./$EXEC $VECTOR_SIZE 1 $POLICY_VAL >> $OUTPUT
    else
        for (( THREADS=1; THREADS<=MAX_THREADS; THREADS++ )); do
            echo "Ejecutando: $POLICY_NAME (id=$POLICY_VAL), Threads=$THREADS"
            ./$EXEC $VECTOR_SIZE $THREADS $POLICY_VAL >> $OUTPUT
        done
    fi
done

echo "Ejecuciones completas. Datos guardados en $OUTPUT"