# plot_optimizations.gnu

set terminal pngcairo size 800,600 enhanced font 'Verdana,10'
set output 'optimizations_plot.png'

set title "Comparación de tiempos por nivel de optimización"
set xlabel "N (parámetro de entrada)"
set ylabel "Tiempo de ejecución (segundos)"

set grid
set key left top

plot \
    "out_O0.txt" using 2:3 with linespoints title "-O0", \
    "out_O1.txt" using 2:3 with linespoints title "-O1", \
    "out_O2.txt" using 2:3 with linespoints title "-O2", \
    "out_O3.txt" using 2:3 with linespoints title "-O3"
