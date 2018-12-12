// Ivan Fernandez Mena
// E48

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <algorithm>
#include "Matriz.h"

/**
 *      game(i,j) = "Maximo valor en la casilla i para aquellos j, j-1 e j+1 casillas"
 *
 *      game(i,j) = max(max(game(i-1,j),game(i-1,j-1)), game(i-1, j+1)) + mValues[i][j]
 *
 *
 *      Caso base =     -> game(0,j) = 0     0 <= j <= n
 *                      -> game(i,0) = 0     0 <= i <= n
 *
 *
 *
 *      Coste total: EL coste del problema es O(n2) ya que cada elemento se opera una unica vez y en una matriz.
 *      Se realizan las tres operaciones j, j-1 y j+1 pero son constantes y se recorre la ultima fila pero es un coste
 *      O(n) frente a un coste cuadratico.
 *
 */

void bestPlay( Matriz<int> const & gameTable, int & maxSol, int & solPosition) {

    Matriz<int> game(gameTable.numfils()+1, gameTable.numcols()+2, 0);

    for (int i = 1; i < game.numfils(); ++i) {
        for (int j = 1; j < game.numcols()-1; ++j) {
            game[i][j] = std::max( std::max( game[i-1][j-1], game[i-1][j]), game[i-1][j+1]) + gameTable[i-1][j-1];
        }
    }

    for (int n = 1; n < game.numcols()-1; ++n) {
        if(maxSol < game[game.numfils()-1][n]){
            maxSol = game[game.numfils()-1][n];
            solPosition = n;
        }
    }
}

bool resuelveCaso() {

    int nRowColum;

    std::cin >> nRowColum;

    if(!std::cin)
        return false;

    Matriz<int> gameTable(nRowColum, nRowColum, 0);


    int valueTable;
    for (int i = 0; i < gameTable.numfils(); ++i) {
        for (int j = 0; j < gameTable.numcols(); ++j) {
            std::cin >> valueTable;
            gameTable[i][j] = valueTable;
        }
    }

    int maxSol = 0, solPosition = 0;

    bestPlay(gameTable, maxSol, solPosition);

    std::cout << maxSol << " " << solPosition << "\n";

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