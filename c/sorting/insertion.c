#include <stdio.h>

void insertion_sort(int *arr, int len) {
    /* sorts arr in place using insertion sort */

    int i, j, key;

    for (i = 1; i < len; ++i) {
        key = arr[i];
        j = i-1;

        while (j >= 0 && arr[j] > key) {
            arr[j+1] = arr[j];
            --j;
        }

        arr[j+1] = key;
    }
}

int main(int argc, char **argv) {
    int arr[] = {4, 5, 20, 6, 2, 3, 12, 1};
    insertion_sort(arr, 8);

    int i;
    for (i = 0; i < 8; ++i) {
        printf("%d ", arr[i]);
    }

    printf("\n");

    return 0;
}
