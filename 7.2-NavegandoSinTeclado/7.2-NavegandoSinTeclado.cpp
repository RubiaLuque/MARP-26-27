/*@ <authors>
 *
 * E86 Nombre Apellidos
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>
#include <cstdint>
using namespace std;

#include "DigrafoValorado.h"  // propios o los de las estructuras de datos de clase
#include "IndexPQ.h"

/*@ <answer>

 Se resuelve haciendo Djkstra desde origen hasta destino (N). Con un coste en tiempo de O(MlogN) siendo M el numero de aristas y N el de vertices y 
 en espacio adicional de O(N) por la lista de prioridad y O(N) por el vector de guardado de tiempos de carga.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

class Djkstra {
private:
    const int INF = INT32_MAX;
    int orig;
    vector<int> dist;
    IndexPQ<int> pq;

    void relaja(AristaDirigida<int> a) {
        int v = a.desde();
        int w = a.hasta();
        if (dist[w] > dist[v] + a.valor()) {
            dist[w] = dist[v] + a.valor();
            pq.update(w, dist[w]);
        }
    }

public:
    Djkstra(DigrafoValorado<int> const& g, int orig, int distOrig) : dist(g.V(), INF), orig(orig), pq(g.V()) {
        dist[orig] = distOrig;
        pq.push(orig, distOrig);

        while (!pq.empty()) {
            int v = pq.top().elem;
            pq.pop();
            for (auto a : g.ady(v)) {
                relaja(a);
            }
        }
    }

    bool hayCamino(int v) const {
        return dist[v] != INF;
    }

    int distancia(int v) const {
        return dist[v];
    }


};

void resuelveCaso() {

    int N; //num pags web (vertices)
    cin >> N;
    vector<int> tCarga(N); 
    
    int t;
    for (int i = 0; i < N; ++i) {
        cin >> t;
        tCarga[i] = t;
    }

    DigrafoValorado<int> g(N);
    int M; //num enlaces (aristas)
    cin >> M;
    int v, w, valor;
    for (int i = 0; i < M; ++i) {
        cin >> v >> w >> valor;
        g.ponArista({ v - 1, w - 1, valor + tCarga[w-1]});
    }
    
    Djkstra d(g, 0, tCarga[0]); //O(MlogN)

    if (d.hayCamino(N - 1)) {
        cout << d.distancia(N - 1) << '\n';
    }
    else {
        cout << "IMPOSIBLE\n";
    }

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
