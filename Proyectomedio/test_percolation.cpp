#define CATCH_CONFIG_MAIN
#include "catch2/catch_test_macros.hpp"
#include "catch2/generators/catch_generators.hpp"
#include "percolation.h"
#include <random>

TEST_CASE("Cluster vacio cuando p = 0", "[Percolacion cero]") {
    auto L = GENERATE(8, 16, 32);
    
    auto matriz = vector<vector<int>>(L, vector<int>(L, 0));

    vector<pair<int, int>> clusterV, clusterH;
    int tamV = detectarClusterPercolante(matriz, clusterV);
    int tamH = detectarClusterPercolanteHorizontal(matriz, clusterH);

    REQUIRE(max(tamV, tamH) == 0);
}

TEST_CASE("Cluster lleno cuando p = 1", "[Percolacion llena]") {
    auto L = GENERATE(8, 16, 32);

    auto matriz = vector<vector<int>>(L, vector<int>(L, 1));

    vector<pair<int, int>> clusterV, clusterH;
    int tamV = detectarClusterPercolante(matriz, clusterV);
    int tamH = detectarClusterPercolanteHorizontal(matriz, clusterH);

    REQUIRE(max(tamV, tamH) == (L * L));
}

TEST_CASE("Deteccion de cluster en un caso donde no hay percolacion", "[Custom cluster]") {
    auto matriz = vector<vector<int>>{
        {1, 0, 0, 0, 0},
        {1, 1, 0, 0, 0},
        {1, 1, 0, 0, 0},
        {1, 1, 1, 1, 0},
        {0, 0, 0, 0, 0},
    };

    vector<pair<int, int>> clusterV;
    int tamV = detectarClusterPercolante(matriz, clusterV);
    vector<pair<int, int>> clusterH;
    int tamH = detectarClusterPercolanteHorizontal(matriz, clusterH);

    REQUIRE(max(tamV, tamH) == 0);
}

TEST_CASE("Deteccion de cluster en un caso donde hay percolacion", "[Custom cluster]") {
    auto matriz = vector<vector<int>>{
        {1, 0, 0, 0, 0},
        {1, 1, 0, 0, 0},
        {1, 1, 0, 0, 0},
        {1, 1, 1, 1, 1},
        {1, 0, 0, 0, 0},
    };

    vector<pair<int, int>> clusterV;
    int tamV = detectarClusterPercolante(matriz, clusterV);
    vector<pair<int, int>> clusterH;
    int tamH = detectarClusterPercolanteHorizontal(matriz, clusterH);

    REQUIRE(max(tamV, tamH) == 11);
}
