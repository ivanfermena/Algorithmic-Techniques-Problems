//
// Created by ivanfermena on 03/11/18.
//

#include <fstream>
#include <iostream>
#include "GrafoValorado.h"

class RoadsDrivingTrunk {
public:
    RoadsDrivingTrunk(GrafoValorado<int> const& G) : marked(G.V(), false) {
        for (int v = 0; v < G.V(); ++v) {
            if (!marked[v]) { // se recorre una nueva componente conexa
                dfs(G, v);
            }
        }
    }
// tamaño máximo de una componente conexa
    int is_valid() const {
        return _is_ok;
    }

private:
    std::vector<bool> marked; // marked[v] = se ha visitado el vértice v?
    int _is_ok = true;

// recorrido en profundidad de la componente de v
    void dfs(GrafoValorado<int> const& G, int v) {
        marked[v] = true;
        for (Arista<int> w : G.ady(v)) {
            if (!marked[w.uno()]) {
                dfs(G, w.uno());
            }
        }
    }
};


bool resuelveCaso(){

    int vertex, edges, vertex_ini, vertex_end;
    int weight;

    std::cin >> vertex;

    while(!std::cin)
        return false;

    std::cin >> edges;

    GrafoValorado<int> graph(vertex);

    for (int i = 0; i < edges; ++i) {
        std::cin >> vertex_ini >> vertex_end >> weight;
        graph.ponArista(Arista<int>(vertex_ini, vertex_end, weight));
    }

    // Ahora llegan las peticiones de viajes
    int number_trunks, trunk_ini, trunk_end, trunk_weight;

    std::cin >> number_trunks;
    for (int j = 0; j < number_trunks; ++j) {
        std::cin >> trunk_ini >> trunk_end >> trunk_weight;
        // Calcular si hay
    }

}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    std::ifstream in("datos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif

    while (resuelveCaso());

    // Para restablecer entrada. Comentar para acepta el reto
#ifndef DOMJUDGE // para dejar todo como estaba al principio
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif

    return 0;
}