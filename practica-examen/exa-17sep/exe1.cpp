// Ivan Fernandez Mena
// E48

// Lo que pide el enunciado es la componente conexa mas grande

// Coste:   Coste viene determinado por el sort al tener que ordenar de mayor a menor los libros, quedando O(NlogN).
//          Si nos centramos solo en las operaciones de resuelve seria lineal en el numero de libros ya que solo recorre
//          una unica vez cada uno.

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <algorithm>

int resolver(std::vector<int> const& vc, int maxPeso){

    int sol = 0;

    int i = 0, j = vc.size()-1;

    while ( i <= vc.size() && i < j ) {
        if(vc[i] + vc[j] <= maxPeso){
            sol++; ++i; --j;
        }else{
            sol++;
            --j;
        }
    }

    if(i == j)
        sol++;

    return sol;
}

bool resultCase(){

    int maxPeso, numSillas, peso;

    std::cin >> maxPeso >> numSillas;

    if(!std::cin)
        return false;

    std::vector<int> vc;

    for (int i = 0; i < numSillas; ++i) {
        std::cin >> peso;
        vc.push_back(peso);
    }

    std::sort(vc.begin(), vc.end());

    std::cout << resolver(vc, maxPeso) << "\n";

    return true;
}

int main() {
#ifndef DOMJUDGE
    std::ifstream in("../exa-17sep/datos-1.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    while(resultCase());

#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif

    return 0;
}