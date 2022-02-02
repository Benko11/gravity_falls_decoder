#include <string.h>
#include <ctype.h>

#ifndef STRTOUPPERCASE_H
#define STRTOUPPERCASE_H
char *strtouppercase(char *word) {
    char *ptr = word;
    char *copy = (char *)malloc((strlen(word) + 1) * sizeof(char));
    char *aux = copy;
    while (*ptr != '\0') {
        *aux++ = toupper(*ptr);
        ptr++;
    }

    return copy;
}
#endif