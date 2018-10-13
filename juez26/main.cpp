
// Ivan Fernandez Mena - TAIS48

// El ejercicio lo he resulto con una unica cola de prioridad, en la que ordeno por tiempo y despues por la propia cola que le toca. Voy tratando de manera independiente con dos
// bucles el llenado del principio y el caso en el que haya mas elementos.

// Coste de la operacion principal es O(C*logn) en el n como numero de colas que hay, ya que se tienen que tratar una vez cada cliente y contar tambien las operaciones de la propia cola
// de prioridad. Por usar dos bucles no cambia el coste ya que estan separados y se sumarian los costes de cantidad de colas y clientes.

// C es el numero de clientes

#include <iostream>
#include <fstream>
#include "PriorityQueue.h"
using namespace std;

struct dato
{
	int time;
	int cola;
	dato(int t, int c): time(t), cola(c){}
	dato() : time(0), cola(0) {}
};

bool operator<(dato const& a, dato const& b) { 
	return a.time < b.time || (a.time == b.time && a.cola < b.cola);
}

bool resuelveCaso() {
   int N, C;
   cin >> N >> C;
   
   if (N == 0)
      return false;
   
   PriorityQueue <dato> prio_queue;
   int time;
   dato aux_dato;

   // Llenamos las colas en orden
   int i = 0;

   for (; i < N && i < C; i++) {
       cin >> time;
	   prio_queue.push(dato(time, i + 1));
   }

   int num_client = i;

   while (num_client < C) {
	   aux_dato = prio_queue.top(); prio_queue.pop();
	   cin >> time;
	   prio_queue.push(dato(aux_dato.time + time, aux_dato.cola));
	   num_client++;
   }

   if(i == N) aux_dato = prio_queue.top();
   else aux_dato = dato(0, num_client+1);
   
   cout << aux_dato.cola << "\n";

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
