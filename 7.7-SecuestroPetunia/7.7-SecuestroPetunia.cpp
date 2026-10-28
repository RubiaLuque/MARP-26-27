/*@ <authors>
 *
 * E86 Nombre Apellidos
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>
#include <limits>
using namespace std;

#include "DigrafoValorado.h"  // propios o los de las estructuras de datos de clase
#include "IndexPQ.h"

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

class Dijikstra {
private:
    const int64_t INF = std::numeric_limits<int64_t>::max();
    vector<int> origenes;
    vector<int64_t> dist;
    IndexPQ<int64_t> pq;

    void relajar(AristaDirigida<int64_t> a) {
        int v = a.desde(), w = a.hasta();
        if (dist[w] > dist[v] + a.valor()) {
            dist[w] = dist[v] + a.valor();
            pq.update(w, dist[w]);
        }
    }

public:
    Dijikstra(DigrafoValorado<int64_t> const& g, vector<int> const& origenes) : origenes(origenes), dist(g.V(), INF), pq(g.V()) {
        for (int64_t i = 0; i < origenes.size(); ++i) {
            dist[origenes[i]] = 0;
            pq.push(origenes[i], 0);
        }

        while (!pq.empty()) {
            int v = pq.top().elem; pq.pop();
            for (auto a : g.ady(v)) {
                relajar(a);
            }
        }
    }

    int64_t distancia(int v) const { return dist[v]; }
};

void resuelveCaso() {
    int64_t T; //Tiempo maximo (umbral)
    cin >> T;
    int P, C; //P->num vertices, C->num aristas
    cin >> P >> C;
    
    DigrafoValorado<int64_t> g(P);
    int origen, destino;
    int64_t valor;
    for (int i = 0; i < C; ++i) {
        cin >> origen >> destino >> valor;
        g.ponArista({ origen - 1, destino - 1, valor });
        g.ponArista({ destino - 1, origen -1, valor });
    }

    int B;
    cin >> B;
    int pueblo;
    vector<int> pueblosBorriquin(B);
    for (int i = 0; i < B; ++i) {
        cin >> pueblo;
        pueblosBorriquin[i] = pueblo-1;
    }

    //O(PlogC)
    Dijikstra dj(g, pueblosBorriquin);

    int alcanzables = 0;
    //O(P)
    for (int i = 0; i < P; ++i) {
        if (dj.distancia(i) <= T) {
            alcanzables++;
        }
    }
    
    cout << alcanzables << '\n';
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
