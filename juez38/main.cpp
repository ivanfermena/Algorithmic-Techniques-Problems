// TAIS48 Ivan Fernandez Mena

#include <fstream>
#include <iostream>
#include <iomanip>
#include <queue>
#include "GrafoValorado.h"
#include "IndexPQ.h"

class Comp{
public:
    bool operator()(Arista<int> const & left, Arista<int> const & right) const {
        return left.valor() < right.valor()
               || (left.valor() == right.valor() && left.uno() < right.uno());
    }
};

class Bridges {
public:
    Bridges(GrafoValorado<int> const& G) : pq(G.V()), marked(G.V(), false) {

        _minimun_value = 0;
        _count_markes = 0;

        visit(G, 0);

        while(!pq.empty() && mst.size() < G.V() - 1){

            Arista<int> e = pq.top().prioridad; pq.pop();

            int v = e.uno(), w = e.otro(v);
            if(marked[v] && marked[w])
                continue;

            mst.push(e);
            _minimun_value += e.valor();
            if(!marked[v]) visit(G, v);
            if(!marked[w]) visit(G, w);
        }

    }

    int getCountMinimal(){
        return _minimun_value;
    }

    int getCountMarkes(){
        return _count_markes;
    }


private:
    std::vector<bool> marked;
    std::queue<Arista<int>> mst;
    IndexPQ<Arista<int>, Comp> pq;
    int _minimun_value;
    int _count_markes;

    void visit(GrafoValorado<int> G, int v)
    {
        marked[v] = true;
        _count_markes++;
        for (Arista<int> e : G.ady(v))
            if (!marked[e.otro(v)])
                pq.update(e.otro(v), e);
    }
};


bool resuelveCaso(){

    int vertex, edges, vertex_ini, vertex_end, weight;

    std::cin >> vertex;

    while(!std::cin)
        return false;

    std::cin >> edges;

    GrafoValorado<int> graph(vertex);

    for (int i = 0; i < edges; ++i) {
        std::cin >> vertex_ini >> vertex_end >> weight;
        graph.ponArista(Arista<int>(vertex_ini-1, vertex_end-1, weight));
    }

    Bridges bridge(graph);

    if(bridge.getCountMarkes() == graph.V())
        std::cout << bridge.getCountMinimal() << "\n";
    else
        std::cout << "No hay puentes suficientes" << "\n";

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