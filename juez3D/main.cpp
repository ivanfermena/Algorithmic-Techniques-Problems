#include <iostream>
#include <iomanip>
#include <fstream>
#include "GrafoValorado.h"
#include <string>
#include <queue>
#include "IndexPQ.h"

#define INF_MAX 100000000

bool operator<(Arista<int> const& a, Arista<int> const& b){
    return a.valor() <= b.valor();
}

struct aristasConteo{
    Arista<int> aris;
    int valueW = 0;
    aristasConteo(Arista<int> a, int w):aris(a), valueW(w){}
};

class ViajeColegio{
public:
    ViajeColegio(GrafoValorado<int> const& G) : marked(G.V(), false), pq(G.V()), distTo(G.V(), INF_MAX), edgeTo(G.V()) {

        distTo[0] = 0;
        pq.push(0, 0); // Initialize pq with 0, weight 0.
        while (!pq.empty()) {
            int v = pq.top().elem;
            pq.pop();
            visit(G, v);
        }
    }

    std::vector<Arista<int>> pathTo(int v){
        std::vector<Arista<int>> path;
        for (Arista<int> e = edgeTo[v]; e.uno() != 0; e = edgeTo[e.uno()]){
            path.push_back(e);
            v = e.uno();
        }

        path.push_back(edgeTo[v]);
        return path;
    }


private:
    std::vector<bool> marked;
    std::queue<Arista<int>> mst;
    IndexPQ<int> pq;
    std::vector<Arista<int>> edgeTo;
    std::vector<int> distTo;


    void visit(GrafoValorado<int> const & G, int v) {
        marked[v] = true;
        for (Arista<int> e : G.ady(v)) {
            int w = e.otro(v);

            if (marked[w])
            if (marked[w]) continue;

            if (e.valor() < distTo[w]) {
                edgeTo[w] = e;
                distTo[w] = e.valor();
                pq.update(w, distTo[w]);
            }
        }
    }
};

bool resuelveCaso() {

    int V, A, v, w, value;

    std::cin >> V;

    if(!std::cin)
        return false;

    std::cin >> A;

    GrafoValorado<int> graphs(V);

    // Insertamos las aristas
    for (int i = 0; i < A; ++i) {
        std::cin >> v >> w >> value;
        graphs.ponArista(Arista<int>(v-1, w-1, value));
    }

    ViajeColegio vc(graphs);

    std::vector<Arista<int>> ac = vc.pathTo(graphs.V()-1);

    for(Arista<int> a : ac){
        std::cout << a.valor() << " ";
    }

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