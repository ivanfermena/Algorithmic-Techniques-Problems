// Ivan Fernandez Mena
// E48

// Coste: Primerop viene definido por la PQ que requiere que se inserten todas las aristas.
            // PQ construccion : O(E)
            // Union y COnnected por ser un conjunto disjunto de peso es O(log E)
            // Borrar un elemento de la PQ: O(log E)

            // Por tanto, el coste total es: O(E + E*logE) Ya que se hace una contruccion una vez y las operaciones dictadas E veces. (Para arista)

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include "GrafoValorado.h"
#include "PriorityQueue.h"
#include <queue>
#include "ConjuntosDisjuntos.h"


bool operator <(Arista<int> const& a, Arista<int> const& b){
    return a.valor() < b.valor() || a.valor() == b.valor();
}


class Puentes{
public:
    Puentes(GrafoValorado<int> const & G, PriorityQueue<Arista<int>> pq) : UF(G.V()), costMST(0) {

        while(!pq.empty() && mst.size() < G.V()-1){
            Arista<int> e = pq.top(); pq.pop();
            int v = e.uno(), w = e.otro(v);
            if(!UF.unidos(v, w)){
                UF.unir(v,w);
                mst.push(e);
                costMST += e.valor();
            }
        }
    }

    bool isConected(){
        return UF.num_cjtos() == 1;
    }

    int costeMST(){
        return costMST;
    }

private:

    std::queue<Arista<int>> mst;
    ConjuntosDisjuntos UF;
    int costMST;

};

bool resultCase(){

    int numVertex, numEdge, vertex, edge, value;

    std::cin >> numVertex;

    if(!std::cin)
        return false;

    std::cin >> numEdge;

    GrafoValorado<int> graph(numVertex);
    PriorityQueue<Arista<int>> pq;

    for (int i = 0; i < numEdge; ++i) {
        std::cin >> vertex >> edge >> value;
        Arista<int> e(vertex-1, edge-1, value);
        graph.ponArista(e);
        pq.push(e);
    }

    Puentes puen(graph, pq);

    if(puen.isConected()) std::cout << puen.costeMST() << "\n";
    else std::cout << "No hay puentes suficientes" << "\n";

    return true;
}

int main() {
#ifndef DOMJUDGE
    std::ifstream in("../exa-16sep/datos-1.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    while(resultCase());


#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif

    return 0;
}