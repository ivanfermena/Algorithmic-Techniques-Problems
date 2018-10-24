// Ivan Fernandez Mena
// E48

#include <iostream>
#include <iomanip>
#include <fstream>
#include "GrafoDirigido.h"

class MinimalRoad {
public:
    // Como maximo podemos tener que minimo de movimientos sea recorrer todos los vertices
    MinimalRoad(const GrafoDirigido& G, int const d) : marked(G.V(), false), _minimal_mov(G.V()), _dice(d) {
        for (auto v = 0; v < G.V(); ++v) {
            if (!marked[v]) {
                marked[v] = true;
                std::vector<bool> marked_inv(G.V(), false);
                int count_mov = 0;
                _global_count = 0;
                dfs(G, v, count_mov, marked_inv);
                _minimal_mov = std::min(_minimal_mov, count_mov);
            }
        }
    }

    int minimal() const {
        return _minimal_mov;
    }

private:
    std::vector<bool> marked;
    int _minimal_mov;
    int _dice; // Dado
    int _global_count;

    // recorrido en profundidad de la componente de v
    void dfs(GrafoDirigido const& G, int v, int & count_mov, std::vector<bool> & marked_inv) {
        marked_inv[v] = true;

        ++_global_count;
        if(_global_count >= _dice){
            ++count_mov;
            _global_count = 0;
        }

        for (int w : G.ady(v)) {
            if (!marked_inv[w]) {
                dfs(G, w, count_mov, marked_inv);
            }
        }
    }
};

bool resuelveCaso() {

    int N, K, S, E;

    std::cin >> N >> K >> S >> E;

    if(N == 0 && K == 0 && S == 0 && E == 0)
        return false;

    GrafoDirigido graphs(N*N);

    // Primero conectamos todos los vertices en orden ascendente hasta N
    for (int j = 0; j < graphs.V()-1; ++j) {
        graphs.ponArista(j, j+1);
    }

    int v_first, v_second;

    for (int i = 0; i < S + E; ++i) {
        std::cin >> v_first >> v_second;
        graphs.ponArista(v_first-1, v_second-1);
    }

    MinimalRoad game(graphs, K);

    std::cout << game.minimal() << "\n";

    return true;
}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    std::ifstream in("datos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif

    while(resuelveCaso());

    // Para restablecer entrada. Comentar para acepta el reto
#ifndef DOMJUDGE // para dejar todo como estaba al principio
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif

    return 0;
}