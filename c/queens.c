#include <stdio.h>
#include <math.h>

/* pseudo-code for generic backtracking:
 *
 * backtrack(X[0..i])
 *   if X[0..i] is a solution
 *     write X[0..i]
 *   else
 *     for x in Si+1 consistent with X[0..i] and constraints
 *       X[i+1] = x
 *       backtrack(X[0..i+1])
 */

#define N 4
static unsigned int count = 0;

void print_solution(int tup[]) {
    int i;

    printf("(");
    for (i = 0; i < N; ++i) {
        printf("%d", tup[i]);
        if (i < N-1)
            printf(", ");
    }
    printf(")\n");
}

void queens(int tup[], int row) {
    int i, j, d, collision;

    if (row >= N) {
        ++count;
        print_solution(tup);
        return;
    }

    for (i = 0; i < N; ++i) {
        tup[row] = i;
        collision = 0;

        for (j = 0; j < row; ++j) {
            d = tup[j] - tup[row];
            /* check if a queen is in this column or
             * in one of the diagonals */
            if (d == 0 || d == j-row || d == row-j)
                collision = 1;
        }

        if (!collision)
            queens(tup, row+1);
    }
}

int main(int argc, char **argv) {
    int i;
    int tup[N];

    /* first queen only needs to utilize 
     * the first half of the board */
    for (i = 0; i < N/2; ++i) {
        tup[0] = i;
        queens(tup, 1);
    }
    printf("Total: %d\n", count);

    return 0;
}
