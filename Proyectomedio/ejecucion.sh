#!/bin/bash

echo "Compilacion"

g++ -O3 main.cpp

echo "Ejecucion"

parallel './a.out {1} {2} 10' ::: 32 64 128 256 512 ::: $(seq 0.0 0.033 1.0) | sort -t'|' -k1,1n -k2,2n > resultados.txt

echo "Completado"