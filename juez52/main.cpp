// Ivan Fernandez Mena
// E48

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <algorithm>

/**
 * En este problema lo que se ha solicitado es la maxima diferencia que podrian llegar los Broncos en la liga. Para esto
 * es necesario guardar los resultados de cada uno de los quipos en dos vectores, el vector de Broncos y el del rival.
 * Para obtener una maxima diferencia lo que se tiene que hacer es comparar los elementos de los broncos mas grandes con
 * los mas pequeños de los rivales. Comprobando en no sumar las derrotas.
 *
 * Para esto el vector de los Broncos se ha ordenado de mayor a menos y el de rivales con sort normal (creciente).
 *
 * Pero si miramos el problema completo el coste es Nlog(N) por tener que ordenar previamente antes de usar esos vectores.
 * Donde 0(Nlog(N)) donde N es el numero de elementos, es decir, distancia(primero, ultimo), siguiendo el metodo sort.
 *
 */

int best_win(std::vector<int> const &broncos, std::vector<int> const &rival) {

    int N = broncos.size();
    int sum_dif = 0;

    for (int i = 0; i < N; ++i) {
        if(broncos[i] > rival[i])
            sum_dif += broncos[i] - rival[i];
    }
    return sum_dif;
}

bool resuelveCaso() {

    int N;

    std::cin >> N;

    if(N == 0)
        return false;

    std::vector<int> broncos(N), rival(N);

    for(int & resulRival: rival ){
        std::cin >> resulRival;
    }

    for(int & resulBroncos: broncos ){
        std::cin >> resulBroncos;
    }

    // Ordenamos los vectores
    std::sort(broncos.begin(), broncos.end(), std::greater<int>());
    std::sort(rival.begin(), rival.end());

    std::cout << best_win(broncos, rival) << "\n";

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