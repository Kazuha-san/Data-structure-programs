#include <iostream>
using namespace std;
#define MAX 20

int main() {
    int n;
    int adj[MAX][MAX];
    int visited[MAX];
    int q[MAX];
    int front = -1, rear = -1;

    cout << "Enter number of nodes: ";
    cin >> n;

    cout << "Enter adjacency matrix:\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> adj[i][j];
        }
    }

    cout << "Enter starting node: ";
    char s;
    cin >> s;

    int start = s - 'A';

    for (int i = 0; i < n; i++)
        visited[i] = 0;

    visited[start] = 1;
    front = 0;
    rear = 0;
    q[rear] = start;

    cout << "BFS Traversal: ";
    while (front <= rear) {
        int node = q[front++];
        cout << char(node + 'A') << " ";

        for (int j = 0; j < n; j++) {
            if (adj[node][j] == 1 && visited[j] == 0) {
                visited[j] = 1;
                q[++rear] = j;
            }
        }
    }

    return 0;
}
