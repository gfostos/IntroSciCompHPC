#include "percolation.h"

using namespace std::chrono;

int main(int argc, char* argv[]) {
    if (argc != 4) {
        cerr << "Uso: ./percolate L p num_iteraciones\n";
        return 1;
    }

    int L = stoi(argv[1]);
    double p = stod(argv[2]);
    int n = stoi(argv[3]);

    int count_perco = 0;
    double suma = 0;
    double suma_cuadrados = 0;

    auto start = high_resolution_clock::now();
    random_device rd;
    for (int i = 0; i < n; ++i) {
        mt19937 gen(rd());
        auto matriz = generarMatriz(L, p, gen);

        vector<pair<int, int>> clusterV, clusterH;
        int tamV = detectarClusterPercolante(matriz, clusterV);
        int tamH = detectarClusterPercolanteHorizontal(matriz, clusterH);

        int tamano = max(tamV, tamH);

        if (tamano > 0) {
            count_perco++;
            suma += tamano;
            suma_cuadrados += pow(tamano, 2);
        }
    }
    auto end = high_resolution_clock::now();
    duration<double> duracion = end - start;

    double P = (n > 0) ? static_cast<double>(count_perco) / n : 0;
    double promedio = (count_perco > 0) ? suma / count_perco : 0;
    double promedio_normal = static_cast<double>(promedio) / (L * L);
    double std = (count_perco > 1)
        ? sqrt((suma_cuadrados - pow(suma, 2) / count_perco) / (count_perco - 1))
        : 0;

    printf("%d | %.3f | %.1f | %.2f | %.3f | %.3f | %.3f s\n", L, p, P, promedio, promedio_normal, std, duracion.count());

    return 0;
}