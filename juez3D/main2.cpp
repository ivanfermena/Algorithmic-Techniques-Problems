// Ivan Fernandez Mena
// E48

#include <iostream>
#include <iomanip>
#include <fstream>
#include "Grafo.h"

class Bipartito {
public:
    // Constructor de marcadores que gestiona si has pasado por el
    Bipartito(const Grafo& G) : marked(G.V(), false), _is_bipartito(true), colors(G.V(), -1) {
        int color = 0;
        for (auto v = 0; v < G.V(); ++v) {
            if (!marked[v]) {
                dfs(G, v, color);
            }
        }
    }
    // tamaño máximo de una componente conexa
    bool is_bipartito() const {
        return _is_bipartito;
    }

    int get_min_color(){
        return std::min(value_0, value_1);
    }

private:
    std::vector<bool> marked; // marked[v] = se ha visitado el vértice v?
    std::vector<int> colors; // colors[v] = 0 un color y 1 otro color, -1 si no tiene ningun valor
    bool _is_bipartito;
    int value_0 = 1;
    int value_1 = 1;

    // recorrido en profundidad de la componente de v
    void dfs(Grafo const& G, int v, int & color) {
        marked[v] = true;
        colors[v] = color;
        int control_color = color;

        for (int w : G.ady(v)) {
            if (!marked[w]) {
                //color = (control_color == 0 ? 1 : 0);
                if(control_color == 0) {
                    color = 1;
                    value_1++;
                }
                else{
                    color = 0;
                    value_0++;
                }

                dfs(G, w, color);
            }else if(colors[w] == control_color)
                _is_bipartito = false;
        }
    }
};

bool resuelveCaso() {

    // Variables
    int num_vertices, num_aristas;
    std::cin >> num_vertices;
    if(!std::cin)
        return false;

    Grafo graphs(num_vertices);

    std::cin >> num_aristas;

    int vertice_first, vertice_second;

    for (int i = 0; i < num_aristas; ++i) {
        std::cin >> vertice_first >> vertice_second;
        graphs.ponArista(vertice_first-1, vertice_second-1);
    }

    Bipartito bip(graphs);

    // Obtenemos el is_bipartito
    if(bip.is_bipartito()) std::cout << bip.get_min_color() << "\n";
    else std::cout << "IMPOSIBLE\n";

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