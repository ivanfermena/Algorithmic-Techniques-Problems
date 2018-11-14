// GUILLERMO CORTINA FERN�NDEZ TAIS61
// IVAN FERNANDEZ MENA TAIS48

//EN ESTE PROBLEMA HEMOS USADO EL AGORITM DE DISKTRA PARA RESOLVER EL PROBLEMA DE LOS RATONES, EL CUAL TIENE UNA COMPLEJIDAD DE E LOG E, SIENDO E
//EL NUMERO DE ARISTAS DEL GRAFO G(), HEMOS CREADO DOS CONTADORES, UNO PARA RATONES Y UNO PARA EL TIEMPO Y HEMOS IDO INCREMENTANDO CUANDO EL TIEMPO
//ERA MENOR DEL MAXIMO TIEMPO.
//HEMOS USADO EL GRAFO INVERSO

#include <iostream>
#include <fstream>
#include "GrafoDirigidoValorado.h"
#include "IndexPQ.h"
#include <vector>

using namespace std;

#define MAX_INT 10000000

class Ratones {
public:
	Ratones(GrafoDirigidoValorado<int> G, int s, int controlTime): pq(G.V()), edgeTo(G.V()), distTo(G.V(), MAX_INT), marked(G.V(), false), cTime(controlTime) {
		
		countRat = 0;

		marked[s] = true;
		
		distTo[s] = 0;
		pq.push(s, 0);
		while(!pq.empty()){
			int v = pq.top().elem; pq.pop();
			for (AristaDirigida<int> e : G.ady(v))
				relax(e);
		}
	}

	int getCountRat() {
		return countRat;
	}

private:
	vector<AristaDirigida<int>> edgeTo;
	vector<int> distTo;
	IndexPQ<int> pq;
	vector<bool> marked;
	int countRat;
	int cTime;

	void relax(AristaDirigida<int> e){
		int v = e.from(), w = e.to();
		if (distTo[w] > distTo[v] + e.valor()) {
			distTo[w] = distTo[v] + e.valor();
			edgeTo[w] = e;
			pq.update(w, distTo[w]);
		}
		if (distTo[w] <= cTime && !marked[w]) {
			marked[w] = true;
			countRat++;
		}
	}

};

bool resuelveCaso() {
	int N, S, T, P;
	cin >> N >> S >> T >> P;

	if (!cin)
		return false;

	GrafoDirigidoValorado<int> G(N);

	int ini, end, value;

	for (int i = 0; i < P; i++){
		cin >> ini >> end >> value;
		G.ponArista(AristaDirigida<int>(ini-1, end-1, value));
	}

	Ratones rats(G.inverso(), S-1, T);

	cout << rats.getCountRat() << "\n";

	return true;
}

int main() {
	// ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	std::ifstream in("datos.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

	while (resuelveCaso());

	// para dejar todo como estaba al principio
#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
	system("PAUSE");
#endif
	return 0;
}
