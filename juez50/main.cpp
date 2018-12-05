// Ivan Fernandez Mena
// E48

/**
 * En este porblema lo que se pide es un algoritmo voraz. Lo que se ha usado es un vector de agujeros, obtenidos desde la entrada y colocados en orden.
 * Para saber si un agjero se podia tapar se ha controlado con una variable, hasta que punto podia ocupar ese ultimo parche puesto. Si el sigueinte
 * agujero estaba fuera de ese parche, se actualizaba esa variable. Todo esto aumentando el contador de parches.
 *
 * El coste del algoritmo es lineal en el numero de parches O(N), ya que los exploramos y tratamos una unica vez y vemos todos.
 *
 */

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>

int hose(std::vector<long int> const& holes, int patch) {
    
    long int N = holes.size();
    int patches = 1;
    long int end_patch = holes[0] + patch; // Primer rango a partir del primer parche (siempre tiene un parche)

    for (int i = 1; i < N; ++i) { // estamos en gi
        if (holes[i] > end_patch) {
            ++patches;
            end_patch = holes[i] + patch;
        }
    }
    return patches;
}

bool resuelveCaso() {

    int N, L;

    std::cin >> N >> L;

    if(!std::cin)
        return false;

    std::vector<long int> holes(N);

    for(long int & hole: holes ){
        std::cin >> hole;
    }

    std::cout << hose(holes, L) << "\n";

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