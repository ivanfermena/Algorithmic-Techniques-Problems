// Ivan Fernandez Mena
// E48

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <algorithm>
#include "Matriz.h"

#define INF 1000000

/**
 *      game(i,j) = "Maximo valor de la suma de celdas de 1 al i en la posicion j "
 *
 *      game(i,j) =     -> game(i,j) si "v[i][j] > j"                                 (si no cabe P[i])
 *                      -> max(chest(i-1,j), chest(i-1,j-(2*P[i] + P[i])) + vi) si "P[i] <= j"
 *
 *      Caso base =     -> posible(0,j) = 0     0 <= j <= M
 *                      -> posible(i,0) = 0     0 <= i <= n
 *
 */

void best_chest(std::vector<int> const& P, std::vector<int> const& V, int M, int & valor, std::vector<bool> & cuales, int & countChest) { // P y V 1-based

    int n = P.size() - 1;

    Matriz<int> mochila(n+1, M+1, 0);

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= M; ++j) {
            if ((2*P[i] + P[i]) > j)
                mochila[i][j] = mochila[i-1][j];
            else
                mochila[i][j] = std::max(mochila[i-1][j], mochila[i-1][j - (2*P[i] + P[i])] + V[i]);
            }
        }

        valor = mochila[n][M];

        // cálculo de los objetos
        int resto = M;

        for (int i = n; i >= 1; --i) {
            if (mochila[i][resto] == mochila[i-1][resto]) { // no cogemos objeto i
                cuales[i] = false;
            } else {                                        // sí cogemos objeto i
                cuales[i] = true;
                countChest++;
                resto = resto - (2*P[i] + P[i]);
            }
        }
}

bool resuelveCaso() {

    int oxigenMax, numChests;

    std::cin >> oxigenMax;

    if(!std::cin)
        return false;

    std::cin >> numChests;

    std::vector<int> vcProfundity(numChests + 1);
    std::vector<int> vcGolds(numChests + 1);

    for(int i = 1; i <= numChests; i++){
        int auxProf, auxGold;
        std::cin >> auxProf >> auxGold;
        vcProfundity[i] = auxProf;
        vcGolds[i] = auxGold;
    }

    int maxGold = 0, countChest = 0;

    std::vector<bool> chestSelected(numChests);

    // Primer apartado
    best_chest(vcProfundity, vcGolds, oxigenMax, maxGold, chestSelected, countChest);

    std::cout << maxGold << "\n";
    std::cout << countChest << "\n";
    for (int j = 1; j <= chestSelected.size(); ++j) {
        if(chestSelected[j])
            std::cout << vcProfundity[j] << " " << vcGolds[j] << "\n";
    }

    std::cout << "----\n";

    return true;
}

int main() {
#ifndef DOMJUDGE
    std::ifstream in("datos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    while (resuelveCaso());

#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif

    return 0;
}