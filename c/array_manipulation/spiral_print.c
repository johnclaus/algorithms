/* spiral_print.c -- "spiral print" a 2D array
 *
 *  [ ]->[ ]->[ ]
 *             |
 *             v
 *  [ ]->[ ]  [ ]
 *   ^         |
 *   |         v
 *  [ ]<-[ ]<-[ ]
 */

#include <stdio.h>

int main(int argc, char **argv) {
    int i, j, k;

    int A[4][4] = {
        { 1,  2,  3,  4},
        {12, 13, 14,  5},
        {11, 16, 15,  6},
        {10,  9,  8,  7},
    };

    for (i = 3, j = 0; i >= 0; --i, ++j) {
        /* moves left to right */
        for (k = j; k < i; ++k)
            printf("%d\n", A[j][k]);

        /* moves top to bottom */
        for (k = j; k < i; ++k)
            printf("%d\n", A[k][i]);

        /* moves right to left */
        for (k = i; k > j; --k)
            printf("%d\n", A[i][k]);

        /* moves bottom to top */
        for (k = i; k > j; --k)
            printf("%d\n", A[k][j]);

        /* needed for odd matrices (3x3, etc) to print the last element,
         * which is the middle of the array. */
        if (i == k && i == j)
            printf("%d\n", A[k][k]);
    }

    return 0;
}
