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
    int minTime;
    Hour(int hour, int minu){
        minTime = (hour * 60) + minu;
    }
    Hour():minTime(0){}
};

struct Film{
    int hourIni;
    int hourEnd;

    Film(Hour iniTime, int endTime):hourIni(iniTime.minTime){
        hourEnd = iniTime.minTime + endTime;
    }
    Film():hourIni(0),hourEnd(0){}
};

bool operateInterval(Film const& a, Film const& b){
    return a.hourEnd < b.hourEnd;
}

inline std::istream & operator >> (std::istream & in, Hour & rhs) {
    int horas, minutos;
    char auxChar = ':';
    in >> horas >> auxChar >> minutos;
    rhs = Hour(horas, minutos);
    return in;
}

int seleccion_tunnel(std::vector<Film> const &flats) {

    int N = flats.size();
    int count_films = 1;
    long int last_end = flats[0].hourEnd;

    for (int i = 1; i < N; ++i) {
        if(last_end + 10 <= (flats[i].hourIni)){
            last_end = flats[i].hourEnd;
            count_films++;
        }
    }
    return count_films;
}

bool resuelveCaso() {

    int hoursNumber;
    Hour elemIni;
    int elemEnd;

    std::cin >> hoursNumber;

    if(hoursNumber == 0)
        return false;

    std::vector<Film> flats;

    for(int i = 0; i < hoursNumber; ++i ){
        std::cin >> elemIni >> elemEnd;
        flats.push_back(Film(elemIni, elemEnd));
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