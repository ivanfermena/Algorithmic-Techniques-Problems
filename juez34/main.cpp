// Ivan Fernandez Mena
// E48

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <string>

#include "ConjuntosDisjuntos.h"

using Map = std::vector<std::string>;

// grafo implícito en el mapa
class Manchas {
    public:
        Manchas(Map const& M) : rows(M.size()), columns(M[0].size()), marked(rows, std::vector<bool>(columns, false)),_maximo(0), conj(rows*columns) {
            for(int i = 0; i < rows; ++i) {
                for (int j = 0; j < columns; ++j) {
                    if (M[i][j] == '#' && !marked[i][j]) { // se recorre una nueva mancha
                        dfs(M, i, j);
                        _maximo = std::max(_maximo, std::abs(conj.tam(i * columns + j)));
                    }
                }
            }
        }

        int maximo() const { return _maximo; }

        void update(Map const& M, int i, int j){
            marked[i][j] = true;
            for (auto d : dirs) {
                int ni = i + d.first, nj = j + d.second;
                if (correcta(ni,nj) && M[ni][nj] == '#') {
                    conj.unir(i * columns + j , ni * columns + nj);
                }
            }
            _maximo = std::max(_maximo, std::abs(conj.tam(i * columns + j)));
        }

    private:
        int rows, columns;
        std::vector<std::vector<bool>> marked;
        int _maximo;
        ConjuntosDisjuntos conj;

        bool correcta(int i, int j) const {
            return 0<= i && i<rows && 0<= j && j<columns;
        }

        const std::vector<std::pair<int,int>> dirs = {{1,0},{0,1},{-1,0},{0,-1},{1,1},{-1,-1},{-1,1},{1,-1}};

        void dfs(Map const& M, int i, int j) {
            marked[i][j] = true;
            for (auto d : dirs) {
                int ni = i + d.first, nj = j + d.second;
                if (correcta(ni,nj) && M[ni][nj] == '#' && !marked[ni][nj]) {
                    conj.unir(i * columns + j , ni * columns + nj);
                    dfs(M, ni, nj);
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

    // Insertamos elementos

    int num_news_elem, new_row, new_colum;

    std::cin >> num_news_elem;

    for (int i = 0; i < num_news_elem; ++i) {
        std::cin >> new_row >> new_colum;

        std::string aux = map[new_row-1];
        aux[new_colum-1] = '#';
        map[new_row-1] = aux;

        manchas.update(map, new_row-1, new_colum-1);

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