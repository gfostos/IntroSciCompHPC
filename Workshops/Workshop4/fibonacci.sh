parallel 'g++ -O{} fibonacci.cpp -o a_O{}.out' ::: 0 1 2 3 fast

echo "Compilación completada."

parallel './a_O{1}.out {2} >> {1}.txt' ::: 0 1 2 3 fast ::: $(seq 5 5 45)

parallel 'sort -n -k1 -o {}.txt {}.txt' ::: 0 1 2 3 fast

echo "Ejecución completada."