#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "strutils.h"

void str_reverse(char *str) {
    int n = strlen(str);
    for (int i = 0; i < n / 2; i++) {
        char tmp = str[i];
        str[i] = str[n - i - 1];
        str[n - i - 1] = tmp;
    }
}

void str_trim(char *str) {
    char *start = str;
    while (isspace((unsigned char)*start)) start++;

    char *end = str + strlen(str) - 1;
    while (end > start && isspace((unsigned char)*end)) end--;

    *(end + 1) = '\0';
    memmove(str, start, end - start + 2);
}

int str_to_int(const char *str, int *out) {
    char *end;
    long val = strtol(str, &end, 10);
    if (*end != '\0') return -1;
    *out = (int)val;
    return 0;
}
