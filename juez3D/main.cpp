// Ivan Fernandez Mena TAIS48

#include <iostream>
#include <fstream>
#include "Grafo.h"

using namespace std;

/*
Hemos planteado el ejercicio como el de grafos bipartitos, marcando de un color los cruzes
que tienen guardia y de otro los cruces que no pueden tener. Usamos un vector para marcar los colores
e indicar si esta marcado o no y recorremos el grafo en profundidad, marcando unicamente con guardia los
cruzes que tengan calle.

Controlamos que no haya dos guardias en una misma calle a partir de estos colores diferentes. 

El coste del algoritmo principal es O(V + E) siendo V el numero de cruces y E el numero de calles. Este coste
viene por recorrer una vez las calles y cruces.
*/

class Calles {
public:
	Calles(Grafo const& G) : marked(G.V(), -1) {
		cont_0 = 0;
		cont_1 = 0;
		for (int v = 0; v < G.V(); ++v) {
			if (marked[v] == -1) { // se recorre una nueva componente conexa
				int conj = 0;
				dfs(G, v, conj);
			}
		}
	}

	int getCont_min() {
		return std::min(cont_0, cont_1);
	}

private:
	vector<int> marked; // marked[v] = se ha visitado el vértice v?
	int cont_0;
	int cont_1;

	// recorrido en profundidad de la componente de v
	void dfs(Grafo const& G, int v, int conj) {
		conj = (conj == 0 ? 1 : 0);
		marked[v] = conj;

		if(conj == 1 && G.ady(v).size() > 0 && cont_0 != -1)
			cont_0++;
		else if(conj == 0 && G.ady(v).size() > 0 && cont_1 != -1)
			cont_1++;
		
		for (int w : G.ady(v)) {
			if (marked[w] == -1) {
				dfs(G, w, marked[v]);
			}
			else {
				if (marked[w] == marked[v]){
					cont_0 = -1;
					cont_1 = -1;
				}
			}
		}
	}

};


bool resuelveCaso() {
   int cruces, calles;
   cin >> cruces >> calles;
   
   if (!cin)
      return false;
   
   Grafo grafo(cruces);
   for (int i = 0; i < calles; i++) {
	   int aux1, aux2;
	   cin >> aux1 >> aux2;
	   grafo.ponArista(aux1-1, aux2-1);
   }
    
   Calles calle(grafo);

   if (calle.getCont_min() == -1)
	   cout << "IMPOSIBLE\n";
   else
	   cout << calle.getCont_min() << "\n";
   
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
