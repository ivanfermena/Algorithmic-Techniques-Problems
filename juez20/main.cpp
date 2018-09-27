// Ivan Fernandez Mena
// E48

#include <iostream>
#include <iomanip>
#include <fstream>
#include "PriorityQueue.h"

bool resuelveCaso() {

    // Variables
    long int numElem, elem, value_aux, effort = 0;
    long int value_a, value_b;
    PriorityQueue<long int> prio_queue;

    // Leemos la cantidad de numeros
    std::cin >> numElem;

    // Ya no hay mas casos
    if(numElem == 0)
        return false;

    // Insertamos los valores en la cola
    for(int i = 0; i < numElem; i++){
        std::cin >> elem;
        prio_queue.push({elem});
    }

    if(numElem == 1) {
        std::cout << effort << "\n";
        return true;
    }

    while (!prio_queue.empty()) {
        // Cogemos los dos primeros
        value_a = prio_queue.top(); prio_queue.pop();
        value_b = prio_queue.top(); prio_queue.pop();

        // Sumamos los elemntos
        value_aux = value_a + value_b;

        // Insertamos de nuevo la suma a la cola
        if(!prio_queue.empty())
            prio_queue.push({value_aux});

        // Actualizamos el esfuerzo
        effort += value_aux;
    }
    std::cout << effort << "\n";
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