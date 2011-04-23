/* divide_and_conquer.c
 *
 * Write a divide-and-conquer algorithm for finding the position of the
 * largest element in an array of size N.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 1024

int find_largest(int A[], int i, int j) {
    /*
     * Finds the largest element in an unsorted array A[] and
     * returns the index of that element.
     *
     * find_largest(...) uses a divide-and-conquer approach to this problem.
     * - The basic idea is to break the problem down until you're returning
     *   a single element's index. Once you do that, the algorithm can backtrack
     *   and compare the best elements of each branch (left and right).
     */

    int m;
    int left, right;

    if (i < j) {
        m = (i+j) / 2;
        left = find_largest(A, i, m);
        right = find_largest(A, m+1, j);
        if (A[left] > A[right])
            return left;
        return right;
    }
    return i;
}

int main(int argc, char **argv) {
    int i;
    int A[N];

    srand(time(NULL));
    for (i = 0; i < N; ++i) {
        A[i] = rand() % N+1;
    }

    i = find_largest(A, 0, N);
    printf("A[%d] = %d\n", i, A[i]);

    return 0;
}
