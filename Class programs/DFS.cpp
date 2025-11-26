#include <iostream>
using namespace std;
#define MAX 20

int main() {
    int n;
    int adj[MAX][MAX];
    int visited[MAX];
    int st[MAX];
    int top = -1;

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

    cout << "DFS Traversal: ";
    st[++top] = start;

    while (top != -1) {
        int node = st[top--];

        if (visited[node] == 0) {
            visited[node] = 1;
            cout << char(node + 'A') << " ";
        }

        for (int j = n - 1; j >= 0; j--) {
            if (adj[node][j] == 1 && visited[j] == 0) {
                st[++top] = j;
            }
        }
    }

    return 0;
}
