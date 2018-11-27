// Ivan Fernandez Mena
// E48

/**
 * El problema quiere resolver con que orden tienen que subir una personas a los telefericos dobles. Te dan un maximo de
 * peso y este no se puede superar. El problema se ha resuelto con un vector comparando la suma del primero con el ultimo
 * con el maximo de peso que se puede llevar. Importante tener en cuenta que si no se puede entrar una persona, se tiene
 * que mover el indice final y sumar uno al numeor de sillas, ya que este no se podra emparejar con nadie.
 *
 * Tambien se tiene que controlar cuando solo te queda un elemento y los indices de control son de igual valor, sumando
 * uno al contador de sillas.
 *
 * Pero si miramos el problema completo el coste es Nlog(N) por tener que orden ar previamente antes de usar esos vectores.
 * Donde 0(Nlog(N)) donde N es el numero de elementos, es decir, distancia(primero, ultimo), siguiendo el metodo sort.
 *
 */


#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <algorithm>

int seleccion_chairs(std::vector<int> const &persons, int sizeMax) {

    int N = persons.size();
    int count_chairs = 0;

    int j_last = N-1;
    int i = 0;
    for (; j_last > i; --j_last) {
        if(persons[i] + persons[j_last] <= sizeMax){
            count_chairs++;
            i++;
        }else
            count_chairs++;
    }

    if(j_last == i)
        count_chairs++;

    return count_chairs;
}

bool resuelveCaso() {

    int sizeMax, N;

    std::cin >> sizeMax >> N;

    if(!std::cin)
        return false;

    std::vector<int> persons(N);

    for(int & auxPerson: persons){
        std::cin >> auxPerson;
    }

    // Ordenamos los vectores
    std::sort(persons.begin(), persons.end());

    std::cout << seleccion_chairs(persons, sizeMax) << "\n";

    return true;

}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    std::ifstream in("datos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif

    while(resuelveCaso());

    // Para restablecer entrada. Comentar para acepta el reto
#ifndef DOMJUDGE // para dejar todo como estaba al principio
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif

    return 0;
}