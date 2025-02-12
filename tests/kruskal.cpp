#include <gtest/gtest.h>
#include "../src/Kruskal.h"

class KruskalTest : public ::testing::Test {
protected:
    Graph* g;

    void SetUp() override {
        g = new Graph(5);
    }

    void TearDown() override {
        delete g;
    }
};

TEST_F(KruskalTest, GrafoPequeno) {
    g->AddEdge(0, 1, 1);
    g->AddEdge(1, 2, 2);
    g->AddEdge(2, 3, 3);
    g->AddEdge(3, 4, 4);
    
    EXPECT_EQ(g->KruskalMST(), 10);
}

TEST_F(KruskalTest, GrafoConectadoConCiclo) {
    g->AddEdge(0, 1, 2);
    g->AddEdge(1, 2, 3);
    g->AddEdge(2, 3, 4);
    g->AddEdge(3, 4, 5);
    g->AddEdge(4, 0, 1);  // Crea un ciclo

    EXPECT_EQ(g->KruskalMST(), 10);
}

TEST_F(KruskalTest, GrafoDesconectado) {
    g->AddEdge(0, 1, 5);
    g->AddEdge(1, 2, 10);
    
    // Nodo 3 y 4 sin conexión
    EXPECT_ANY_THROW(g->KruskalMST());  // Debería fallar por grafo desconectado
}

TEST_F(KruskalTest, GrafoDenso) {
    g->AddEdge(0, 1, 1);
    g->AddEdge(1, 2, 2);
    g->AddEdge(2, 3, 3);
    g->AddEdge(3, 4, 4);
    g->AddEdge(0, 2, 2);
    g->AddEdge(1, 3, 3);
    g->AddEdge(2, 4, 4);

    EXPECT_EQ(g->KruskalMST(), 10);
}
