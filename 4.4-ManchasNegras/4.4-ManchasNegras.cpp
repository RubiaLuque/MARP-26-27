/*@ <authors>
 *
 * MARP64 Muxu Rubia
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

/*@ <answer>

 Grafo implicito. Recorrido DFS intentando encontrar la maxima componente conexa.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

class ManchasNegras {
private:
    int F, C;
    vector<vector<bool>> visit;
    int maxMancha;
    int numManchas;

    const vector<pair<int, int>> dirs = { {0,-1}, {-1, 0}, {1, 0}, {0, 1} }; //Posibles direcciones

    //O(F+C)
    int dfs(vector<string> const& bitmap, int i, int j) {
        visit[i][j] = true;
        int tam = 1;

        for (auto d : dirs) {
            int dir_i = i + d.first;
            int dir_j = j + d.second;

            //Debe cumplirse:
            // - Posicion valida dentro del bitmap
            // - Que sea una mancha (#)
            // - Que no haya sido visitada antes
            if (dirCorrecta(i + d.first, j + d.second) && bitmap[dir_i][dir_j] == '#' && !visit[dir_i][dir_j]) {
                tam += dfs(bitmap, dir_i, dir_j);
            }
        }

        return tam;

    }

    bool dirCorrecta(int i, int j) const {
        if (i < 0 || i >= F || j < 0 || j >= C) return false;
        else return true;
    }

public:
    //O(F*C + F + C)
    ManchasNegras(vector<string> const& bitmap) : F(bitmap.size()), C(bitmap[0].size()), visit(F, vector<bool>(C, false)), 
        maxMancha(0), numManchas(0) {

        //O(F + C)
        for (int i = 0; i < F; ++i) {
            for (int j = 0; j < C; ++j) {

                if (bitmap[i][j] == '#' && !visit[i][j]) { //Nueva componente conexa
                    numManchas++; //Aumenta el numero de manchas

                    int tam = dfs(bitmap, i, j); //Se obtiene el tamaño de la mancha nueva

                    if (tam > maxMancha) maxMancha = tam; //Se compara con el tamaño maximo existente
                }
            }
        }
    }

    //O(1)
    int getNumManchas() const {
        return numManchas;
    }

    //O(1)
    int getMaxMancha() const {
        return maxMancha;
    }
};

void resuelveCaso() {

    // leer los datos de la entrada
    int F, C;
    cin >> F >> C;

    vector<string> bitmap(F);

    //La linea que se lea se guarda en la linea correspondiente de bitmap
    for (string& l : bitmap) {
        cin >> l; 
    }

    // resolver el caso posiblemente llamando a otras funciones
    ManchasNegras m(bitmap);

    // escribir la solución
    cout << m.getNumManchas() << ' ' << m.getMaxMancha() << '\n';
}

//@ </answer>
//  Lo que se escriba debajo de esta línea ya no forma parte de la solución.

int main() {
    // entrada/salida rápida
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // ajustes para que cin extraiga directamente de un fichero (solamente en local)
#ifndef DOMJUDGE
    ifstream in("casos.txt");
    if (!in.is_open()) {
        cout << "Error: no se ha podido abrir el archivo de entrada." << endl;
        // sin fichero no hay nada que leer, y cin >> ... dejaría las
        // variables sin tocar, con su valor basura
        return 1;
    }
    auto cinbuf = cin.rdbuf(in.rdbuf());
#endif

    int numCasos;
    cin >> numCasos;
    for (int i = 0; i < numCasos; ++i)
        resuelveCaso();

    // para dejar todo como estaba al principio
#ifndef DOMJUDGE
    cin.rdbuf(cinbuf);
#endif
    return 0;
}
