// Ivan Fernandez Mena
// E48

//

#include <iostream>
#include <iomanip>
#include <fstream>
#include "GrafoDirigido.h"
#include <string>
#include <queue>
#include <stack>

class Arbolescencia {
public:
    Arbolescencia(GrafoDirigido const& G) : marked(G.V()) {
        _isArbol = true;
        for (int i = 0; i < G.V(); ++i) {
            elem_conex = i;
            if(!marked[i])
                dfs(G, i);
        }
    }

    std::pair<int, bool> solutionArbolecencia(){
        return std::pair<int, bool>(reservePostorden.top(), _isArbol);
    }

private:
    std::vector<bool> marked; // marked[v] = ¿hay camino de s a v?
    std::stack<int> reservePostorden;
    bool _isArbol;
    int elem_conex;

    void dfs(GrafoDirigido const& G, int v) {
        marked[v] = true;
        for(int w : G.ady(v))
            if(!marked[w])
                dfs(G, w);
            else if(w == elem_conex)
                _isArbol = false;
        reservePostorden.push(v);
    }
};

bool resuelveCaso() {

    int V, A, v, w;

    std::cin >> V;

    if(!std::cin)
        return false;

    std::cin >> A;

    GrafoDirigido graphs(V);

    // Insertamos las aristas
    for (int i = 0; i < A; ++i) {
        std::cin >> v >> w;
        graphs.ponArista(v, w);
    }

    Arbolescencia arb(graphs);

    std::cout << (arb.solutionArbolecencia().second ? "SI " + std::to_string(arb.solutionArbolecencia().first) : "NO") << "\n";

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