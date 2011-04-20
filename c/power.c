#include <stdio.h>

/*
 * Compute a^n for positive integer exponents. Exploit the relationship
 * between a solution to an instance of size n and a solution to an instance
 * of size n-1 (a^n = a^n-1 * a)
 *
 * Recursive definition of the algorithm:
 *
 * f(n) = a^n = { f(n-1) * a    if n > 1,
 *                a             if n = 1 }
 */

int power(int a, int n) {
    /* recursive */
    if (n == 1)
        return a;
    return a*power(a, n-1);
}

/* bottom-up solution just multiplies a by itself n-1 times */
int power2(int a, int n) {
    /* iterative */
    int i, res = a;
    for (i = 1; i < n; ++i) {
        res *= a;
    }
    return res;
}

void usage(const char *prog) {
    printf("Usage: %s a n\n" \
           "  Where `a` is an integer and" \
           " `n` is a positive integer exponent.\n", prog);
}

int main(int argc, char **argv) {
    int a, n;

    if (argc < 3) {
        usage(argv[0]);
        return 0;
    }

    a = atoi(argv[1]);
    n = atoi(argv[2]);

    if (n == 0) {
        usage(argv[0]);
        return 0;
    }

    printf("%d\n", power2(a, n));
    return 0;
}
