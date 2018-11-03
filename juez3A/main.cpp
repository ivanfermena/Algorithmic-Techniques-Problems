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

            _isArbol = false;
            int posible_vertice = 0;

            for (int j = 0; j < G.V(); ++j) {
                if(G.ady(j).size() == 0){
                    posible_vertice = j;
                    _isArbol = true; // Posible solucion buena
                }
            }

            GrafoDirigido G_normal = G.inverso();

            if(_isArbol) {
                dfs(G_normal, posible_vertice);
            }

            // Comprobamos que esten marcados
            for (bool item: marked) {
                if(!item) {
                    _isArbol = false;
                    break;
                }
            }

            number_sol = posible_vertice;
        }

        std::pair<int, bool> solutionArbolecencia(){
            return std::pair<int, bool>(number_sol, _isArbol);
        }

    private:
        std::vector<bool> marked; // marked[v] = ¿hay camino de s a v?
        bool _isArbol;
        int number_sol = 0;

        void dfs(GrafoDirigido const& G, int v) {
            marked[v] = true;
            for(int w : G.ady(v))
                if(!marked[w])
                    dfs(G, w);
                else _isArbol = false;
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

    // Obtenemos el inverso
    GrafoDirigido graphsInv = graphs.inverso();

    Arbolescencia arb(graphsInv);

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