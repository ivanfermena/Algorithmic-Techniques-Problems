//
// Created by ivanfermena on 03/11/18.
//

#include <fstream>
#include <iostream>
#include <iomanip>
#include <queue>
#include "GrafoValorado.h"
#include "IndexPQ.h"

class Bridges {
public:
    Bridges(GrafoValorado<int> const& G) : pq(G.V()), marked(G.V(), false) {

        visit(G, 0);

        while(!pq.empty() && mst.size() < G.V() - 1){

            Arista<int> e = pq.top(); pq.pop();

            int v = e.uno(), w = e.otro(v);
            if(marked[v] && marked[w])
                continue;

            mst.pop();
            if(!marked[v]) visit(G, v);
            if(!marked[w]) visit(G, w);
        }

    }

private:
    std::vector<bool> marked;
    std::queue<Arista<int>> mst;
    IndexPQ<Arista<int>> pq;

    void visit(GrafoValorado<int> G, int v)
    {
        marked[v] = true;
        for (Arista<int> e : G.ady(v))
            if (!marked[e.otro(v)])
                pq.push(e.uno(), e);
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