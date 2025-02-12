#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

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
            parent[i] = parent[parent[i]];
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
    vector<tuple<int, int, int>> edges;
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
    void KruskalMST() {
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
    }
};

/**
 * @brief Función principal.
 */
int main() {
    Graph g(6);
    g.AddEdge(0, 1, 4);
    g.AddEdge(0, 2, 4);
    g.AddEdge(1, 2, 2);
    g.AddEdge(1, 3, 6);
    g.AddEdge(2, 3, 8);
    g.AddEdge(3, 4, 9);
    g.AddEdge(4, 5, 10);

    g.KruskalMST();
    return 0;
}
