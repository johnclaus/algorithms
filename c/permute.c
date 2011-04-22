/* heap.c
 * - implementation of hea63 permutation algorithm.
 */

#include <stdio.h>

#define N 3
#define PERMS 6
static char A[N];
/* 3! == 6 */
static char perms[PERMS][N];
static int pcount = 0;

void swap(char *a, int i, int j) {
    char tmp;
    tmp = a[i];
    a[i] = a[j];
    a[j] = tmp;
}

void print_permutation(void) {
    int i;
    for (i = 0; i < N; ++i) {
        printf("%c", A[i]);
    }
    printf("\n");
}

void HeapPermute(int n) {
    int i;

    if (n == 0) {
        for (i = 0; i < N; ++i) {
            perms[pcount][i] = A[i];
        }
        ++pcount;
    } else {
        for (i = 0; i < n; ++i) {
            HeapPermute(n-1);
            if (n % 2 == 0)
                swap(A, 0, n-1);
            else
                swap(A, i, n-1);
        }
    }
}

int main(int argc, char **argv) {
    int i, j;

    for (i = 0; i < N; ++i) {
        A[i] = 'a' + i;
    }

    HeapPermute(N);

    for (i = 0; i < PERMS; ++i) {
        for (j = 0; j < N; ++j) {
            printf("%c", perms[i][j]);
        }
        printf("\n");
    }
    return 0;
}
