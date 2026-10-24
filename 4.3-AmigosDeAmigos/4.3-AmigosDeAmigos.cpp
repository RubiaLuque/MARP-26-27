/*@ <authors>
 *
 * MARP64 Muxu Rubia
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

#include "Grafo.h"  // propios o los de las estructuras de datos de clase

/*@ <answer>

 Buscar la maxima componente conexa del grafo. Se hace un recorrido en profundidad (DFS) del grafo y se almacena en tamaño del grupo mas
 grande encontrado hasta el momento. Coste O(N+M) donde N es el numero de personas y M el numero de conexiones entre ellas

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

class MaxCompConexa {
private:
    vector<bool> visit;
    int max;

    //O(V+A)
    int dfs(Grafo const& g, int v) {
        visit[v] = true;
        int tam = 1; //tam es 1 porque se añade un amigo más (v) al grupo en el que este v

        for (int w : g.ady(v)) {
            if (!visit[w])
                tam += dfs(g, w);
        }

        return tam;
    }

public:
    //O(V+A)
    MaxCompConexa(Grafo const& g) : visit(g.V(), false), max(0) {

        //Se recorren todos los vertices
        //O(V+A) porque ninguna arista o vertice se recorre mas de una vez
        for (int v = 0; v < g.V(); ++v) {
            if (!visit[v]) { //Si un vertice no estaba visitado, se trata como una nueva componente conexa
                int tam = dfs(g, v);

                if (tam > max) max = tam; //Si esta nueva componente es mayor que la anterior se actualiza el maximo
            }
        }
    }

    int getMax() {
        return max;
    }

};

void resuelveCaso() {

    // leer los datos de la entrada
    //N = num personas ciudad (vertices)
    //M = num pares personas que se conocen (aristas)
    int N, M;
    cin >> N >> M;

    Grafo g = Grafo(N);

    int v, w;
    //O(M)
    for (int i = 0; i < M; ++i) {
        cin >> v >> w;
        g.ponArista(v - 1, w - 1); //Los datos empiezan en 1 pero en los grafos en 0
    }

    // resolver el caso posiblemente llamando a otras funciones
    MaxCompConexa m(g); //O(N+M)

    int max = m.getMax();
    // escribir la solución
    cout << max << '\n';
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
