//
// Created by ivanfermena on 03/11/18.
//

#include <fstream>
#include <iostream>
#include "GrafoValorado.h"

class RoadsDrivingTrunk {
public:
    RoadsDrivingTrunk(GrafoValorado<int> const& G, int t_ini ,int t_end, long int t_weight) : marked(G.V(), false), trunk_ini(t_ini) ,trunk_end(t_end), trunk_weight(t_weight) {
        //for (int v = trunk_ini; v < G.V(); ++v) {
        //    if (!marked[v]) { // se recorre una nueva componente conexa
                dfs(G, trunk_ini);
        //    }
        //}
    }
// tamaño máximo de una componente conexa
    int is_valid() const {
        return _is_ok;
    }

private:
    std::vector<bool> marked; // marked[v] = se ha visitado el vértice v?
    int _is_ok = false;
    int trunk_ini ,trunk_end;
    long int trunk_weight;

// recorrido en profundidad de la componente de v
    void dfs(GrafoValorado<int> const& G, int v) {
        marked[v] = true;
        for (Arista<int> a : G.ady(v)) {
            int w = a.otro(v);
            if (!marked[w] && a.valor() >= trunk_weight) {
                if(w == trunk_end)
                    _is_ok = true;
                dfs(G, w);
            }
        }
    }
};


bool resuelveCaso(){

    int vertex, edges, vertex_ini, vertex_end;
    long int weight;

    std::cin >> vertex;

    while(!std::cin)
        return false;

    std::cin >> edges;

    GrafoValorado<int> graph(vertex);

    for (int i = 0; i < edges; ++i) {
        std::cin >> vertex_ini >> vertex_end >> weight;
        graph.ponArista(Arista<int>(vertex_ini-1, vertex_end-1, weight));
    }

    // Ahora llegan las peticiones de viajes
    int number_trunks, trunk_ini, trunk_end;
    long int trunk_weight;

    std::cin >> number_trunks;
    for (int j = 0; j < number_trunks; ++j) {
        std::cin >> trunk_ini >> trunk_end >> trunk_weight;
        RoadsDrivingTrunk roads(graph, trunk_ini-1, trunk_end-1, trunk_weight);
        std::cout << (roads.is_valid() ? "SI\n" : "NO\n");
    }

    return true;
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