#ifndef MAX_FLOW_SOLVER_H
#define MAX_FLOW_SOLVER_H

#include <vector>
#include <queue>
#include <climits>

using namespace std;

/**
 * @brief Implementación alternativa para encontrar el flujo máximo en una red de flujo.
 */
class MaxFlowSolver {
public:
    /**
     * @brief Calcula el flujo máximo usando BFS con una cola de prioridad.
     */
    static int Solve(int n, const vector<vector<int>>& capacity, int source, int sink) {
        vector<vector<int>> flow(n, vector<int>(n, 0));
        vector<int> parent(n, -1);
        int max_flow = 0;

        while (PriorityBFS(n, capacity, flow, source, sink, parent)) {
            int flow_path = AugmentFlow(capacity, flow, source, sink, parent);
            max_flow += flow_path;
        }
        return max_flow;
    }

private:
    /**
     * @brief BFS usando una cola de prioridad para mejorar la búsqueda de caminos.
     */
    static bool PriorityBFS(int n, const vector<vector<int>>& capacity, const vector<vector<int>>& flow,
                            int source, int sink, vector<int>& parent) {
        fill(parent.begin(), parent.end(), -1);
        priority_queue<pair<int, int>> pq;
        pq.push({INT_MAX, source});
        parent[source] = -2;

        while (!pq.empty()) {
            int u = pq.top().second;
            int current_flow = pq.top().first;
            pq.pop();

            for (int v = 0; v < n; ++v) {
                if (parent[v] == -1 && capacity[u][v] > flow[u][v]) {
                    parent[v] = u;
                    int new_flow = min(current_flow, capacity[u][v] - flow[u][v]);
                    if (v == sink) return true;
                    pq.push({new_flow, v});
                }
            }
        }
        return false;
    }

    /**
     * @brief Aumenta el flujo en la red siguiendo el camino encontrado por BFS.
     */
    static int AugmentFlow(const vector<vector<int>>& capacity, vector<vector<int>>& flow,
                           int source, int sink, const vector<int>& parent) {
        int flow_path = INT_MAX;
        for (int v = sink; v != source; v = parent[v]) {
            int u = parent[v];
            flow_path = min(flow_path, capacity[u][v] - flow[u][v]);
        }
        for (int v = sink; v != source; v = parent[v]) {
            int u = parent[v];
            flow[u][v] += flow_path;
            flow[v][u] -= flow_path;
        }
        return flow_path;
    }
};

#endif
