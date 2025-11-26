#include <iostream>
using namespace std;

struct Edge {
    int start, end, weight;
};

int main() {
    int n, e;
    cout << "Enter number of vertices: ";
    cin >> n;

    cout << "Enter number of edges: ";
    cin >> e;

    Edge edges[e];
    cout << "Enter edges in sorted order (start end weight):\n";
    for (int i = 0; i < e; i++) {
        cin >> edges[i].start >> edges[i].end >> edges[i].weight;
    }

    int sets[n];
    for (int i = 0; i < n; i++) {
        sets[i] = i;
    }

    cout << "\nEdges:\n";
    int totalCost = 0;

    for (int i = 0; i < e; i++) {
        int u = edges[i].start;
        int v = edges[i].end;

        int setU = sets[u];
        int setV = sets[v];

        if (setU != setV) {
            cout << u << " " << v << " " << edges[i].weight << endl;
            totalCost += edges[i].weight;

            for (int j = 0; j < n; j++) {
                if (sets[j] == setV) {
                    sets[j] = setU;
                }
            }
        }
    }

    cout << "Total cost: " << totalCost << endl;
    return 0;
}
