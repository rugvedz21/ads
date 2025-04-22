#include <iostream>
#include <fstream>
using namespace std;

const int V = 4; // Number of locations

int graph[V][V];


void loadGraphFromFile(const char* filename) {
    ifstream fin(filename);
    if (!fin) {
        cout << "Error opening file!\n";
        return;
    }

    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            fin >> graph[i][j];
        }
    }

    fin.close();
}


int minDistance(int dist[], bool visited[]) {
    int min = 9999, index = -1;
    for (int i = 0; i < V; i++) {
        if (!visited[i] && dist[i] < min) {
            min = dist[i];
            index = i;
        }
    }
    return index;
}

void dijkstra(int start) {
    int dist[V];
    bool visited[V] = {false};

    for (int i = 0; i < V; i++)
        dist[i] = 9999;

    dist[start] = 0;

    for (int i = 0; i < V - 1; i++) {
        int u = minDistance(dist, visited);
        visited[u] = true;

        for (int v = 0; v < V; v++) {
            if (!visited[v] && graph[u][v] && dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
            }
        }
    }

    cout << "\nShortest paths from Supplier (0):\n";
    for (int i = 0; i < V; i++) {
        cout << "To location " << i << " distance = " << dist[i] << " km\n";
    }
}

int main() {
    loadGraphFromFile("supply.txt");
    dijkstra(0); 
    return 0;
