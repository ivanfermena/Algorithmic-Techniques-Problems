// Ivan Fernandez Mena
// E48

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <algorithm>

/**
 * En este problema lo que se ha solicitado es saber cuanto es el minimo de tuneles hacen falta para que todos los
 * edificios esten conectados con la playa. Hemos usado una estructura con el tamaño de los edificios. Hemos ordenado
 * por el final de los edificios y se ha ido comprobando que el inicio este dentro del tunel para no generar uno nuevo.
 *
 * Pero si miramos el problema completo el coste es Nlog(N) por tener que ordenar previamente antes de usar esos vectores.
 * Donde 0(Nlog(N)) donde N es el numero de elementos, es decir, distancia(primero, ultimo), siguiendo el metodo sort.
 *
 */

struct sizeFlat {
    long int ini;
    long int end;
    sizeFlat(long int i, long int e): ini(i), end(e){}
    sizeFlat(): ini(0), end(0){}
};


bool operateInterval(sizeFlat const& a, sizeFlat const& b){
    return a.end < b.end;
}

int seleccion_tunnel(std::vector<sizeFlat> const &flats) {

    int N = flats.size();
    int count_tunnel = 1;
    long int last_end = flats[0].end;

    for (int i = 1; i < N; ++i) {
        if(flats[i].ini >= last_end){
            last_end = flats[i].end;
            count_tunnel++;
        }
    }
    return count_tunnel;
}

bool resuelveCaso() {

    int flatsNumber;
    long int elemIni, elemEnd;

    std::cin >> flatsNumber;

    if(flatsNumber == 0)
        return false;

    std::vector<sizeFlat> flats;

    for(int i = 0; i < flatsNumber; ++i ){
        std::cin >> elemIni >> elemEnd;
        flats.push_back(sizeFlat(elemIni, elemEnd));
    }

    // Ordenamos los vectores
    std::sort(flats.begin(), flats.end(), operateInterval);

    std::cout << seleccion_tunnel(flats) << "\n";

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