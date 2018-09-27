// Ivan Fernandez Mena
// E48

#include <iostream>
#include <iomanip>
#include <fstream>
#include "PriorityQueue.h"
#include <string>
#include <vector>

struct data{
    std::string name;
    long int severity;
    long int time;
    data(std::string n, long int s, long int t):name(n),severity(s),time(t){};
    data(){};
};

// Cambiamos el comparador < de tal modo que compruebe gravedad y si no times.
bool operator<(data const& a, data const& b){
    return a.severity > b.severity || (a.severity == b.severity && a.time < b.time);
}

bool resuelveCaso() {

    int numElem;
    PriorityQueue<data> prio_queue;
    data sol, aux_sol;
    int number_turn = 0;

    std::cin >> numElem;

    // Ya no hay mas casos
    if(numElem == 0)
        return false;

    // Insertamos los valores en la cola
    for(int i = 0; i < numElem; i++){
        char turn;
        std::string aux_name;
        long int aux_severity;

        std::cin >> turn;

        if(turn == 'I'){
            std::cin >> aux_name >> aux_severity;
            prio_queue.push(data(aux_name, aux_severity, number_turn++));
        }else if(turn == 'A'){
            sol = prio_queue.top(); prio_queue.pop();
            std::cout << sol.name << "\n";
        }

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