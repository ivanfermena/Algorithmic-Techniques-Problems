// Ivan Fernandez Mena
// E48

#include <iostream>
#include <iomanip>
#include <fstream>
#include "TreeMap_AVL.h"
#include <vector>

void resuelveCaso(int numElem) {

    int elem, minimum, maximum;
    map<int, int> treeMap;

    // Insertamos los elementos de cada caso
    for (int i = 0; i < numElem; ++i) {
        std::cin >> elem;
        treeMap.insert(elem);
    }

    std::cin >> minimum >> maximum;

    std::vector<int> sol = treeMap.rangeToValues(minimum, maximum);

    for(int item: sol)
        std::cout << item << " ";
    std::cout << "\n";
}

// C:\Users\ivanf\CLionProjects\juez12\datos.txt

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    std::ifstream in("datos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif

    int numControl;
    std::cin >> numControl;
    while (numControl != 0) {
        resuelveCaso(numControl);
        std::cin >> numControl;
    }

    // Para restablecer entrada. Comentar para acepta el reto
#ifndef DOMJUDGE // para dejar todo como estaba al principio
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif

    return 0;
}