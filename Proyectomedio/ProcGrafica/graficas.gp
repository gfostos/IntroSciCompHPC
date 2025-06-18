set title "Tiempo promedio de cómputo vs Tamaño del sistema"
set xlabel "Tamaño del sistema L"
set ylabel "Tiempo promedio (s)"
set logscale y
set grid
set key top left
set term pngcairo size 800,600
set output "tiempo_vs_L.png"
plot "tprom1.txt" using 1:2 with linespoints title "Tiempo promedio (1)", "tprom2.txt" using 1:2 with linespoints title "Tiempo promedio (2)", "tprom3.txt" using 1:2 with linespoints title "Tiempo promedio (3)", "tpromfast.txt" using 1:2 with linespoints title "Tiempo promedio (Fast)"