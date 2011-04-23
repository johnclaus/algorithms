/*
 * Find integer pairs in an integer array so that they sum up to a specific number N.
 */

#include <stdio.h>

/* You can make it faster by ensuring a sorted array + binary search */

void find_int_pair_sum(int *arr, int len, int N, int *pair) {
    int i, j;
    int first, second;
    int found = 0;

    for (i = 0; i < len-1; ++i) {
        first = arr[i];
        for (j = i+1; j < len; ++j) {
            second = arr[j];
            if ((first+second) == N) {
                found = 1;
                break;
            }
        }

        if (found) {
            break;
        }
    }

    if (found) {
        pair[0] = first;
        pair[1] = second;
    } else {
        pair[0] = pair[1] = -1;
    }
}

int main(int argc, char **argv) {
    int arr[8] = { 1, 2, 3, 4, 5, 10, 20, 50 };
    int N = 70;
    int out[2];

    find_int_pair_sum(arr, 8, N, out);

    printf("%d, %d\n", out[0], out[1]);

    return 0;
}
