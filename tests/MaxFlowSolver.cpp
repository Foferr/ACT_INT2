#include <gtest/gtest.h>
#include "../src/MaxFlowSolver.h"

// TEST 1: Grafo simple 
TEST(test_max_flow_solver, test_1_max_flow_solver)
{
    vector<vector<int>> capacity = {{0, 3, 3, 0, 0, 0},
                                    {0, 0, 2, 3, 0, 0},
                                    {0, 0, 0, 0, 2, 0},
                                    {0, 0, 0, 0, 4, 2},
                                    {0, 0, 0, 0, 0, 2},
                                    {0, 0, 0, 0, 0, 3}};
    
    int V = capacity.size();
    ASSERT_EQ(MaxFlowSolver::Solve(V, capacity, 0, V - 1), 4);
}

// TEST 2: Grafo pequeño con restricciones
TEST(test_max_flow_solver, test_2_max_flow_solver)
{
    vector<vector<int>> capacity = {{0, 5, 0, 0},
                                    {0, 0, 4, 0},
                                    {0, 0, 0, 6},
                                    {0, 0, 0, 0}}; 

    int V = capacity.size(); 
    ASSERT_EQ(MaxFlowSolver::Solve(V, capacity, 0, V - 1), 4); 
}

// TEST 3: Grafo desconectado (Sin flujo posible)
TEST(test_max_flow_solver, test_3_max_flow_solver)
{
    vector<vector<int>> capacity = {{0, 5, 0, 0},
                                    {0, 0, 4, 0},
                                    {0, 0, 0, 0},  
                                    {0, 0, 0, 0}}; 

    int V = capacity.size(); 
    ASSERT_EQ(MaxFlowSolver::Solve(V, capacity, 0, V - 1), 0); 
}

// TEST 4: Red compleja, con múltiples caminos
TEST(test_max_flow_solver, test_4_max_flow_solver)
{
    vector<vector<int>> capacity = {{0, 10, 10, 0, 0, 0},
                                    {0, 0, 2, 4, 8, 0},
                                    {0, 0, 0, 0, 9, 0},
                                    {0, 0, 0, 0, 0, 10},
                                    {0, 0, 0, 6, 0, 10},
                                    {0, 0, 0, 0, 0, 0}}; 

    int V = capacity.size(); 
    ASSERT_EQ(MaxFlowSolver::Solve(V, capacity, 0, V - 1), 19); 
}
