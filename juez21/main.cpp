// Ivan Fernandez Mena
// E48

#include <iostream>
#include <iomanip>
#include <fstream>
#include "PriorityQueue.h"

// Coste de las operaciones es de O(NlogN + KlogN) donde N es el numero de elemtos de registros y K numero de consultas

struct data{
    int id;
    int period;
    int time;
    //data(int i, int p, int t):id(i),period(p),time(t){};
};

// Cambiamos el comparador < de tal modo que compruebas tiempos y si no id's.
bool operator<(data const& a, data const& b){
    return a.time < b.time || (a.time == b.time && a.id < b.id);
}

bool resuelveCaso() {

    int numElem, aux_id, aux_period, sendings;
    PriorityQueue<data> prio_queue;

    std::cin >> numElem;

    // Ya no hay mas casos
    if(numElem == 0) return false;

    // Insertamos los valores en la cola
    for(int i = 0; i < numElem; i++){
        std::cin >> aux_id >> aux_period;
        prio_queue.push({aux_id, aux_period, aux_period});
    }

    std::cin >> sendings;

    for (int j = sendings; j > 0 ; --j) {
        data elem_now = prio_queue.top();
        prio_queue.pop();

        std::cout << elem_now.id << "\n";
        elem_now.time += elem_now.period; // Incrementamos el siguiente turno
        prio_queue.push(elem_now); // Reinsertamos con el nuevo tiempo
    }
    std::cout << "----" << "\n";
    return true;
}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    std::ifstream in("datos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif

    bool numControl = true;
    while (numControl) {
        numControl = resuelveCaso();
    }

    // Para restablecer entrada. Comentar para acepta el reto
#ifndef DOMJUDGE // para dejar todo como estaba al principio
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif

    return 0;
}