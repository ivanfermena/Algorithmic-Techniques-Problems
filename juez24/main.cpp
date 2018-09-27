// Ivan Fernandez Mena
// E48

#include <iostream>
#include <iomanip>
#include <fstream>
#include "PriorityQueue.h"
#include <string>
#include <vector>

bool resuelveCaso() {

    int numElem;
    PriorityQueue<long int, std::greater<long int>> prio_queue_n;
    PriorityQueue<long int> prio_queue_n1;
    long int number, n, n1;


    // Control de casos
    std::cin >> numElem;
    if(numElem == 0)
        return false;

    // Caso base de un elemento
    std::cin >> number;
    prio_queue_n.push(number);

    std::cout << number*2 << " ";

    // Miramos cada valor de entrada
    for(int i = 0; i < numElem - 1; i++){

        std::cin >> number;
        n = prio_queue_n.top();

        if(number > n) prio_queue_n1.push(number);
        else prio_queue_n.push(number);

        // Compruebas reordenar

        // Rotamos para que el izquierdo siempre sea mayor o igual que el n+1
        if(prio_queue_n.size() < prio_queue_n1.size()){
            long int aux_n1 = prio_queue_n1.top(); prio_queue_n1.pop();
            prio_queue_n.push(aux_n1);
        }
        else if(prio_queue_n.size() > prio_queue_n1.size() + 1){
            long int aux_n = prio_queue_n.top(); prio_queue_n.pop();
            prio_queue_n1.push(aux_n);
        }

        // Calcular mediana
        if((prio_queue_n.size() + prio_queue_n1.size()) % 2 == 0) { // Par
            std::cout << ((prio_queue_n.top() + prio_queue_n1.top())*2)/2 << " ";
        }
        else std::cout << (prio_queue_n.top() * 2) << " ";
    }
    std::cout << "\n";
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