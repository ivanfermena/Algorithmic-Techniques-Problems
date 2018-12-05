// Ivan Fernandez Mena
// E48

#include <iostream>
#include <iomanip>
#include <fstream>
#include "Grafo.h"
#include <queue>
#include <string>
#include <vector>

using Mapa = std::vector<std::string>; // grafo implícito en el mapa

class Manchas {
public:
    Manchas(Mapa const& M) : F(M.size()), C(M[0].size()), marked(F, std::vector<bool>(C, false)), _numero(0), _maximo(0) {
        for (int i = 0; i < F; ++i) {
            for (int j = 0; j < C; ++j) {
                if (M[i][j] == '.' && !marked[i][j]) {
                    // se recorre una nueva mancha
                    int nuevotam = 0;
                    dfs(M, i, j, nuevotam);
                    ++_numero;
                }
            }
        }
    }
    int numero() const { return _numero-1; }

    int maximo() const { return _maximo; }

    private:
        int F, C; // tamaño del mapa
        std::vector<std::vector<bool>> marked; // marked[i][j] = se ha visitado <i,j>?
        int _numero; // número de manchas
        int _maximo; // tamaño de la mancha más grande

        bool correcta(int i, int j) const {
            return 0 <= i && i<F && 0 <= j && j < C;
        }

    const std::vector<std::pair<int,int>> dirs = {{1,0},{0,1},{-1,0},{0,-1}};

     // recorrido en profundidad de la mancha del vértice <i,j>
        void dfs(Mapa const& M, int i, int j, int & tam) {
            marked[i][j] = true;
            ++tam;
            for (auto d : dirs) {
                int ni = i + d.first, nj = j + d.second;
                if (correcta(ni,nj) && M[ni][nj] == '.' && !marked[ni][nj]) {
                    dfs(M, ni, nj, tam);
                }
            }
        }
};

void insertMap(Mapa & mapa, int rows){
    int num_count = 0;
    for (std::string & linea : mapa ) {
        if(num_count >= rows) return;
        std::cin >> linea;
        num_count++;
    }
}

bool resuelveCaso() {

    int rows, columns;

    std::cin >> columns >> rows;

    if(!std::cin)
        return false;

    Mapa mapa(rows);
    // leemos la imagen

    insertMap(mapa, rows);

    // y la analizamos
    Manchas manchas(mapa);
    std::cout << manchas.numero() << '\n';

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