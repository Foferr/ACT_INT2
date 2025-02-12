#ifndef KRUSKAL_H
#define KRUSKAL_H

#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

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
            parent[i] = parent[parent[i]];
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
    vector<tuple<int, int, int>> edges; // vector para almacenar aristas (peso, nodo1, nodo2)
    int vertices;

public:
    Graph(int V) : vertices(V) {}

    // Método para agregar una arista al grafo
    void AddEdge(int x, int y, int weight) {
        edges.push_back({weight, x, y});
    }

    // Algoritmo de Kruskal para obtener el árbol de expansión mínima (MST)
    int KruskalMST() {
        sort(edges.begin(), edges.end());
        DSU dsu(vertices);
        int totalWeight = 0;

        cout << "MST:\n";
        for (auto& [weight, u, v] : edges) {
            if (dsu.Find(u) != dsu.Find(v)) {
                dsu.Unite(u, v);
                cout << u << " - " << v << " (" << weight << ")\n";
                totalWeight += weight;
            }
        }
        cout << "Peso total: " << totalWeight << endl;

        return totalWeight; // Devuelve el peso total para las pruebas
    }
};

#endif // KRUSKAL_H
