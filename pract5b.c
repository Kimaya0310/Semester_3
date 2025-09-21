#include <stdio.h>
#include <string.h>

//Value +Direction
typedef struct {
    int val;
    char dir; //d, u, s
} Cell;

int main() {
    char S[] = "AABCBDC";
    int n = strlen(S);

    Cell c[n+1][n+1];  // DP matrix (same dimensions, so n)

    // Initialize first row
    for (int i = 0; i <= n; i++) {
        c[i][0].val = 0; 
        c[i][0].dir = 'h';
    }
    for (int j = 0; j <= n; j++) {
        c[0][j].val = 0; 
        c[0][j].dir = 'h';
    }

    // Fill the matrix
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (S[i-1] == S[j-1] && i != j) {
                c[i][j].val = c[i-1][j-1].val + 1;
                c[i][j].dir = 'd'; // diagonal
            } else if (c[i-1][j].val >= c[i][j-1].val) {
                c[i][j].val = c[i-1][j].val;
                c[i][j].dir = 'u'; // up
            } else {
                c[i][j].val = c[i][j-1].val;
                c[i][j].dir = 's'; //side
            }
        }
    }

    // Print cost matrix
    printf("\nCost Matrix (val,dir):\n");
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= n; j++) {
            printf("%2d%c ", c[i][j].val, c[i][j].dir);
        }
        printf("\n");
    }

    // Final LRS length
    printf("\nFinal LRS length = %d\n", c[n][n].val);

    // Backtrack to get LRS string
    int i = n, j = n, idx = c[n][n].val;
    char lrs[idx+1];
    lrs[idx] = '\0';

    while (i > 0 && j > 0) {
        if (c[i][j].dir == 'd') {
            lrs[--idx] = S[i-1];
            i--; j--;
        } else if (c[i][j].dir == 'u') {
            i--;
        } else {
            j--;
        }
    }

    printf("LRS = %s\n", lrs);

    return 0;
}