#include <iostream>
using namespace std;

struct block {
    float weight;
};

class Queue {
    int front;
    int rear;
    int size;
    int* arr;

public:
    Queue(int size = 5) {
        this->size = size;
        arr = new int[size];
        front = -1;
        rear = -1;
    }

    ~Queue() {
        delete[] arr;
    }

    void enqueue(int data) {
        if (rear == size - 1) {
            cout << "Queue is full" << endl;
            return;
        }
        if (front == -1) {
            front = 0;
        }
        rear++;
        arr[rear] = data;
    }

    int dequeue() {
        if (front == -1 || front > rear) {
            cout << "Queue is empty" << endl;
            return -1;
        }
        return arr[front++];
    }

    bool isEmpty() {
        return front == -1 || front > rear;
    }
};

class Stack {
    int top;
    int size;
    int* arr;

public:
    Stack(int size = 5) {
        this->size = size;
        arr = new int[size];
        top = -1;
    }

    ~Stack() {
        delete[] arr;
    }

    void push(int data) {
        if (top == size - 1) {
            cout << "Stack is full" << endl;
            return;
        }
        arr[++top] = data;
    }

    int pop() {
        if (top == -1) {
            cout << "Stack is empty" << endl;
            return -1;
        }
        return arr[top--];
    }

    int peek(){
        return arr[top];

    }

    bool isEmpty() {
        return top == -1;
    }
};

class Graph {
    int n;
    block** arr;

public:
    Graph(int n) {
        this->n = n;

        arr = new block*[n];
        for (int i = 0; i < n; i++) {
            arr[i] = new block[n];
            for (int j = 0; j < n; j++) {
                arr[i][j].weight = 0;
            }
        }
    }

    void add_edge(int x, int y, float weight) {
        if (x >= 0 && x < n && y >= 0 && y < n) {
            arr[x][y].weight = weight;
            arr[y][x].weight = weight;
        } else {
            cout << "Invalid edge (" << x << ", " << y << ") Should be less than " << n << "!!!" << endl;
        }
    }

    int degree_of_node(int row) {
        int count = 0;

        for (int i = 0; i < n; i++) {
            if (arr[row][i].weight > 0) {
                count++;
            }
        }
        return count;
    }

    bool is_adj(int x, int y) {
        return arr[x][y].weight > 0;
    }

    void display() {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cout << arr[i][j].weight << " ";
            }
            cout << endl;
        }
    }

    void DFS(int start) {
        int* visited = new int[n] {0}; 
        Stack s(n); 
    
        visited[start] = 1;
        s.push(start); 

        cout << "DFS Traversal: ";
        while (!s.isEmpty()) {
            int node = s.pop(); 
            cout << char(65 + node) << " "; 
    
            
            for (int j = 0; j < n; j++) {
                if (is_adj(node, j) && !visited[j]) {
                    visited[j] = 1; 
                    s.push(j); 
                }
            }
        }
        cout << endl;
        delete[] visited; 
    }

    void BFS(int start) {
        int* visited = new int[n] {0}; 
        Queue q(n); 
    
        visited[start] = 1; 
        q.enqueue(start); 
    
        cout << "BFS Traversal: ";
        while (!q.isEmpty()) {
            int node = q.dequeue(); 
            cout << char(65 + node) << " "; 
    
            // Explore all adjacent nodes
            for (int j = 0; j < n; j++) {
                if (is_adj(node, j) && !visited[j]) {
                    visited[j] = 1; 
                    q.enqueue(j); 
                }
            }
        }
        cout << endl;
        delete[] visited; 
    }

    ~Graph() {
        for (int i = 0; i < n; i++) {
            delete[] arr[i];
        }
        delete[] arr;
    }
};

int main() {
    Graph g(9);
    g.add_edge(0, 1, 1);
    g.add_edge(0, 8, 1);
    g.add_edge(8, 2, 1);
    g.add_edge(8, 6, 1);
    g.add_edge(2, 3, 1);
    g.add_edge(2, 4, 1);
    //g.add_edge(4, 2, 1);
    g.add_edge(2, 5, 1);
    g.add_edge(4, 7, 1);
    g.add_edge(6, 5, 1);
    g.add_edge(6, 7, 1);
        
    cout << "Adjacency Matrix:" << endl;
    g.display();

    g.DFS(0);
    g.BFS(0);

    return 0;
}
