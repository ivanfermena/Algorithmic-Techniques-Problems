// Ivan Fernandez Mena
// E48

#include <iostream>
#include <iomanip>
#include <fstream>
#include "PriorityQueue.h"

// Se da por echo que si se usa una estructura periodica minimo se repetira cada un elemento
struct data {
    long long int ini;
    long long int end;
    long long int period;
    data():ini(0),end(0),period(0){};
    data(long long int i, long long int e):ini(i),end(e),period(0){}; // Constructor No Periodicas
    data(long long int i, long long int e, long long int p):ini(i),end(e),period(p){}; // Constructor Periodicas
};

// Comparator de data, ordenamos hasta por periodo
bool operator<(data const& a, data const& b){
    return a.ini < b.ini || (a.ini == b.ini && a.end < b.end) || (a.ini == b.ini && a.end == b.end && a.period < b.period);
}

bool resolver(PriorityQueue <data> & prio_queue, int const test_time){

    bool control_end = true;

    // Obtenemos el primero y guardamos en min, max para empezar a comprobar
    data first_elem = prio_queue.top(); prio_queue.pop();
    data control = data(first_elem.ini, first_elem.end);
    data elem_queue = first_elem;

    // Comprobamos si es periodico
    if(first_elem.period != 0) prio_queue.push(data(first_elem.ini + first_elem.period, first_elem.end + first_elem.period, first_elem.period));

    while(elem_queue.ini < test_time && control_end && !prio_queue.empty()){

        elem_queue = prio_queue.top(); prio_queue.pop();

        if(control.end < elem_queue.ini){
            control = elem_queue;

            if(elem_queue.period != 0) prio_queue.push(data(elem_queue.ini + elem_queue.period, elem_queue.end + elem_queue.period, elem_queue.period));
        }
        else if(elem_queue.ini < test_time){
            control_end = false;
        }
    }

    return control_end;
}

bool resuelveCaso() {

    // Variables
    int num_unique, num_periodic, test_time;
    PriorityQueue <data> prio_queue;
    long long int in_ini, in_end, in_period;

    std::cin >> num_unique >> num_periodic >> test_time;
    if (!std::cin)
        return false;

    // Leemos los unicos e insertamos en la cola
    for (int i = 0; i < num_unique; ++i) {
        std::cin >> in_ini >> in_end;
        prio_queue.push(data(in_ini, in_end - 1));
    }

    // Leemos los periodicos e insertamos en la cola
    for (int i = 0; i < num_periodic; ++i) {
        std::cin >> in_ini >> in_end >> in_period;
        prio_queue.push(data(in_ini, in_end - 1, in_period));
    }

    // Lanzamos el resolver con los valores recogidos

    !resolver(prio_queue, test_time) ? std::cout << "SI" << "\n" : std::cout << "NO" << "\n";

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