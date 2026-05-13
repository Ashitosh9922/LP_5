
#include <iostream>
#include <vector>
#include <queue>
#include <omp.h>
using namespace std;

class Graph {
    int V;
    vector<vector<int>> adj;

public:
    Graph(int V) {
        this->V = V;
        adj.resize(V);
    }

    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u); // undirected graph
    }

    void parallelBFS(int start) {
        vector<int> visited(V, 0);
        queue<int> q;

        visited[start] = 1;
        q.push(start);

        cout << "Parallel BFS: ";

        while (!q.empty()) {
            int size = q.size();

            #pragma omp parallel for
            for (int i = 0; i < size; i++) {
                int node=-1;

                #pragma omp critical
                {
                    if (!q.empty()) {
                        node = q.front();
                        q.pop();
                        cout << node << " ";
                    }
                }
                if(node == -1)
    continue;

                for (int neighbor : adj[node]) {
                    if (!visited[neighbor]) {
                        #pragma omp critical
                        {
                            if (!visited[neighbor]) {
                                visited[neighbor] = 1;
                                q.push(neighbor);
                            }
                        }
                    }
                }
            }
        }
        cout << endl;
    }
};

int main() {
    int V, E;
    cout << "Enter number of vertices and edges: ";
    cin >> V >> E;

    Graph g(V);

    cout << "Enter edges (u v):\n";
    for (int i = 0; i < E; i++) {
        int u, v;
        cin >> u >> v;
        g.addEdge(u, v);
    }

    int start;
    cout << "Enter starting vertex: ";
    cin >> start;

    g.parallelBFS(start);

    return 0;
}
/*1. Compile the program
g++ -fopenmp bfs.cpp -o bfs
2. Run the program
./bfs
✅ On Windows (MinGW / MSYS2)
1. Compile
g++ -fopenmp bfs.cpp -o bfs.exe
2. Run
bfs.exe*/
 
