// TAIS48 Ivan Fernandez Mena

#include <fstream>
#include <iostream>
#include <iomanip>
#include <queue>
#include "IndexPQ.h"
#include "ConjuntosDisjuntos.h"
#include "GrafoDirigidoValorado.h"

class AristaTime{
public:
    AristaTime(AristaDirigida<int> a, int c):aris(a), cost(c){}
    AristaTime():aris(AristaDirigida<int>(0,0,0)), cost(0){}

    AristaDirigida<int> gestArista() const{
        return aris;
    }

    int getCost() const{
        return cost;
    }

private:
    AristaDirigida<int> aris;
    int cost;
};

class Comp{
public:
    bool operator()(AristaTime left, AristaTime right) {
        return left.gestArista().valor() < right.gestArista().valor()
               || (left.gestArista().valor() == right.gestArista().valor() && left.getCost() < right.getCost());
    }
};

class Web {
public:
    Web(GrafoDirigidoValorado<int> const& G, IndexPQ<AristaTime, Comp> & pq, std::vector<int> & costTime) : uf(G.V()), lastElem(false) {

        _minimun_value = 0;

        while(!pq.empty() && mst.size() < G.V() - 1 && !lastElem){

            AristaDirigida<int> e = pq.top().prioridad.gestArista(); pq.pop();

            int v = e.from(), w = e.to();

            if(!uf.unidos(v, w)) {
                uf.unir(v, w);
                mst.push(e);

                _minimun_value += e.valor() + costTime[v];
            }

            // Es la solucion, ya qu ese ha llegado al ultimo que se buscaba
            if(uf.unidos(0, G.V() - 1)){
                _minimun_value += costTime[w];
                lastElem = true;
            }
        }

    }

    int getFinish(){
        return lastElem;
    }

    int getCountMinimal(){
        return _minimun_value;
    }

private:

    std::queue<AristaDirigida<int>> mst;
    ConjuntosDisjuntos uf;

    bool lastElem;
    int _minimun_value;
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

    IndexPQ<AristaTime, Comp> pq(edges);

    for (int i = 0; i < edges; ++i) {
        std::cin >> vertex_ini >> vertex_end >> weight;
        AristaDirigida<int> aris(vertex_ini-1, vertex_end-1, weight);
        graph.ponArista(aris);
        AristaTime arisTime(aris, costTime[vertex_ini-1] + costTime[vertex_end-1] + aris.valor());
        pq.update(i, arisTime);
    }

    Web bridge(graph, pq, costTime);

    if(bridge.getFinish())
        std::cout << bridge.getCountMinimal() << "\n";
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