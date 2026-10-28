/*@ <authors>
 *
 * MARP64 Muxu Rubia
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>
#include <deque>
#include <cstdint>
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


class Djkstra {
private:
    const int INF = INT32_MAX;
    int orig;
    vector<int> dist;
    vector<AristaDirigida<int>> ulti;
    IndexPQ<int> pq; //(vertice, distancia a orig) --> la prioridad de un vertice se mide con respecto a su distancia a origen

    void relajar(AristaDirigida<int> a) {
        int v = a.desde(), w = a.hasta();
        //Si la distancia previa a w era mayor que la encontrada con la arista 'a', nos quedamos con la distancia que utiliza a 'a'
        if (dist[w] > dist[v] + a.valor()) {
            dist[w] = dist[v] + a.valor();
            ulti[w] = a;
            pq.update(w, dist[w]); //O(logV)
        }
    }

public:
    //O(AlogV) siendo A num aristas y V num vertices
    Djkstra(DigrafoValorado<int> const& g, int orig) : orig(orig), dist(g.V(), INF), ulti(g.V()), pq(g.V()) {
        dist[orig] = 0;
        pq.push(orig, 0);
        while (!pq.empty()) {
            int v = pq.top().elem;
            pq.pop(); //O(logV) siendo V el numero de vertices
            for (auto a : g.ady(v)) {
                relajar(a);
            }
        }
    }

    bool hayCamino(int v) const {
        return dist[v] != INF;
    }

    int distancia(int v) const {
        return dist[v];
    }
    
    deque<AristaDirigida<int>> camino(int v) const {
        deque<AristaDirigida<int>> cam;
        AristaDirigida<int> a;
        for (a = ulti[v]; a.desde() != orig; a = ulti[a.desde()]) {
            cam.push_front(a);
        }

        cam.push_front(a);
        return cam;
    }
};


void resuelveCaso() {

    //N --> num vertices (ptos entrega, carga...)
    //C --> num aristas (calles)
    int N, C;
    cin >> N >> C;

    DigrafoValorado<int> g = DigrafoValorado<int>(N);

    int v, w, t;
    for (int i = 0; i < C; ++i) {
        cin >> v >> w >> t;
        g.ponArista({ v-1, w-1, t });
        g.ponArista({ w - 1, v - 1, t });
    }

    //K --> Num pedidos: num consultas
    int K, orig, dest;
    cin >> K;
    //O(K*C*logN)
    for (int i = 0; i < K; ++i) {
        cin >> orig >> dest;
        Djkstra dj(g, orig - 1); //O(ClogN)
        //Si existe camino de origen a destino
        if (dj.hayCamino(dest - 1)) {
            cout << dj.distancia(dest - 1) << ": ";
            auto cam = dj.camino(dest - 1);
            while (!cam.empty()) {
                cout << cam.front().desde() + 1 << " -> ";
                cam.pop_front();
            }

            cout << dest << '\n';
        }
        else {
            cout << "NO LLEGA\n";
        }
    }

    cout << "---\n";

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
