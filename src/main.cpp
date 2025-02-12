#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <utility>
#include "Kruskal.h"
#include "linear_search.h"
#include "MaxFlowSolver.h"
#include "traveling_salesman.h"

using namespace std;

char convert_to_letters(int index) {
    return static_cast<char>('A' + index);
}

string format_tsp_output(const vector<int>& route) {
    string result;
    for (int node : route) {
        result += convert_to_letters(node);
        result += " ";
    }
    result += convert_to_letters(route[0]);
    return result;
}

vector<vector<int>> read_distances(int V) {
    vector<vector<int>> distances(V, vector<int>(V));
    for (int i = 0; i < V; ++i) {
        for (int j = 0; j < V; ++j) {
            cin >> distances[i][j];
        }
    }
    return distances;
}

vector<vector<int>> read_capacities(int V) {
    vector<vector<int>> capacities(V, vector<int>(V));
    for (int i = 0; i < V; ++i) {
        for (int j = 0; j < V; ++j) {
            cin >> capacities[i][j];
        }
    }
    return capacities;
}

pair<int, int> read_centers_and_contract(int V, vector<pair<int, int>>& centrals) {
    int x, y;
    char ch;
    
    // Leer coordenadas de las centrales 
    for (int i = 0; i < V; ++i) {
        cin >> ch; 
        cin >> x;
        cin >> ch; 
        cin >> y;
        cin >> ch; 
        centrals.emplace_back(x, y);
    }

    cin >> ch; 
    cin >> x;
    cin >> ch; 
    cin >> y;
    cin >> ch; 
    return {x, y};
}

/**
 * @brief Ejecuta el algoritmo de Kruskal.
 * @param V Número de nodos.
 * @param distances Matriz de distancias entre nodos.
 */
void kruskal_algorithm(int V, const vector<vector<int>>& distances) {
    Graph g(V);
    for (int i = 0; i < V; ++i) {
        for (int j = i + 1; j < V; ++j) {
            if (distances[i][j] != 0) {
                g.AddEdge(i, j, distances[i][j]);
            }
        }
    }
    cout << "Parte 1: Algoritmo de Kruskal: " << endl;
    g.KruskalMST();
}

/**
 * @brief Ejecuta el algoritmo de Traveling Salesman Problem (TSP).
 * @param V Número de nodos.
 * @param distances Matriz de distancias entre nodos.
 */
void tsp_algorithm(int V, const vector<vector<int>>& distances) {
    cout << "Parte 2: Traveling Salesman Problem" << endl;
    auto tsp_answer = TravelingSalesman::Solve(V, distances);  // Cambiar de TSP::Solve a TravelingSalesman::Solve
    cout << format_tsp_output(tsp_answer) << endl;
}


/**
 * @brief Ejecuta el algoritmo de Ford Fulkerson para encontrar el flujo máximo.
 * @param V Número de nodos.
 * @param capacities Matriz de capacidades entre nodos.
 */
void max_flow_algorithm(int V, const vector<vector<int>>& capacities) {
    cout << "Parte 3: Max Flow" << endl;
    int max_flow = MaxFlowSolver::Solve(V, capacities, 0, V - 1);
    cout << max_flow << endl;
}

/**
 * @brief Ejecuta la búsqueda lineal para encontrar el contrato más cercano.
 * @param centrals Lista de ubicaciones de las centrales.
 * @param new_contract Coordenada del nuevo contrato.
 */
void linear_search_algorithm(const vector<pair<int, int>>& centrals, const pair<int, int>& new_contract) {
    cout << "Parte 4: Busqueda Lineal" << endl;
    auto linear_search_result = SearchNearest::Find(centrals, new_contract);
    cout << "(" << linear_search_result.first << ", " << linear_search_result.second << ")" << endl;
}

/**
 * @brief Función principal del programa.
 * Ejecuta los cuatro problemas solicitados.
 */
int main() {
    int V;
    cin >> V;

    vector<pair<int, int>> centrals; // Asegúrate de declarar el vector de centrals aquí

    // Leer distancias, capacidades, y datos de centrales y nuevo contrato
    auto distances = read_distances(V);
    auto capacities = read_capacities(V);
    auto new_contract = read_centers_and_contract(V, centrals);

    // Ejecutar los algoritmos
    kruskal_algorithm(V, distances);
    tsp_algorithm(V, distances);
    max_flow_algorithm(V, capacities);
    linear_search_algorithm(centrals, new_contract);

    return 0;
}
