#include <iostream>
#include <vector>
#include <random>
#include <stack>

using namespace std;

// Generar matriz aleatoria con probabilidad p
vector<vector<int>> generarMatriz(int L, double p, mt19937 &gen) {
    uniform_real_distribution<> dis(0.0, 1.0);
    vector<vector<int>> matriz(L, vector<int>(L, 0));
    for (int i = 0; i < L; ++i)
        for (int j = 0; j < L; ++j)
            matriz[i][j] = (dis(gen) < p) ? 1 : 0;
    return matriz;
}

// DFS ITERATIVA para detectar percolación vertical (arriba → abajo)
bool dfsPercolanteIterativo(int x, int y, const vector<vector<int>> &matriz,
                            vector<vector<bool>> &visitado, vector<pair<int, int>> &cluster) {
    int L = matriz.size();
    stack<pair<int, int>> pila;
    pila.push({x, y});
    bool llegaAlFondo = false;

    while (!pila.empty()) {
        auto [i, j] = pila.top();
        pila.pop();

        if (i < 0 || i >= L || j < 0 || j >= L) continue;
        if (matriz[i][j] == 0 || visitado[i][j]) continue;

        visitado[i][j] = true;
        cluster.push_back({i, j});

        if (i == L - 1) llegaAlFondo = true;

        pila.push({i - 1, j});
        pila.push({i + 1, j});
        pila.push({i, j - 1});
        pila.push({i, j + 1});
    }

    return llegaAlFondo;
}

// DFS ITERATIVA para detectar percolación horizontal (izquierda → derecha)
bool dfsPercolanteHorizontalIterativo(int x, int y, const vector<vector<int>> &matriz,
                                      vector<vector<bool>> &visitado, vector<pair<int, int>> &cluster) {
    int L = matriz.size();
    stack<pair<int, int>> pila;
    pila.push({x, y});
    bool llegaADerecha = false;

    while (!pila.empty()) {
        auto [i, j] = pila.top();
        pila.pop();

        if (i < 0 || i >= L || j < 0 || j >= L) continue;
        if (matriz[i][j] == 0 || visitado[i][j]) continue;

        visitado[i][j] = true;
        cluster.push_back({i, j});

        if (j == L - 1) llegaADerecha = true;

        pila.push({i - 1, j});
        pila.push({i + 1, j});
        pila.push({i, j - 1});
        pila.push({i, j + 1});
    }

    return llegaADerecha;
}

// Detectar clúster percolante vertical
int detectarClusterPercolante(const vector<vector<int>> &matriz, vector<pair<int, int>> &finalPercolatingCluster) {
    int L = matriz.size();
    vector<vector<bool>> visitado(L, vector<bool>(L, false));

    // Asegurarse de que el vector de salida esté vacío al comenzar
    finalPercolatingCluster.clear(); 

    // Iterar por la fila superior para encontrar un punto de inicio
    for (int j = 0; j < L; ++j) {
        if (matriz[0][j] == 1 && !visitado[0][j]) {
            // Usar un clúster temporal para esta búsqueda específica
            vector<pair<int, int>> currentDfsCluster; 
            
            // Si el DFS desde (0, j) encuentra un camino que percola...
            if (dfsPercolanteIterativo(0, j, matriz, visitado, currentDfsCluster)) {
                // ...entonces este es nuestro clúster percolante. Cópialo y devuelve su tamaño.
                finalPercolatingCluster = currentDfsCluster;
                return finalPercolatingCluster.size();
            }
            // Si no percoló, 'currentDfsCluster' se descarta y la matriz 'visitado' 
            // previene que se re-analicen estas celdas.
        }
    }

    // Si el bucle termina, no se encontró ningún clúster percolante vertical
    return 0;
}

// Detectar clúster percolante horizontal
int detectarClusterPercolanteHorizontal(const vector<vector<int>> &matriz, vector<pair<int, int>> &finalPercolatingCluster) {
    int L = matriz.size();
    vector<vector<bool>> visitado(L, vector<bool>(L, false));

    // Asegurarse de que el vector de salida esté vacío al comenzar
    finalPercolatingCluster.clear();

    // Iterar por la columna izquierda para encontrar un punto de inicio
    for (int i = 0; i < L; ++i) {
        if (matriz[i][0] == 1 && !visitado[i][0]) {
            // Usar un clúster temporal para esta búsqueda específica
            vector<pair<int, int>> currentDfsCluster;
            
            // Si el DFS desde (i, 0) encuentra un camino que percola...
            if (dfsPercolanteHorizontalIterativo(i, 0, matriz, visitado, currentDfsCluster)) {
                // ...entonces este es nuestro clúster percolante. Cópialo y devuelve su tamaño.
                finalPercolatingCluster = currentDfsCluster;
                return finalPercolatingCluster.size();
            }
            // Si no percoló, 'currentDfsCluster' se descarta.
        }
    }

    // Si el bucle termina, no se encontró ningún clúster percolante horizontal
    return 0;
}

int main(int argc, char* argv[]) {
    if (argc != 4) {
        cerr << "Uso: ./a.out L p num_iteraciones\n";
        return 1;
    }

    int L = stoi(argv[1]);
    double p = stod(argv[2]);
    int n = stoi(argv[3]);  // número de repeticiones

    int count_perco = 0;
    double suma = 0;
    double suma_cuadrados = 0;

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

    double P = (n > 0) ? static_cast<double>(count_perco) / n : 0;
    double promedio = (count_perco > 0) ? suma / count_perco : 0;
    double promedio_normal = static_cast<double>(promedio) / (L * L);
    double std = (count_perco > 1)
        ? sqrt((suma_cuadrados - pow(suma, 2) / count_perco) / (count_perco - 1))
        : 0;

    printf("%d | %.3f | %.1f | %.2f | %.3f | %.3f\n", L, p, P, promedio, promedio_normal, std);

    return 0;
}

