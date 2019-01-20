// Ivan Fernandez Mena
// E48

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include "Matriz.h"
#include <string>

#define INF 1000000000

void Floyd(Matriz<int> const& G, Matriz<int> & C, int & max) {

    int n = G.numfils() - 1;
    C = G;

    for (int k = 1; k <= n; ++k) {
        for (int i = 1; i <= n; ++i){
            for (int j = 1; j <= n; ++j) {
                C[i][j] = std::min(C[i][k] + C[k][j], C[i][j]);
            }
        }
    }

    // Una vez hecho calculado el C ahora vemos el camino maximo
    for (int l = 1; l <= n && max != -1; ++l) {
        for (int i = 1; i <= n && max != -1; ++i) {
            // Obtienes el maximo
            if(l != i && C[l][i] < INF) {
                max = std::max(max, C[l][i]);
            }else if(C[l][i] >= INF){
                max = -1;
            }
        }
    }
}

bool resuelveCaso() {

    int nVertex, nEdge;

    std::cin >> nVertex >> nEdge;

    if(!std::cin)
        return false;

    Matriz<int> graph(nVertex+1,nVertex+1,INF);
    for (int u = 1; u <= nVertex; ++u)
        graph[u][u] = 0;

    std::unordered_map<std::string, int> umap;

    std::string uPerson, vPerson;
    int count = 1;

    for (int i = 0; i < nEdge; ++i) {
        std::cin >> uPerson >> vPerson;
        if(umap.insert({uPerson, count}).second)
            count++;
        if(umap.insert({vPerson, count}).second)
            count++;
        graph[umap[uPerson]][umap[vPerson]] = 1;
        graph[umap[vPerson]][umap[uPerson]] = 1;
    }

    int max = 0;
    Matriz<int> C(0,0); Matriz<int> camino(0,0);
    Floyd(graph, C, max);

    if(max == -1) std::cout << "DESCONECTADA" << "\n";
    else std::cout << max << "\n";

    return true;
}

int main() {
#ifndef DOMJUDGE
    std::ifstream in("datos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    while (resuelveCaso());

#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif

    return 0;
}