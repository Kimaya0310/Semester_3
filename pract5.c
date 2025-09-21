#include <stdio.h>
#include <string.h>

// Value + Direction
typedef struct {
    int val;
    char dir; // d,u,s directions
} Cell;

int main() {
    char X[] = "AGCCCTAAGGGCTACCTAGCTT";
    char Y[] = "GACAGCCTACAAGCGTTAGCTTG";

    int m = strlen(X);
    int n = strlen(Y);

    Cell c[m+1][n+1];  // DP matrix

    // Initialize first row/column
    for (int i = 0; i <= m; i++) {
        c[i][0].val = 0;
        c[i][0].dir = 'h';
    }
    for (int j = 0; j <= n; j++) {
        c[0][j].val = 0;
        c[0][j].dir = 'h';
    }

    // Fill the matrix
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (X[i-1] == Y[j-1]) {
                c[i][j].val = c[i-1][j-1].val + 1;
                c[i][j].dir = 'd'; // diagonal
            } else if (c[i-1][j].val >= c[i][j-1].val) {
                c[i][j].val = c[i-1][j].val;
                c[i][j].dir = 'u'; // up
            } else {
                c[i][j].val = c[i][j-1].val;
                c[i][j].dir = 's'; // side
            }
        }
    }

    // Print the matrix
    printf("\nCost Matrix (val,dir):\n");
    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= n; j++) {
            printf("%2d%c ", c[i][j].val, c[i][j].dir);
        }
        printf("\n");
    }

    // Final cost
    printf("\nFinal LCS length = %d\n", c[m][n].val);

    // Backtrack to get LCS string
    int i = m, j = n, idx = c[m][n].val;
    char lcs[idx+1];
    lcs[idx] = '\0';

    while (i > 0 && j > 0) {
        if (c[i][j].dir == 'd') {
            lcs[--idx] = X[i-1];
            i--; j--;
        } else if (c[i][j].dir == 'u') {
            i--;
        } else {
            j--;
        }
    }

    printf("LCS = %s\n", lcs);

    return 0;
}