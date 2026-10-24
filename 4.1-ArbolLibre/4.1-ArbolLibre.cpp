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

 Para que un grafo se arbol libre debe cumplirse que:
 - Conexo --> Todos los vertices estan visitados tras hacer un recorrido DFS desde origen (podria hacerse BFS tambien)
 - Aciclico --> Conexo y num aristas = num vertices - 1

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

class ArbolLibre {
private:
    vector<bool> visit;
    bool aciclico;

    //O(A+V) siendo A num aristas y V num vertices
    //Nos permite saber si todos los vertices son alcanzables desde un vertice origen rellenando visit --> Conexo
    void dfs(Grafo const& g, int v) {
        visit[v] = true; //se marca como visitado el vertice v
        //Se recorren todos los adyacentes a v mirando su lista de adyacencia
        for (int w : g.ady(v)) {
            //Si un adyacente no se ha visitado ya, se hace recursion sobre ese vertice
            if (!visit[w])
                dfs(g, w);
        }
    }

    bool esConexo() {
        for (int i = 0; i < visit.size(); ++i) {
            if (!visit[i]) return false;
        }
        return true;
    }

public:
    ArbolLibre(Grafo const& g) : visit(g.V(), false) {
        dfs(g, 0); //Se realiza un unico recorrido desde origen para saber si todos los vertices son alcanzables (conexo)
        aciclico = (g.A() == g.V() - 1) ? true : false;
    }

    bool esArbolLibre() {
        return esConexo() && aciclico;
    }

};


void resuelveCaso() {

    // leer los datos de la entrada
    Grafo g = Grafo(std::cin);

    // resolver el caso posiblemente llamando a otras funciones
    ArbolLibre l = ArbolLibre(g);
    bool aLibre = l.esArbolLibre();
    // escribir la solución
    if (aLibre)
        cout << "SI\n";
    else
        cout << "NO\n";
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
