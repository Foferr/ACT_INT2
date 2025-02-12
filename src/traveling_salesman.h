#ifndef TRAVELING_SALESMAN_H
#define TRAVELING_SALESMAN_H

#include <vector>
#include <climits>

using namespace std;

/**
 * @brief Clase para resolver el problema del viajero.
 */
class TravelingSalesman {
public:
    /**
     * @brief Encuentra la ruta óptima usando backtracking.
     */
    static vector<int> Solve(int n, const vector<vector<int>>& distances) {
        vector<int> best_route, current_route;
        vector<bool> visited(n, false);
        int min_cost = INT_MAX;

        current_route.push_back(0);  // Empieza desde el nodo 0
        visited[0] = true;
        
        // Llamada a DFS, pasando distances como referencia constante
        dfs(0, n, distances, visited, 0, min_cost, best_route, current_route);
        return best_route;
    }

private:
    static void dfs(int node, int n, const vector<vector<int>>& distances, vector<bool>& visited, 
                    int current_cost, int& min_cost, vector<int>& best_route, vector<int>& current_route) {
        // Si se ha visitado todos los nodos
        if (current_route.size() == n) {
            // Calcula el costo total al regresar al nodo inicial
            int total_cost = current_cost + distances[node][0];
            if (total_cost < min_cost) {
                min_cost = total_cost;
                best_route = current_route;
            }
            return;
        }

        // Recorrer los nodos no visitados
        for (int next = 0; next < n; next++) {
            if (!visited[next]) {
                visited[next] = true;
                current_route.push_back(next);
                dfs(next, n, distances, visited, current_cost + distances[node][next], min_cost, best_route, current_route);
                visited[next] = false;
                current_route.pop_back();
            }
        }
    }
};

#endif // TRAVELING_SALESMAN_H
