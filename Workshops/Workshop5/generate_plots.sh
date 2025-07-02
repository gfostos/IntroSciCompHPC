#!/bin/bash

# Asegúrate de que los scripts de Gnuplot estén en el mismo directorio
# o ajusta las rutas si los colocas en otro lugar.

echo "Generando plot de Speedup..."
gnuplot speedup.gp

if [ $? -ne 0 ]; then
    echo "Error al generar speedup_plot.pdf"
    exit 1
fi

echo "Generando plot de Eficiencia Paralela..."
gnuplot efficiency.gp

if [ $? -ne 0 ]; then
    echo "Error al generar efficiency_plot.pdf"
    exit 1
fi

echo "Gráficos generados: speedup_plot.pdf y efficiency_plot.pdf en el directorio actual."