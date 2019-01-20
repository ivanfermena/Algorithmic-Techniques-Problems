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

int resolver(std::vector<int> const& vc){

    int descuento = 0;

    for (int i = 1; i <= vc.size() && vc.size() > 2; ++i) {
        descuento += ((i % 3) == 0 ? vc[i-1] : 0);
    }

    return descuento;
}

bool resultCase(){

    int numBooks, priceBook;

    std::cin >> numBooks;

    if(!std::cin)
        return false;

    std::vector<int> vc;

    for (int i = 0; i < numBooks; ++i) {
        std::cin >> priceBook;
        vc.push_back(priceBook);
    }

    std::sort(vc.begin(), vc.end(), std::greater<int>());

    std::cout << resolver(vc) << "\n";

    return true;
}

int main() {
#ifndef DOMJUDGE
    std::ifstream in("../exa-16sep/datos-1.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    while(resultCase());

#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif

    return 0;
}