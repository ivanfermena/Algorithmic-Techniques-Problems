// Ivan Fernandez Mena
// E48

// Lo que pide el enunciado es la componente conexa mas grande

// Coste: O(E + V) .Ya que recorre todos los vertices al menos una vez y comprueba su aristas al menos una vez.

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include "Grafo.h"

class Amigos{
public:
    Amigos(Grafo const & G, int s):marked(G.V(), false), edgeTo(G.V(), 0), maxConex(0){

        for (int i = 0; i < G.V(); ++i) {
            int count = 0;
            if(!marked[i]) {
                dfs(G, i, count);
                maxConex = std::max(maxConex, count);
            }
        }

    }

    int getMax(){
        return maxConex;
    }

private:
    std::vector<int> marked;
    std::vector<int> edgeTo;
    int maxConex;

    int dfs(Grafo G, int v, int & count){
        marked[v] = true;
        count++;
        for(int w : G.ady(v)){
            if(!marked[w]){
                edgeTo[w] = v;
                dfs(G, w, count);
            }
        }
    }

};

void resultCase(){

    int numVertex, numEdge, vertex, edge;

    std::cin >> numVertex >> numEdge;

    Grafo graph(numVertex);

    for (int i = 0; i < numEdge; ++i) {
        std::cin >> vertex >> edge;
        graph.ponArista(vertex-1, edge-1);
    }

    Amigos ami(graph, 0);

    std::cout << ami.getMax() << "\n";

}

int main() {
#ifndef DOMJUDGE
    std::ifstream in("../exa-16feb/datos-1.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    int numCases;
    std::cin >> numCases;
    for (int i = 0; i < numCases; ++i) {
        resultCase();
    }

#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif

    return 0;
}