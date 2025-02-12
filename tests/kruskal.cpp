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
    
    // Los nodos 3 y 4 no están conectados, causando que el grafo sea desconectado
    try {
        g->KruskalMST();  
        FAIL() << "Se esperaba una excepción debido a un grafo desconectado.";
    } catch (const std::runtime_error& e) {
        EXPECT_STREQ(e.what(), "Grafo desconectado");
    } catch (...) {
        FAIL() << "Se esperaba una excepción de tipo std::runtime_error.";
    }
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
