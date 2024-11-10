#include <iostream>
using namespace std;

class Graph {
   public:
    int vertices;
    bool** adjMatrix;

    Graph(int v) {
        vertices = v;
        adjMatrix = new bool*[v];
        for (int i = 0; i < v; i++) {
            adjMatrix[i] = new bool[v];
            for (int j = 0; j < v; j++) {
                adjMatrix[i][j] = false;
            }
        }
    }

    void addEdge(int u, int v) {
        adjMatrix[u][v] = true;
        adjMatrix[v][u] = true;
    }

    bool isSafe(int v, int path[], int pos) {
        if (adjMatrix[path[pos - 1]][v] == false) return false;
        for (int i = 0; i < pos; i++) {
            if (path[i] == v) return false;
        }
        return true;
    }

    bool hamiltonianPathUtil(int path[], int pos) {
        if (pos == vertices) return true;

        for (int v = 0; v < vertices; v++) {
            if (isSafe(v, path, pos)) {
                path[pos] = v;
                if (hamiltonianPathUtil(path, pos + 1)) return true;
                path[pos] = -1;
            }
        }
        return false;
    }

    bool findHamiltonianPath() {
        int* path = new int[vertices];
        for (int i = 0; i < vertices; i++) path[i] = -1;

        path[0] = 0;

        if (hamiltonianPathUtil(path, 1)) {
            for (int i = 0; i < vertices; i++) {
                cout << path[i] << " ";
            }
            cout << endl;
            delete[] path;
            return true;
        }

        delete[] path;
        return false;
    }
};

int main() {
    Graph g(5);
    g.addEdge(0, 1);
    g.addEdge(0, 3);
    g.addEdge(1, 2);
    g.addEdge(1, 3);
    g.addEdge(2, 4);
    g.addEdge(3, 4);

    if (g.findHamiltonianPath())
        cout << "No Hamiltonian Path exists" << endl;
    else
        cout << "Hamiltonian Path exists" << endl;

    return 0;
}
