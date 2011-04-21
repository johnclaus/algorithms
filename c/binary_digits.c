#include <stdio.h>

int binary_digits(int n) {
    int count = 1;
    while (n > 1) {
        ++count;
        n /= 2;
    }
    return count;
}

int main(int argc, char **argv) {
    printf("%d\n", binary_digits(10));
    return 0;
}
