#include <stdio.h>
#define INF 9999
#define N 8   // number of nodes

// Function to compute shortest path in multistage graph
void shortestPath(int cost[N][N], int stages, int n) {
    int dist[N], path[N], i, j;

    // Initialize distances with INF
    for (i = 0; i < n; i++) {
        dist[i] = INF;
        path[i] = -1;
    }

    dist[n-1] = 0; //distance cost = 0

    //Compute Shortest path (backward)
    for (i = n-2; i >= 0; i--) {
        for (j = i+1; j < n; j++) {
            if (cost[i][j] != INF && dist[j] + cost[i][j] < dist[i]) {
                dist[i] = dist[j] + cost[i][j];
                path[i] = j;
            }
        }
    }

    // Print results
    printf("Minimum cost from Zero Mile (node 0) to node %d = %d\n", n-1, dist[0]);
    printf("Path: 0 ");
    i = 0;
    while (path[i] != -1) {
        printf("-> %d ", path[i]);
        i = path[i];
    }
    printf("\n");
}

int main() {
    // Example graph
    int cost[N][N] = {
        {INF, 2,  4,  INF, INF, INF, INF, INF},
        {INF, INF, INF, 7,  INF, INF, INF, INF},
        {INF, INF, INF, 1,  3,  INF, INF, INF},
        {INF, INF, INF, INF, INF, 2,  INF, INF},
        {INF, INF, INF, INF, INF, 5,  6,  INF},
        {INF, INF, INF, INF, INF, INF, INF, 4},
        {INF, INF, INF, INF, INF, INF, INF, 2},
        {INF, INF, INF, INF, INF, INF, INF, INF}
    };

    int stages = 4; // example stages
    shortestPath(cost, stages, N);

    return 0;
}
