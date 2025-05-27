set terminal pdf enhanced font "Helvetica,12"
set output 'fibonacci.pdf'

set title "Rendimiento de las Implementaciones de Fibonacci"
set xlabel "n"
set ylabel "Tiempo(s)"
set grid
set logscale y

set key outside right top # Position the legend

color_O0 = "#08A1FE" # Blue
color_O1 = "#E30808" # Red
color_O2 = "#14A214" # Green
color_O3 = "#FF7F00" # Orange
color_Ofast = "#9E09A8" # Purple

plot \
    '0.txt' using 1:2 with linespoints lc rgb color_O0 pt 'x' title 'Recursivo (0)', \
    '0.txt' using 1:3 with linespoints lc rgb color_O0 pt '○' title 'Iterativo (0)', \
    '1.txt' using 1:2 with linespoints lc rgb color_O1 pt 'x' title 'Recursivo (1)', \
    '1.txt' using 1:3 with linespoints lc rgb color_O1 pt '○' title 'Iterativo (1)', \
    '2.txt' using 1:2 with linespoints lc rgb color_O2 pt 'x' title 'Recursivo (2)', \
    '2.txt' using 1:3 with linespoints lc rgb color_O2 pt '○' title 'Iterativo (2)', \
    '3.txt' using 1:2 with linespoints lc rgb color_O3 pt 'x' title 'Recursivo (3)', \
    '3.txt' using 1:3 with linespoints lc rgb color_O3 pt '○' title 'Iterativo (3)', \
    'fast.txt' using 1:2 with linespoints lc rgb color_Ofast pt 'x' title 'Recursivo (fast)', \
    'fast.txt' using 1:3 with linespoints lc rgb color_Ofast pt '○' title 'Iterativo (fast)'