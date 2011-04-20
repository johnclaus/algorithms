/* strrev.c
 * - reverse a string: "abc" -> "cba"
 */

#include <stdio.h>
#include <string.h>

void reverse(char *s, int start, int end) {
    int i, j;
    char tmp;
    for (i = start, j = end; i < j; ++i, --j) {
        tmp = s[i];
        s[i] = s[j];
        s[j] = tmp;
    }
}

void wordrev(char *s) {
    int i, j, tmp;
    for (i = 0; i < strlen(s); ++i) {
        j = i;
        while (s[i] != '\0' && s[i] != ' ')
            ++i;
        reverse(s, j, i-1);
    }
}

int main(int argc, char **argv) {
    int i;
    char s[] = "hello world foo bar baz";
    printf("normal: %s\n", s);

    reverse(s, 0, strlen(s)-1);
    printf("reversed string: %s\n", s);

    wordrev(s);
    printf("reversed words: %s\n", s);

    return 0;
}
