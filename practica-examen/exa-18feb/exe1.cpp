// Ivan Fernandez Mena
// E48

// Coste:

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include "PriorityQueue.h"

struct tarea{
    int timeIni;
    int timeEnd;
    int periodo;

    tarea(int i, int e):timeIni(i), timeEnd(e), periodo(-1){}
    tarea(int i, int e, int p):timeIni(i), timeEnd(e), periodo(p){}

    tarea():timeIni(0), timeEnd(0), periodo(0){}

    void incrementar(){
        timeIni += periodo;
        timeEnd += periodo;
    }
};

bool operator< (tarea const& a, tarea const& b){
    return a.timeIni < b.timeIni || (a.timeIni == b.timeIni && a.timeEnd < b.timeEnd);
}

bool resolver(PriorityQueue<tarea> & pq, int times){

    bool sol = true;


    tarea tr = pq.top(); pq.pop();
    int endLastTarea = -1;

    while(tr.timeIni < times && sol){

        if(tr.periodo != -1){
            tr.incrementar();
            pq.push(tr);
        }

        if(endLastTarea >= tr.timeIni && endLastTarea <= times)
            sol = false;

        endLastTarea = tr.timeEnd - 1;
        if(!pq.empty()) {
            tr = pq.top();
            pq.pop();
        }
    }

    return sol;
}

bool resultCase(){

    int numUnicas, numPeriodicas, rango, inicioTarea, finTarea, periodoRegistro;

    std::cin >> numUnicas >> numPeriodicas >> rango;

    if(!std::cin)
        return false;

    PriorityQueue<tarea> pq;

    for (int i = 0; i < numUnicas; ++i) {
        std::cin >> inicioTarea >> finTarea;
        pq.push(tarea(inicioTarea, finTarea));
    }

    for (int i = 0; i < numPeriodicas; ++i) {
        std::cin >> inicioTarea >> finTarea >> periodoRegistro;
        pq.push(tarea(inicioTarea, finTarea, periodoRegistro));
    }

    std::cout << (!resolver(pq, rango) ? "SI" : "NO") << "\n";

    return true;
}

int main() {
#ifndef DOMJUDGE
    std::ifstream in("../exa-18feb/datos-1.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    while(resultCase());

#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif

    return 0;
}