/*
 * write an algorithm to determine if N is a power of 2.
 */

#include <stdio.h>
#include <math.h>

/* 2^3 = 8
 * log2(8) = 3
 * - exploit the relationship between log2(N) and 2^x = N
 * - you can compute log2(N) with log(N) / log(2)
 */

int power_of_two(int n) {
    int lg2 = log(n) / log(2);
    if (pow(2, lg2) == n)
        return 1;
    return 0;
}

/* the same idea above can be applied to this problem:
 * - given two numbers, X and Y, determine if X is an integer power of Y.
 */

int power_of_y(int x, int y) {
    int lg = log(x) / log(y);
    if (pow(y, lg) == x)
        return 1;
    return 0;
}

int main(int argc, char **argv) {
    printf("%d\n", power_of_y(16, 4));
    return 0;
}
