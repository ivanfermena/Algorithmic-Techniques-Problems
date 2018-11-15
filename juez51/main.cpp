// Ivan Fernandez Mena
// E48

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <algorithm>

/**
 * En este ejercicio lo que se solicita es la suma minima de la diferencia de la altura de los esquiadores y los esquis.
 * Para eso lo que se ha hecho es la creacion de dos vectores ordenados, uno con esquiadores y otro con esquis.
 * De este modo se hace la diferencia de manera ordenada de menos a menor, asi aseguramos que la diferencia es la minima
 * posible.
 *
 * El coste del algoritmo es lineal ya que solo ves una vez a cada elemento de los dos vectores. O(N), donde ana es el
 * numero de esquiadores y esquis.
 *
 * Pero si miramos el problema completo el coste es Nlog(N) por tener que ordenar previamente antes de usar esos vectores.
 * Donde 0(Nlog(N)) donde N es el numero de elemntos, es decir, distancia(primero, ultimo), siguiendo el metodo sort.
 *
 */

int champions(std::vector<long int> const &skiers, std::vector<long int> const &skis) {

    long int N = skiers.size();
    int sum_dif = 0;

    for (int i = 0; i < N; ++i) { // estamos en gi
            sum_dif += std::abs(skiers[i] - skis[i]);
    }
    return sum_dif;
}

bool resuelveCaso() {

    int N;

    std::cin >> N;

    if(N == 0)
        return false;

    std::vector<long int> skiers(N), skis(N);

    for(long int & skier: skiers ){
        std::cin >> skier;
    }

    for(long int & ski: skis ){
        std::cin >> ski;
    }

    // Ordenamos los vectores
    std::sort(skiers.begin(), skiers.end());
    std::sort(skis.begin(), skis.end());

    std::cout << champions(skiers, skis) << "\n";

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