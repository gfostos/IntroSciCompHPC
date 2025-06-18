#ifndef PERCOLATION_HPP
#define PERCOLATION_HPP

#include <iostream>
#include <vector>
#include <random>
#include <stack>
#include <cmath> // Para pow y sqrt
#include <chrono>

// Usar el espacio de nombres std para no repetirlo
using namespace std;

// --- Declaraciones de las funciones ---

vector<vector<int>> generarMatriz(int L, double p, mt19937 &gen);

bool dfsPercolanteIterativo(int x, int y, const vector<vector<int>> &matriz,
                            vector<vector<bool>> &visitado, vector<pair<int, int>> &cluster);

bool dfsPercolanteHorizontalIterativo(int x, int y, const vector<vector<int>> &matriz,
                                      vector<vector<bool>> &visitado, vector<pair<int, int>> &cluster);
                                      
int detectarClusterPercolante(const vector<vector<int>> &matriz, vector<pair<int, int>> &finalPercolatingCluster);

int detectarClusterPercolanteHorizontal(const vector<vector<int>> &matriz, vector<pair<int, int>> &finalPercolatingCluster);

#endif // PERCOLATION_H