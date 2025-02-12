#ifndef KRUSKAL_H
#define KRUSKAL_H

#include <unordered_map>
#include <vector>
#include <tuple>

using namespace std;

/**
 * @brief Estructura DSU para manejar conjuntos disjuntos.
 */
class DSU {
    unordered_map<int, int> parent;
    unordered_map<int, int> size;

public:
    /**
     * @brief Constructor.
     */
    DSU(int n) {
        for (int i = 0; i < n; i++) {
            parent[i] = i;
            size[i] = 1;
        }
    }

    /**
     * @brief Encuentra el líder del conjunto.
     */
    int Find(int i) {
        while (i != parent[i]) {
            parent[i] = parent[parent[i]];  // Compresión de ruta
            i = parent[i];
        }
        return i;
    }

    /**
     * @brief Une dos conjuntos.
     */
    void Unite(int x, int y) {
        int rootX = Find(x);
        int rootY = Find(y);

        if (rootX != rootY) {
            if (size[rootX] < size[rootY]) {
                parent[rootX] = rootY;
                size[rootY] += size[rootX];
            } else {
                parent[rootY] = rootX;
                size[rootX] += size[rootY];
            }
        }
    }
};

/**
 * @brief Clase para representar un grafo.
 */
class Graph {
    vector<tuple<int, int, int>> edges; // Almacena las aristas (peso, nodo1, nodo2)
    int vertices;

public:
    /**
     * @brief Constructor.
     */
    Graph(int V) : vertices(V) {}

    /**
     * @brief Agrega una arista.
     */
    void AddEdge(int x, int y, int weight) {
        edges.push_back({weight, x, y});
    }

    /**
     * @brief Algoritmo de Kruskal para MST.
     */
    void KruskalMST();
};

#endif // KRUSKAL_H
