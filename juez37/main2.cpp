// TAIS48 Ivan Fernandez Mena

#include <fstream>
#include <iostream>
#include <iomanip>
#include <queue>
#include "GrafoValorado.h"
#include "IndexPQ.h"

class Bridges {
public:
    Bridges(GrafoValorado<int> const& G) : pq(G.V()), distTo(G.V(), 99999), edgeTo(G.V(), Arista<int>(0, 0 ,0)), marked(G.V(), false) {

        _minimun_value = 0;
        _count_markes = 0;

        distTo[0] = 0;
        pq.push(0, Arista<int>(0, 0 ,0));

        while(!pq.empty()){
            Arista<int> auxArista = pq.top().prioridad; pq.pop();
            visit(G, auxArista.uno());
        }

    }

    int getCountMinimal(){
        return _minimun_value;
    }

    int getCountMarkes(){
        return _count_markes;
    }


private:
    std::vector<bool> marked;
    IndexPQ<Arista<int>> pq;
    std::vector<Arista<int>> edgeTo;
    std::vector<int> distTo;

    int _minimun_value;
    int _count_markes;

    void visit(GrafoValorado<int> G, int v){

        marked[v] = true;
        _count_markes++;

        for (Arista<int> e : G.ady(v)) {
            int w = e.otro(v);

            if(marked[w]) continue;

            if (e.valor() < distTo[w]) {
                edgeTo[w] = e;
                distTo[w] = e.valor();
                _minimun_value += e.valor();
                pq.update(w, e);
            }
        }
    }
};


bool resuelveCaso(){

    int vertex, edges, vertex_ini, vertex_end, weight;

    std::cin >> vertex;

    while(!std::cin)
        return false;

    std::cin >> edges;

    GrafoValorado<int> graph(vertex);

    for (int i = 0; i < edges; ++i) {
        std::cin >> vertex_ini >> vertex_end >> weight;
        graph.ponArista(Arista<int>(vertex_ini-1, vertex_end-1, weight));
    }

    Bridges bridge(graph);

    if(bridge.getCountMarkes() == graph.V())
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