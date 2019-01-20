// Ivan Fernandez Mena
// E48

// Lo que pide el enunciado es la componente conexa mas grande

// Coste: Coste de dfs: E + V

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include "GrafoValorado.h"

class Trunk{
public:
    Trunk(GrafoValorado<int> const & G, int it, int et, long int vt) : marked(G.V(), false), endTrunk(et),iniTrunk(it), valueTrunk(vt){
        // NO ponemos el for de conexa ya que no queremos que mire todas, solo saber si llega
        dfs(G, iniTrunk);
    }

    int getPosible(){
        return marked[endTrunk];
    }

private:
    std::vector<int> marked;
    int iniTrunk, endTrunk;
    long int valueTrunk;

    int dfs(GrafoValorado<int> const& G, int v){
        marked[v] = true;
        for(Arista<int> aris : G.ady(v)){
            int w = aris.otro(v);
            if(!marked[w] && aris.valor() >= valueTrunk){
                dfs(G, w);
            }
        }
    }

};

bool resultCase(){

    int numVertex, numEdge, vertex, edge;
    long int value;

    std::cin >> numVertex;

    if(!std::cin)
        return false;

    std::cin >> numEdge;

    GrafoValorado<int> graph(numVertex);

    for (int i = 0; i < numEdge; ++i) {
        std::cin >> vertex >> edge >> value;
        graph.ponArista(Arista<int>(vertex-1, edge-1, value));
    }

    int numQueries, iniTrunk, endTrunk;
    long int valueTrunk;

    std::cin >> numQueries;

    for (int j = 0; j < numQueries; ++j) {
        std::cin >> iniTrunk >> endTrunk >> valueTrunk;
        Trunk tk(graph, iniTrunk-1, endTrunk-1, valueTrunk);
        std::cout << (tk.getPosible() ? "SI" : "NO") << "\n";
    }

    return true;
}

int main() {
#ifndef DOMJUDGE
    std::ifstream in("../exa-18feb/datos-1.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    while(resultCase());

#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif

    return 0;
}