set title "Tiempo de ejecución vs Número de threads"
set xlabel "Número de threads"
set ylabel "Tiempo (segundos)"
set grid
set key outside
set datafile separator whitespace
set style data linespoints

# Si quieres guardar como imagen PNG
set terminal pngcairo size 800,600
set output 'lu_tiempo.png'

# Graficar mean_wtime y mean_ctime con barras de error
plot "lu.txt" using 1:3:4 with yerrorlines title "Wall time (prom ± std)", \
     "lu.txt" using 1:5:6 with yerrorlines title "CPU time (prom ± std)"