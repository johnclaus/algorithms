#include <stdio.h>

int binary_search(int A[], int p, int r, int v) {
    int m = (p+r) / 2;

    if (p == r) {
        return -1;
    }

    if (A[m] == v)
        return m;

    if (v > A[m]) {
        /* search right */
        return binary_search(A, m+1, r, v);
    }
    return binary_search(A, p, m-1, v);
}

int main(int argc, char **argv) {
    int A[8] = {1, 2, 3, 4, 5, 6, 7, 8};
    int res = binary_search(A, 0, 8, 0);

    if (res >= 0) {
        printf("A[%d] = %d\n", res, A[res]);
    } else {
        printf("not found\n");
    }
    return 0;
}
