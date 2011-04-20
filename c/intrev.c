/*
 * intreverse.c
 * - reverse the digits in an integer: 123 -> 321
 */

#include <stdio.h>

int intreverse(int n) {
    int r = 0;
    while (n) {
        r += n % 10;
        n /= 10;
        if (n)
            r *= 10;
    }
    return r;
}

int main(int argc, char **argv) {
    int n, r;
    n = 123456;

    r = intreverse(n);
    printf("%d\n", r);
    return 0;
}
