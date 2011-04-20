/*
 * find the weighted midpoint of an array by the sum of a subset.
 */

#include <stdio.h>

#define N 7

int main(int argc, char **argv) {
    /* assumes array is sorted in increasing order */
    int i, j, res, delta;
    int sumi, sumj;
    int a[N] = {0, 1, 2, 3, 4, 5, 6};

    sumi = delta = 0;
    res = -1;

    /* compute sum of entire array */
    for (i = 0; i < N; ++i)
        delta += a[i];

    for (i = 0; i < N; ++i) {
        sumi += a[i];
        sumj = 0;
        for (j = N-1; j > i+1; --j) {
            sumj += a[j];
            if (sumi+a[i+1] > sumj) {
                if (sumj - sumi+a[i+1] < delta) {
                    delta = sumj - sumi+a[i+1];
                    res = i;
                }
            }
        }
    }

    printf("%d\n", res);

    return 0;
}
