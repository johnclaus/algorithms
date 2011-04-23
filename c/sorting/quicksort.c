#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 8

static void swap(int A[], int i, int j) {
    int tmp;
    tmp = A[i];
    A[i] = A[j];
    A[j] = tmp;
}

void QuickSort(int A[], int p, int r) {
    int pivot, i, j;
    if (r > p+1) {
        pivot = A[p];
        i = p+1;
        j = r;
        while (i < j) {
            if (A[i] <= pivot)
                ++i;
            else
                swap(A, i, --j);
        }
        swap(A, --i, p);
        QuickSort(A, p, i);
        QuickSort(A, j, r);
    }
}

int main(int argc, char **argv) {
    int i;
    int A[N] = {8, 3, 5, 1, 4, 2, 7, 6};

    QuickSort(A, 0, N);

    for (i = 0; i < N; ++i) {
        printf("%d ", A[i]);
    }
    printf("\n");

    return 0;
}
