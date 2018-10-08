// Ivan Fernandez Mena
// E48

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <string>

#include "Grafo.h"

using Map = std::vector<std::string>;

// grafo implícito en el mapa
class Manchas {
    public:
        Manchas(Map const& M) : rows(M.size()), columns(M[0].size()), marked(rows, std::vector<bool>(columns, false)), _numero(0), _maximo(0) {
            for(int i = 0; i < rows; ++i) {
                for (int j = 0; j < columns; ++j) {
                    if (M[i][j] == '#' && !marked[i][j]) { // se recorre una nueva mancha
                        ++_numero;
                        int nuevotam = 0;
                        dfs(M, i, j, nuevotam);
                        _maximo = std::max(_maximo, nuevotam);
                    }
                }
            }
        }

        void reordenar(Map const& M, int row, int column){
            cpy_marked = marked;
            int nuevotam = 0;
            new_dfs(M, row, column, nuevotam);
            _maximo = std::max(_maximo, nuevotam);
            marked[row][column] = true;
        }

        int maximo() const { return _maximo; }

    private:
        int rows, columns; // tamaño del mapa
        std::vector<std::vector<bool>> marked; // marked[i][j] = se ha visitado <i,j>?
        std::vector<std::vector<bool>> cpy_marked;
        int _numero; // número de manchas
        int _maximo; // tamaño de la mancha más grande

        bool correcta(int i, int j) const {
            return 0<= i && i<rows && 0<= j && j<columns;
        }

        const std::vector<std::pair<int,int>> dirs = {{1,0},{0,1},{-1,0},{0,-1},{1,1},{-1,-1},{-1,1},{1,-1}};
        // recorrido en profundidad de la mancha del vértice <i,j>

        void dfs(Map const& M, int i, int j, int & tam) {
            marked[i][j] = true;
            ++tam;
            for (auto d : dirs) {
                int ni = i + d.first, nj = j + d.second;
                if (correcta(ni,nj) && M[ni][nj] == '#' && !marked[ni][nj]) {
                    dfs(M, ni, nj, tam);
                }
            }
        }

        void new_dfs(Map const& M, int i, int j, int & tam){
            cpy_marked[i][j] = false;
            ++tam;
            for (auto d : dirs) {
                int ni = i + d.first, nj = j + d.second;
                if (correcta(ni,nj) && M[ni][nj] == '#' && cpy_marked[ni][nj]) {
                    new_dfs(M, ni, nj, tam);
                }
            }
        }
};

bool resuelveCaso() {
    int rows, columns;
    std::cin >> rows >> columns;

    if (!std::cin)
        return false;

    Map map(rows);

    std::string basura;
    getline(std::cin, basura);

    // leemos la imagen
    for (std::string & linea : map) {
        getline(std::cin, linea);
    }
    
    Manchas manchas(map);

    std::cout << manchas.maximo() << " ";

    // Insertamos tres elementos

    int num_news_elem, new_row, new_colum;

    std::cin >> num_news_elem;

    for (int i = 0; i < num_news_elem; ++i) {
        std::cin >> new_row >> new_colum;

        std::string aux = map[new_row-1];
        aux[new_colum-1] = '#';
        map[new_row-1] = aux;

        manchas.reordenar(map, new_row-1, new_colum-1);
        std::cout << manchas.maximo() << " ";
    }
    std::cout << "\n";

    return true;
}

int main() {
#ifndef DOMJUDGE
    std::ifstream in("datos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    while(resuelveCaso());

#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif

    return 0;
}