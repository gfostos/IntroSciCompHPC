#!/bin/bash
#SBATCH --job-name=omp_perf_test   # Nombre del trabajo
#SBATCH --output=results/output_%A_%a.csv # Salida: %A=job_id, %a=array_task_id. Usamos .csv para indicar el formato.
#SBATCH --error=results/error_%A_%a.err   # Errores
#SBATCH --partition=16threads          # ¡Importante! Reemplaza con el nombre de tu partición
#SBATCH --nodes=1                  # Las aplicaciones OpenMP se ejecutan en un solo nodo
#SBATCH --ntasks=1                 # Una sola tarea/proceso para la aplicación OpenMP principal

# --- Parametrización del número de hilos usando SLURM_ARRAY_TASK_ID ---
# Definimos el rango de hilos a probar. Por ejemplo, de 1 a 16.
# Asegúrate de que el valor máximo no exceda el número de CPUs lógicas disponibles en un solo nodo.
# Puedes ver los CPUs disponibles con `sinfo -o "%P %c"`.
# Por ejemplo, si tienes nodos con 64 CPUs (hilos lógicos), puedes ir hasta 64.
# Para pruebas iniciales, 1 a 16 o 1 a 32 es un buen comienzo.
#SBATCH --array=1-16

# --- Recursos por tarea ---
# Solicita a Slurm que asigne tantas CPUs (hilos lógicos) como SLURM_ARRAY_TASK_ID actual.
# Esto es crucial para que Slurm reserve los recursos correctamente.
#SBATCH --cpus-per-task=16

# --- Variables de Entorno para OpenMP ---
# Le dice a OpenMP cuántos hilos debe usar.
# Es VITAL que esta variable coincida con lo que solicitaste a Slurm (--cpus-per-task).
export OMP_NUM_THREADS=${SLURM_ARRAY_TASK_ID}

# Opcional pero recomendado para rendimiento: binding de hilos
# Esto ayuda a que los hilos permanezcan en los núcleos asignados, mejorando el uso de caché.
export OMP_PLACES=cores
export OMP_PROC_BIND=true

# --- Cargar Módulos (si es necesario) ---
# Si tu compilador o bibliotecas requieren módulos específicos:
# module purge
# module load gcc/11.3.0 # Ejemplo: carga una versión específica de GCC

# --- Parámetros de ejecución de tu programa ---
# Definir el tamaño N del arreglo.
# Puedes pasarlo como argumento al script o fijarlo aquí.
# Para este ejemplo, lo pasamos directamente como argumento al programa C++.
# Si quieres probar diferentes N, podrías usar otro job array o bucles.
ARRAY_SIZE_N=100000000 # 100 millones de elementos, para que tome tiempo

# --- Ejecutar el programa ---
# ./tu_programa_compilado <ARGUMENTO_N>
# El programa imprimirá la línea CSV en la salida estándar.
./suma ${ARRAY_SIZE_N} > openmp_times-${SLURM_ARRAY_TASK_ID}.txt