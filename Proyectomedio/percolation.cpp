#include "percolation.h"

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

    finalPercolatingCluster.clear(); 

    for (int j = 0; j < L; ++j) {
        if (matriz[0][j] == 1 && !visitado[0][j]) {
            vector<pair<int, int>> currentDfsCluster; 
            if (dfsPercolanteIterativo(0, j, matriz, visitado, currentDfsCluster)) {
                finalPercolatingCluster = currentDfsCluster;
                return finalPercolatingCluster.size();
            }
        }
    }
    return 0;
}

// Detectar clúster percolante horizontal
int detectarClusterPercolanteHorizontal(const vector<vector<int>> &matriz, vector<pair<int, int>> &finalPercolatingCluster) {
    int L = matriz.size();
    vector<vector<bool>> visitado(L, vector<bool>(L, false));

    finalPercolatingCluster.clear();

    for (int i = 0; i < L; ++i) {
        if (matriz[i][0] == 1 && !visitado[i][0]) {
            vector<pair<int, int>> currentDfsCluster;
            if (dfsPercolanteHorizontalIterativo(i, 0, matriz, visitado, currentDfsCluster)) {
                finalPercolatingCluster = currentDfsCluster;
                return finalPercolatingCluster.size();
            }
        }
    }
    return 0;
}