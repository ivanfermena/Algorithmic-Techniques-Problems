// Ivan Fernandez Mena
// E48

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <algorithm>

/**
 *
 * Pero si miramos el problema completo el coste es Nlog(N) por tener que ordenar previamente antes de usar esos vectores.
 * Donde 0(Nlog(N)) donde N es el numero de elementos, es decir, distancia(primero, ultimo), siguiendo el metodo sort.
 *
 */

struct Hour{
    int hor;
    int min;
    Hour(int h, int m):hor(h), min(m){}
    Hour():hor(0), min(0){}
};

inline std::istream & operator >> (std::istream & in, Hour & rhs) {
    int horas, minutos;
    char auxChar = ':';
    in >> horas >> auxChar >> minutos;
    rhs = Hour(horas, minutos);
    return in;
}

bool operateInterval(Hour const& a, Hour const& b){
    if (a.hor < b.hor)
        return false;
    else if (a.hor == b.hor && a.min < b.min)
        return false;
    else if (a.hor == b.hor && a.min == b.min)
        return false;

    return true;
}

int seleccion_tunnel(std::vector<Hour> const &flats) {

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

    int hoursNumber;
    long int elemIni, elemEnd;

    std::cin >> hoursNumber;

    if(hoursNumber == 0)
        return false;

    std::vector<Hour> flats;

    for(int i = 0; i < hoursNumber; ++i ){
        std::cin >> elemIni >> elemEnd;
        flats.push_back(Hour(elemIni, elemEnd));
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