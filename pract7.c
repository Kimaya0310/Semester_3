#include <stdio.h>
#include <stdlib.h>
#include <float.h>

int main() {
    int n;
    printf("Enter number of book IDs: ");
    scanf("%d", &n);

    int keys[n + 1];
    double p[n + 1], q[n + 1];
    double e[n + 2][n + 1], w[n + 2][n + 1];
    int root[n + 1][n + 1];

    printf("Enter %d sorted book IDs:\n", n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &keys[i]);

    printf("Enter %d probabilities of successful searches (p[i]):\n", n);
    for (int i = 1; i <= n; i++)
        scanf("%lf", &p[i]);

    printf("Enter %d probabilities of unsuccessful searches (q[i]):\n", n + 1);
    for (int i = 0; i <= n; i++)
        scanf("%lf", &q[i]);

    // Initialization
    for (int i = 1; i <= n + 1; i++) {
        e[i][i - 1] = q[i - 1];
        w[i][i - 1] = q[i - 1];
    }

    // OBST Dynamic Programming
    for (int l = 1; l <= n; l++) {  // l = length of chain
        for (int i = 1; i <= n - l + 1; i++) {
            int j = i + l - 1;
            e[i][j] = DBL_MAX;
            w[i][j] = w[i][j - 1] + p[j] + q[j];
            for (int r = i; r <= j; r++) {
                double t = e[i][r - 1] + e[r + 1][j] + w[i][j];
                if (t < e[i][j]) {
                    e[i][j] = t;
                    root[i][j] = r;
                }
            }
        }
    }

    printf("\nMinimum Expected Search Cost: %.4lf\n", e[1][n]);
    return 0;
}
