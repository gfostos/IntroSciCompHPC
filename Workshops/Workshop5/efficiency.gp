# efficiency.gp
set terminal pdfcairo font "Arial,12" size 10in,7in
set output "efficiency_plot.pdf"

# <--- CAMBIA ESTO PARA INCLUIR EL NUMERO DE CORES FISICOS Y LOGICOS REALES DE TU COMPUTADORA
set title "Eficiencia Paralela - Vector Size: 2e8 - Cores Físicos: 8, Hilos Totales: 16"
set xlabel "Número de Threads"
set ylabel "Eficiencia Paralela"
set grid
set key top right
set yrange [0:1.1] # La eficiencia típicamente no supera 1

# Tiempo de referencia (Política 0, 1 hilo)
time_seq = 0.0907619 # <--- ASEGÚRATE QUE ESTE VALOR ES EL CORRECTO DE TUS DATOS

# Curva teórica de eficiencia (Ideal)
ideal_efficiency(x) = 1.0 # La eficiencia ideal es 100% (1.0)

plot \
    "resultados/datos.txt" using (column(1)==1 ? column(2) : NaN):(time_seq/(column(3)*column(2))) with linespoints title "par (Política 1)", \
    "resultados/datos.txt" using (column(1)==2 ? column(2) : NaN):(time_seq/(column(3)*column(2))) with linespoints title "par_ unseq (Política 2)", \
    ideal_efficiency(x) with lines linestyle 1 lc rgb "red" lw 2 title "Teórico (Ideal)"