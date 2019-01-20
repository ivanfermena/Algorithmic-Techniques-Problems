// Ivan Fernandez Mena
// E48

// Lo que pide el enunciado es la componente conexa mas grande

// Coste: El coste de las operaciones son la siguientes:
            // UF unir: log E
            // dfs : E + V

            // Coste total seria: ElogV + VlogV quedandonos con el que sea mayor

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include "Grafo.h"
#include "ConjuntosDisjuntos.h"

class Amigos{
public:
    Amigos(Grafo const & G, int s):marked(G.V(), false), edgeTo(G.V(), 0), conex(true), uf(G.V()){
        dfs(G, 0);
    }

    int getFree(){
        return uf.num_cjtos() == 1 ? conex : false;
    }

private:
    std::vector<int> marked;
    std::vector<int> edgeTo;
    ConjuntosDisjuntos uf;

    bool conex;

    int dfs(Grafo G, int v){
        marked[v] = true;
        for(int w : G.ady(v)){
            if(!marked[w]){
                uf.unir(v,w);
                edgeTo[w] = v;
                dfs(G, w);
            }else if(marked[w] && edgeTo[v] != w)
                conex = false;
        }
    }

};

bool resultCase(){

    int numVertex, numEdge, vertex, edge;

    std::cin >> numVertex;

    if(!std::cin)
        return false;

    std::cin >> numEdge;

    Grafo graph(numVertex);

    for (int i = 0; i < numEdge; ++i) {
        std::cin >> vertex >> edge;
        graph.ponArista(vertex, edge);
    }

    Amigos ami(graph, 0);

    std::cout << (ami.getFree() ? "SI" : "NO") << "\n";

    return true;
}

int main() {
#ifndef DOMJUDGE
    std::ifstream in("../exa-18jul/datos-1.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    while(resultCase());

#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif

    return 0;
}