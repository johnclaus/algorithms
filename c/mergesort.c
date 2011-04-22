/* mergesort.c
 *
 * This implementation doesn't rely on sentinel values to determine when
 * the algorithm is finished.
 *
 * The real magic happens when merging two sorted arrays:
 *
 * 1. Two pointers (in this case, integer indices into the two arrays) are
 *    initialized to the start of each array:
 *      int i = 0, j = 0;
 *      int k = 0; // the index into the final array
 *
 * 2. The two array elements indexed by i and j are compared, with the
 *    smaller element being added to the final array at index k:
 *      if (B[i] <= C[j])
 *          A[k] = B[i];
 *      else
 *          A[k] = C[j];
 *
 * 3. Increment i or j depending on which element was copied into A
 *    and increment k as well. Repeat step 2 until one of the arrays
 *    has been exhausted.
 *
 * 4. Copy whichever array wasn't exhausted into A.
 *      // p is num elements in B, q is num elements in C
 *      if (i == p) {
 *          // B was exhausted, copy rest of C into A
 *          copy_subsequence(C[j, .., q-1], A[k, .., p+q-1])
 *      } else {
 *          // C was exhausted, copy rest of B into A
 *          copy_subsequence(B[i, .., p-1], A[k, .., p+q-1])
 *      }
 */

#include <stdio.h>
#include <stdlib.h>

static void copy_subsequence(int a[], int b[], int i, int p, int j, int q) {
    while (i < p && j < q) {
        b[j++] = a[i++];
    }
}

static void merge_arrays(int A[], int B[], int C[], int p, int q) {
    int i, j, k;
    i = j = k = 0;

    while (i < p && j < q) {
        if (B[i] <= C[j])
            A[k++] = B[i++];
        else
            A[k++] = C[j++];
    }

    if (i == p)
        copy_subsequence(C, A, j, q, k, p+q);
    else
        copy_subsequence(B, A, i, p, k, p+q);
}

void MergeSort(int A[], int n) {
    /* Note the use of n-half when operating on C. This is important for
     * odd numbered arrays for getting the rest of the elements. */
    int half;
    int *B, *C;

    if (n > 1) {
        half = n / 2;

        /* TODO: explore solutions to this algorithm without using malloc */
        B = (int *)malloc(sizeof(int)*half);
        C = (int *)malloc(sizeof(int)*(n-half));

        copy_subsequence(A, B, 0, half, 0, half);
        copy_subsequence(A, C, half, n, 0, n-half);

        MergeSort(B, half);
        MergeSort(C, n-half);
        merge_arrays(A, B, C, half, n-half);

        free(B);
        free(C);
    }
}

int main(int argc, char **argv) {
    int i;
    int A[16] = {5, 4, 3, 1, 9, 8, 2, 6, 10, 40, 32, 41, 13, 20, 7, 23};

    MergeSort(A, 16);

    for (i = 0; i < 16; ++i) {
        printf("%d ", A[i]);
    }
    printf("\n");

    return 0;
}
