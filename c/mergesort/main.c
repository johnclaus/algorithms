#include <stdio.h>
#include <stdlib.h>

/*
 * TODO: Rewrite merge so it doesn't use sentinels. Instead, it should stop once either
 * array L or R has had all its elements copied back into A and then copying the remainder
 * of the other array back into A.
 */

void merge(int *arr, int p, int q, int r) {
    int n1, n2, i, j, k;
    int *L, *R;

    n1 = q - p;
    n2 = r - q;

    /*
     * TODO: How can you design this algorithm so it either doesn't use extra space
     * or it doesn't use malloc each time merge() is called? One way would be to
     * use malloc to create a second array the same size as the first and pass it into
     * merge().
     */

    L = (int *)malloc((n1) * sizeof(int));
    R = (int *)malloc((n2) * sizeof(int));

    for (i = 0; i < n1; ++i) {
        L[i] = arr[p+i];
    }

    for (j = 0; j < n2; ++j) {
        R[j] = arr[q+j];
    }

    /*
     * Should compute sentinel values from largest known element in arr
     */
    L[n1] = 999;
    R[n2] = 999;

    i = j = 0;

    for (k = p; k < r; ++k) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            ++i;
        } else {
            arr[k] = R[j];
            ++j;
        }
    }

    free(L);
    free(R);
}

void mergesort(int *arr, int p, int r) {
    int q;

    if (p < r) {
        q = (p+r) / 2;
        mergesort(arr, p, q);
        mergesort(arr, q+1, r);
        merge(arr, p, q, r);
    }
}

int main(int argc, char **argv) {
    int arr[] = {5, 2, 4, 7, 1, 3, 2, 6};
    mergesort(arr, 0, 8);

    int i;
    for (i = 0; i < 8; ++i) {
        printf("%d ", arr[i]);
    }

    printf("\n");

    return 0;
}
