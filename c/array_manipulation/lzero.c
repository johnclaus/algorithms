/*
 * Partition an array in such a way that zeroes are moved to the left side of the array
 * and all other numbers to the right side of the array. In-place only.
 */

#include <stdio.h>

int main(int argc, char **argv) {
    int i, cur, tmp;
    int a[10] = {1, 2, 0, 3, 0, 5, 6, 0, 10, 0};

    cur = 0;
    for (i = 0; i < 10; ++i) {
        if (a[i] == 0) {
            tmp = a[cur];
            a[cur] = a[i];
            a[i] = tmp;
            ++cur;
        }
    }

    for (i = 0; i < 10; ++i) {
        printf("%d", a[i]);
        if (i < 9)
            printf(", ");
    }

    printf("\n");

    return 0;
}
