#include <stdio.h>
#include "strutils.h"

int main() {
    char s1[] = "Hello World!";
    char s2[] = "KHOI";
    int number;

    printf("Original: '%s'\n", s1);
    str_trim(s1);
    printf("Trimmed: '%s'\n", s1);

    str_reverse(s2);
    printf("Reversed: '%s'\n", s2);

    if (str_to_int("12345", &number) == 0)
        printf("Converted number: %d\n", number);
    else
        printf("Invalid number!\n");

    return 0;
}
