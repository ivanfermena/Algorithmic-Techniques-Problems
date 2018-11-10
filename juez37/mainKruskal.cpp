// TAIS48 Ivan Fernandez Mena

#include <fstream>
#include <iostream>
#include <iomanip>
#include <queue>
#include "GrafoValorado.h"
#include "IndexPQ.h"
#include "ConjuntosDisjuntos.h"

class Bridges {
public:
    Bridges(GrafoValorado<int> const& G, IndexPQ<Arista<int>> & pq) : uf(G.V()), marked(G.V(), false) {

        _minimun_value = 0;
        _count_markes = 0;

        while(!pq.empty() && mst.size() < G.V() - 1){

            Arista<int> e = pq.top().prioridad; pq.pop();

            int v = e.uno(), w = e.otro(v);

            if(!uf.unidos(v, w)) {
                uf.unir(v, w);
                mst.push(e);
                _minimun_value += e.valor();
            }
        }

    }

    int getCountMarkes(){
        return uf.num_cjtos();
    }

    int getCountMinimal(){
        return _minimun_value;
    }

private:

    std::queue<Arista<int>> mst;
    ConjuntosDisjuntos uf;
    std::vector<bool> marked;

    int _minimun_value;
    int _count_markes;
};


bool resuelveCaso(){

    int vertex, edges, vertex_ini, vertex_end, weight;

    std::cin >> vertex;

    while(!std::cin)
        return false;

    std::cin >> edges;

    GrafoValorado<int> graph(vertex);

    IndexPQ<Arista<int>> pq(edges);

    for (int i = 0; i < edges; ++i) {
        std::cin >> vertex_ini >> vertex_end >> weight;
        Arista<int> aris(vertex_ini-1, vertex_end-1, weight);
        graph.ponArista(aris);
        pq.update(i, aris);
    }

    Bridges bridge(graph, pq);

    if(bridge.getCountMarkes() == 1)
        std::cout << bridge.getCountMinimal() << "\n";
    else
        std::cout << "No hay puentes suficientes" << "\n";

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