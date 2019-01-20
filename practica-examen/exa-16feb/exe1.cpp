// Ivan Fernandez Mena
// E48

// Lo que pide el enunciado es la componente conexa mas grande

// Coste: EL coste individual de las operaciones pop y push es de O(log N), por tanto:

//          NlogN + KlogN + 1 donde N es el numero de usuarios insertan y K el numero de consultas que tiene un push y pop por cada una de ellas.
//          EL mas 1 es por la operacion top().

//          Por tanto el coste es: O(NlogN + KlogN)

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include "PriorityQueue.h"

struct registro{
    int id;
    int periodo;
    int value;
    registro(int i, int p):id(i),periodo(p), value(p){}
    registro():id(0),periodo(0), value(0){}

    void incrementar(){
        value += periodo;
    }
};

bool operator< (registro const& a, registro const& b){
    return a.value < b.value || (a.value == b.value && a.id < b.id);
}

int resolver(PriorityQueue<registro> & pq){

    registro rg = pq.top(); pq.pop();
    rg.incrementar();
    pq.push(rg);
    return rg.id;
}

bool resultCase(){

    int numRegistros, idRegistro, periodoRegistro;

    std::cin >> numRegistros;

    if(numRegistros == 0)
        return false;

    PriorityQueue<registro> pq;

    for (int i = 0; i < numRegistros; ++i) {
        // quitar basura
        std::cin >> idRegistro >> periodoRegistro;
        pq.push(registro(idRegistro, periodoRegistro));
    }

    int numConsultas;

    std::cin >> numConsultas;

    for (int j = 0; j < numConsultas; ++j) {
        std::cout << resolver(pq) << "\n";
    }

    std::cout << "----\n";

    return true;
}

int main() {
#ifndef DOMJUDGE
    std::ifstream in("../exa-16feb/datos-1.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    while(resultCase());

#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif

    return 0;
}