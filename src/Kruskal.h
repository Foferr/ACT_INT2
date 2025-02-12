#ifndef KRUSKAL_H
#define KRUSKAL_H

#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <stdexcept> // Para lanzar excepciones

using namespace std;

class DSU {
    unordered_map<int, int> parent;
    unordered_map<int, int> size;

public:
    DSU(int n) {
        for (int i = 0; i < n; i++) {
            parent[i] = i;
            size[i] = 1;
        }
    }

    int Find(int i) {
        while (i != parent[i]) {
            parent[i] = parent[parent[i]]; // Path compression
            i = parent[i];
        }
        return i;
    }

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

class Graph {
    vector<tuple<int, int, int>> edges;
    int vertices;

public:
    Graph(int V) : vertices(V) {}

    // Agrega una arista al grafo
    void AddEdge(int u, int v, int weight) {
        edges.push_back({weight, u, v});
    }

    /**
     * @brief Algoritmo de Kruskal para MST.
     * @return El peso total del árbol de expansión mínima.
     */
    int KruskalMST() {
        // Ordena las aristas por peso
        sort(edges.begin(), edges.end());

        DSU dsu(vertices);
        int totalWeight = 0;
        int edgesUsed = 0;

        // Procesa las aristas en orden de peso
        cout << "MST:\n";
        for (auto& [weight, u, v] : edges) {
            if (dsu.Find(u) != dsu.Find(v)) {
                dsu.Unite(u, v);
                cout << u << " - " << v << " (" << weight << ")\n";
                totalWeight += weight;
                edgesUsed++;
            }
        }

        // Si no se usan suficientes aristas, el grafo está desconectado
        if (edgesUsed < vertices - 1) {
            throw std::runtime_error("Grafo desconectado");
        }

        cout << "Peso total: " << totalWeight << endl;
        return totalWeight;
    }
};

#endif // KRUSKAL_H
