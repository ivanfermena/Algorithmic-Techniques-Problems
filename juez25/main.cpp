// Ivan Fernandez Mena
// E48

#include <iostream>
#include <iomanip>
#include <fstream>
#include "Grafo.h"

// El coste de la operacion de O(v + a) donde v son los vertices y a el numero de aristas

class MaximComponentConexa {
    public:
        // Constructor de marcadores que gestiona si has pasado por el
        MaximComponentConexa(const Grafo& G) : marked(G.V(), false), _maximo(0) {
            for (auto v = 0; v < G.V(); ++v) {
                if (!marked[v]) {
                    // se recorre una nueva componente conexa
                    int tam = 0;
                    dfs(G, v, tam);
                    _maximo = std::max(_maximo, tam);
                }
            }
        }
        // tamaño máximo de una componente conexa
        int maximo() const {
            return _maximo;
        }

    private:
        std::vector<bool> marked; // marked[v] = se ha visitado el vértice v?
        int _maximo;

        // recorrido en profundidad de la componente de v
        void dfs(Grafo const& G, int v, int & tam) {
            marked[v] = true;
            ++tam;
            for (int w : G.ady(v)) {
                if (!marked[w]) {
                    dfs(G, w, tam);
                }
            }
        }
};

bool resuelveCaso() {

    // Variables
    int different_persons, pair_person;
    std::cin >> different_persons >> pair_person;
    Grafo graph(different_persons);

    int person_first, person_second;

    // Recogemos cada valor de personas con la persona a la que esta unida y la insertamos en el grafo
    for (int i = 0; i < pair_person; ++i) {
        std::cin >> person_first >> person_second;
        graph.ponArista(person_first - 1, person_second - 1); // Menos uno ya que las personas estan numeradas con un valor mas
    }

    // Lanzamos la propia creacion del constructor
    MaximComponentConexa mcc(graph);

    // Obtenemos el maximo
    std::cout << mcc.maximo() << '\n';
}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    std::ifstream in("datos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif

    // Obtenemos los casos
    int numCases;
    std::cin >> numCases;
    for (int i = 0; i < numCases; ++i) {
        resuelveCaso();
    }

    // Para restablecer entrada. Comentar para acepta el reto
#ifndef DOMJUDGE // para dejar todo como estaba al principio
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif

    return 0;
}