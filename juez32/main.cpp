// Ivan Fernandez Mena
// E48

#include <iostream>
#include <iomanip>
#include <fstream>
#include "GrafoDirigido.h"
#include <queue>

class MinimalRoad {
    public:
        MinimalRoad(GrafoDirigido const& G, int s) : marked(G.V(), false), distTo(G.V()) {
            bfs(G, s);
            int x  = 1;
        }

        // ¿Hay camino del origen a v?
        bool hayCamino(int v) const {
            return marked[v];
        }

        // número de aristas entre s y v
        int distancia(int v) const {
            return distTo[v];
        }

    private:
        std::vector<bool> marked; // marked[v] = ¿hay camino de s a v?
        std::vector<int> distTo; // distTo[v] = aristas en el camino s-v más corto

        void bfs(GrafoDirigido const& G, int s) {
            std::queue<int> q;

            distTo[s] = 0;
            marked[s] = true;
            q.push(s);

            while (!q.empty()) {
                int v = q.front(); q.pop();

                for (int w : G.ady(v)) {
                    if (!marked[w]) {
                        distTo[w] = distTo[v] + 1;
                        marked[w] = true;
                        q.push(w);
                    }
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

    int v_first, v_second;

    for (int i = 0; i < S; ++i) {
        std::cin >> v_first >> v_second;
        graphs.ponArista(v_first-1, v_second-1);
    }

    for (int i = 0; i < E; ++i) {
        std::cin >> v_first >> v_second;
        graphs.ponArista(v_first-1, v_second-1);
    }

    // Primero conectamos todos los vertices en orden ascendente hasta N
    for (int j = 0; j < graphs.V()-1; j++) {
        for(int i = j; i < j + K && i < graphs.V()-1; i++){
            if(graphs.ady(i+1).empty())
                graphs.ponArista(j, i+1);
            else
                graphs.ponArista(j, graphs.ady(i+1)[0]);
        }
    }

    MinimalRoad game(graphs, 0);

    std::cout << game.distancia(graphs.V()-1) << "\n";

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