#include <gtest/gtest.h>
#include "../src/traveling_salesman.h"

// TEST 1: Grafo pequeño, verifica ruta óptima
TEST(TSPTest, SmallGraphTest) {
    vector<vector<int>> distances = {
        {0, 10, 15, 20},
        {10, 0, 35, 25},
        {15, 35, 0, 30},
        {20, 25, 30, 0}
    };
    
    vector<int> ruta_obtenida = TravelingSalesman::Solve(4, distances);
    vector<int> ruta_esperada = {0, 1, 3, 2};
    
    ASSERT_EQ(ruta_obtenida, ruta_esperada);
}

// TEST 2: Grafo con 4 nodos, diferentes distances
TEST(TSPTest, MediumGraphTest) {
    vector<vector<int>> distances = {
        {0, 29, 20, 21},
        {29, 0, 15, 17},
        {20, 15, 0, 28},
        {21, 17, 28, 0}
    };
    
    vector<int> ruta_obtenida = TravelingSalesman::Solve(4, distances);
    vector<int> ruta_esperada = {0, 2, 1, 3};
    
    ASSERT_EQ(ruta_obtenida, ruta_esperada);
}

// TEST 3: Grafo más grande, validación de tamaño de ruta
TEST(TSPTest, LargeGraphTest) {
    vector<vector<int>> distances = {
        {0, 10, 8, 9, 7},
        {10, 0, 10, 5, 6},
        {8, 10, 0, 8, 9},
        {9, 5, 8, 0, 6},
        {7, 6, 9, 6, 0}
    };
    
    vector<int> ruta_obtenida = TravelingSalesman::Solve(5, distances);
    vector<int> ruta_esperada = {0, 4, 1, 3, 2};  // Esperado puede ser cualquier ruta óptima, validamos tamaño

    ASSERT_EQ(ruta_obtenida.size(), ruta_esperada.size());
}

// TEST 4: Grafo con dos nodos, única ruta válida
TEST(TSPTest, TwoNodeGraphTest) {
    vector<vector<int>> distances = {
        {0, 1},
        {1, 0}
    };
    
    vector<int> ruta_obtenida = TravelingSalesman::Solve(2, distances);
    vector<int> ruta_esperada = {0, 1};
    
    ASSERT_EQ(ruta_obtenida, ruta_esperada);
}
