// TAIS48 Ivan Fernandez Mena

#include <fstream>
#include <iostream>
#include <iomanip>
#include <queue>
#include "IndexPQ.h"
#include "ConjuntosDisjuntos.h"
#include "GrafoDirigidoValorado.h"

#define INT_MAX 100000000

class Web {
public:
    Web(GrafoDirigidoValorado<int> const& G, int s, std::vector<int> const & costTime): pq(G.V()), distTo(G.V(), INT_MAX), edgeTo(G.V()), _minimalCost(-1), last(G.V()-1), cost(costTime) {

        distTo[s] = 0;
        pq.push(s, 0);

        while(!pq.empty()){
            int v = pq.top().elem; pq.pop();
            for(AristaDirigida<int> e : G.ady(v))
                relax(e);
        }
    }

    int getMinimalCost(){
        if(distTo[last] == INT_MAX) return -1;
        else return distTo[last] + cost[last];
    }

private:
    std::vector<AristaDirigida<int>> edgeTo;
    std::vector<int> distTo;
    IndexPQ<int> pq;
    std::vector<int> cost;

    int _minimalCost;
    int last;

    void relax(AristaDirigida<int> e){
        int v = e.from(), w = e.to();
        if(distTo[w] > distTo[v] + e.valor() + cost[v]){
            distTo[w] = distTo[v] + e.valor() + cost[v];
            pq.update(w, distTo[w]);
        }
    }

};


bool resuelveCaso(){

    int vertex, edges, vertex_ini, vertex_end, weight;

    std::cin >> vertex;

    while(vertex == 0) {
        return false;
    }

    std::vector<int> costTime(vertex);

    for(int & aux : costTime) // Vector de costes en casa una de las posiciones es una coste de un vector
        std::cin >> aux;

    std::cin >> edges;

    GrafoDirigidoValorado<int> graph(vertex);

    for (int i = 0; i < edges; ++i) {
        std::cin >> vertex_ini >> vertex_end >> weight;
        AristaDirigida<int> aris(vertex_ini-1, vertex_end-1, weight);
        graph.ponArista(aris);
    }

    Web web(graph, 0, costTime);

    if(web.getMinimalCost() != -1)
        std::cout << web.getMinimalCost() << "\n";
    else
        std::cout << "IMPOSIBLE" << "\n";

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