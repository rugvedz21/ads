#include <iostream>
#include <fstream>
#include <climits>
using namespace std;

#define MAX 100

int graph[MAX][MAX], parent[MAX];
int numVertices;

void loadGraph(const char* filename) {
    ifstream fin(filename);
    if (!fin) {
        cout << "File can't be opened.\n";
        return;
    }
    fin >> numVertices;
    for (int i = 0; i < numVertices; i++)
        for (int j = 0; j < numVertices; j++)
            fin >> graph[i][j];
    fin.close();
}

// ---------- PRIM'S ALGORITHM ----------
void primsMST() {
    int key[MAX], visited[MAX];

    for (int i = 0; i < numVertices; i++) {
        key[i] = INT_MAX;
        visited[i] = 0;
    }

    key[0] = 0; // Start from 0
    parent[0] = -1;

    for (int count = 0; count < numVertices - 1; count++) {
        int min = INT_MAX, u;

        // Find min key vertex not yet visited
        for (int v = 0; v < numVertices; v++)
            if (!visited[v] && key[v] < min)
                min = key[v], u = v;

        visited[u] = 1;

        // Update keys of adjacent vertices
        for (int v = 0; v < numVertices; v++)
            if (graph[u][v] && !visited[v] && graph[u][v] < key[v])
                parent[v] = u, key[v] = graph[u][v];
    }

    cout << "\nPrim's MST:\n";
    int total = 0;
    for (int i = 1; i < numVertices; i++) {
        cout << parent[i] << " - " << i << " = " << graph[i][parent[i]] << endl;
        total += graph[i][parent[i]];
    }
    cout << "Total weight: " << total << endl;
}

// ---------- KRUSKAL'S ALGORITHM ----------
struct Edge {
    int src, dest, weight;
};

Edge edges[MAX * MAX];
int edgeCount = 0;

void collectEdges() {
    edgeCount = 0;
    for (int i = 0; i < numVertices; i++) {
        for (int j = i + 1; j < numVertices; j++) {
            if (graph[i][j]) {
                edges[edgeCount].src = i;
                edges[edgeCount].dest = j;
                edges[edgeCount].weight = graph[i][j];
                edgeCount++;
            }
        }
    }
}

void sortEdges() {
    for (int i = 0; i < edgeCount - 1; i++) {
        for (int j = i + 1; j < edgeCount; j++) {
            if (edges[i].weight > edges[j].weight) {
                Edge temp = edges[i];
                edges[i] = edges[j];
                edges[j] = temp;
            }
        }
    }
}

int findParent(int v, int parentSet[]) {
    if (v == parentSet[v])
        return v;
    return parentSet[v] = findParent(parentSet[v], parentSet);
}

void unionSet(int u, int v, int parentSet[]) {
    int pu = findParent(u, parentSet);
    int pv = findParent(v, parentSet);
    parentSet[pu] = pv;
}

void kruskalMST() {
    collectEdges();
    sortEdges();

    int parentSet[MAX];
    for (int i = 0; i < numVertices; i++)
        parentSet[i] = i;

    cout << "\nKruskal's MST:\n";
    int total = 0, edgesAdded = 0;

    for (int i = 0; i < edgeCount && edgesAdded < numVertices - 1; i++) {
        int u = edges[i].src;
        int v = edges[i].dest;
        int pu = findParent(u, parentSet);
        int pv = findParent(v, parentSet);

        if (pu != pv) {
            cout << u << " - " << v << " = " << edges[i].weight << endl;
            total += edges[i].weight;
            unionSet(pu, pv, parentSet);
            edgesAdded++;
        }
    }

    cout << "Total weight: " << total << endl;
}

// ---------- MAIN ----------
int main() {
    loadGraph("matrix.txt");

    primsMST();
    kruskalMST();

    return 0;
}
