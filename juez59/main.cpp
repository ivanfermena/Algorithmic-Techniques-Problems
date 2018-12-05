// Ivan Fernandez Mena
// E48

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <algorithm>

/**
 * El problema trata de como unos invasores ocupan una ciudad y necesitas colocar los defensas. Se trata de un porblema
 * de obtener el maximo numero de defensas. He usado para la resolucion dos vectores ordenados de menor a mayor y los he
 * ido comparando con dos indices. De tal modo que siempre se asigna si se puede la defensa mas pequeña a la invasion
 * mas pequeña.
 *
 * Pero si miramos el problema completo el coste es Nlog(N) por tener que orden ar previamente antes de usar esos vectores.
 * Donde 0(Nlog(N)) donde N es el numero de elementos, es decir, distancia(primero, ultimo), siguiendo el metodo sort.
 *
 */

int best_defend(std::vector<int> const &invaders, std::vector<int> const &defends) {

    int N = invaders.size();
    int sum = 0;

    int j = 0;
    for (int i = 0; i < defends.size(); ++i) {
        if(defends[i] >= invaders[j]){
            sum++;
            j++;
        }
    }
    return sum;
}

bool resuelveCaso() {

    int N;

    std::cin >> N;

    if(!std::cin)
        return false;

    std::vector<int> invaders(N), defends(N);

    for(int & auxInvaders: invaders ){
        std::cin >> auxInvaders;
    }

    for(int & auxDefenders: defends ){
        std::cin >> auxDefenders;
    }

    // Ordenamos los vectores
    std::sort(invaders.begin(), invaders.end());
    std::sort(defends.begin(), defends.end());

    std::cout << best_defend(invaders, defends) << "\n";

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