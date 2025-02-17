﻿// Ivan Fernandez Mena
// E48

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <algorithm>

#define INF 1000000000

/**
 * En este proble ase tienen N varillas de longitud li con cada una un precio de ci. Se busca sin la posibilidad de romperlas
 * colocar las varillas para hacer una de longitud L. El problema viene dado con diferentes cuestiones cortas que hay que
 * resolver individualmente. En cada uno de los apartados se realizara una explicacion de la recursion.
 *
 * Coste total --> O(4(L)) --> O(L)
 *
 * Apartado 1:
 *
 *      posible(i,l) = "Es posible tener l con [0...i] varillas"
 *
 *      posible(i,l) =  -> posible(i-1,l) si "l[i] > l"                           (si no cabe li)
 *                      -> posible(i-1,l) && posible(i-1,l-l[i]) si "li <= j"
 *
 *      Caso base =     -> posible(0,l) = false j > 0
 *                      -> posible(i,0) = true 0 >= i
 *
 */


// Indicar si es posible o no obtener la varilla deseada soldando algunas de las varillas dadas

bool isPosible(std::vector<int> const & vc, int L){

    int n = vc.size();
    std::vector<bool> m(L+1, false);
    m[0] = true;

    for (int i = 1; i <= n; i++) {
        for (int l = L; l >= 1; l--) {
            if(vc[i-1] <= l)
                m[l] = m[l] || m[l - vc[i-1]];
        }
    }
    return m[L];
}

/**
* Apartado 2:
*
*      formar(i,l) = "Numero total de maneras de obtener l con [0...i] varillas"
*
*      formar(i,l) =  -> formar(i-1,l) si "l[i] > l"                           (si no cabe li)
*                      -> formar(i-1,l) + formar(i-1,l-l[i]) si "li <= j"
*
*      Caso base =     -> formar(0,l) = 0 j > 0
*                      -> formar(i,0) = 1 0 >= i
*/

// Calcular el numero total de maneras de obtener la varilla deseada soldando algunas de las varillas dadas, sin que importe el orden de soldadura.
int formar(std::vector<int> const & vc, int L){

    int n = vc.size();
    std::vector<int> m(L+1, 0);
    m[0] = 1;

// rellenar la matriz
    for (int i = 1; i <= n; i++) {
        for (int l = L; l >= 1; l--) {
            if(vc[i-1] <= l) {
                m[l] = m[l] + m[l - vc[i - 1]];
            }
        }
    }
    return m[L];
}

/**
* Apartado 3:
*
*      formar(i,l) = "Numero minimo de varillas con l para [0...i] varillas"
*
*      formar(i,l) =  -> formar(i-1,l) si "l[i] > l"                           (si no cabe li)
*                     -> formar(i-1,l) + formar(i-1,l-l[i]) + 1 si "li <= j"
*
*      Caso base =     -> formar(0,l) = INF j > 0
*                      -> formar(i,0) = 0 0 >= i
*/

// Calcular el numero mınimo de varillas necesarias para obtener la varilla deseada.
int minimo(std::vector<int> const & vc, int L){

    int n = vc.size();
    std::vector<int> m(L+1, INF);
    m[0] = 0;

    for (int i = 1; i <= n; i++) {
        for (int l = L; l >= 1; l--) {
            if(vc[i-1] <= l)
                m[l] = std::min(m[l], m[l - vc[i-1]] + 1);
        }
    }
    return m[L];
}

/**
* Apartado 4:
*
*      formar(i,l) = "Numero minimo de coste con l para [0...i] varillas"
*
*      formar(i,l) =  -> formar(i-1,l) si "l[i] > l"                           (si no cabe li)
*                     -> formar(i-1,l) + formar(i-1,l-l[i]) + c[i] si "li <= j"
*
*      Caso base =     -> formar(0,l) = INF j > 0
*                      -> formar(i,0) = 0   0 >= i
*/

// Calcular el mınimo coste posible necesario para obtener la varilla deseada
int suma(std::vector<int> const & vc, std::vector<int> const & vcCostes, int L){

    int n = vc.size();
    std::vector<int> m(L+1, INF);
    m[0] = 0;

    for (int i = 1; i <= n; i++) {
        for (int l = L; l >= 1; l--) {
            if(vc[i-1] <= l)
                m[l] = std::min(m[l], m[l - vc[i-1]] + vcCostes[i-1]);
        }
    }
    return m[L];
}




bool resuelveCaso() {

    int numVarillas, longVarilla;

    std::cin >> numVarillas >> longVarilla;

    if(!std::cin)
        return false;

    std::vector<int> longVarillas;
    std::vector<int> costVarillas;

    for(int i = 0; i < numVarillas; i++){
        int auxLong, auxCost;
        std::cin >> auxLong >> auxCost;
        longVarillas.push_back(auxLong);
        costVarillas.push_back(auxCost);
    }

    // Primer apartado

    if(isPosible(longVarillas, longVarilla)){
        std::cout << "SI " << formar(longVarillas, longVarilla) << " " << minimo(longVarillas, longVarilla) << " " << suma(longVarillas, costVarillas, longVarilla) << "\n";
    }else {
        std::cout << "NO" << "\n";
    }

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