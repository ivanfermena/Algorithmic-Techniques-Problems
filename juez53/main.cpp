// Ivan Fernandez Mena
// E48

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <algorithm>

int seleccion_batery(std::vector<long int> const &cars, long int Vn) {

    int N = cars.size();
    int count_cars = 0;
    int j_max = N-1;

    int i = 0;
    for (; i < N && i < j_max; ++i) {
        if(cars[i] + cars[j_max] >= Vn){
            count_cars++;
            j_max--;
        }
    }

    return count_cars;
}

void resuelveCaso() {

    int Np;
    long int Vn;

    std::cin >> Np >> Vn;

    std::vector<long int> cars(Np);

    for(long int & car: cars){
        std::cin >> car;
    }

    // Ordenamos los vectores
    std::sort(cars.begin(), cars.end());

    std::cout << seleccion_batery(cars, Vn) << "\n";

}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    std::ifstream in("datos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif

    int numCases = 0;
    std::cin >> numCases;
    for (int i = 0; i < numCases; ++i) {
        resuelveCaso();
    }

    // Para restablecer entrada. Comentar para acepta el reto
#ifndef DOMJUDGE // para dejar todo como estaba al principio
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif

    return 0;
}