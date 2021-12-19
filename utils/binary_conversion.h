#include <stdlib.h>
#include <string.h>

#ifndef BINARY_CONVERSION_H
#define BINARY_CONVERSION_H
char *binary_conversion(unsigned char character) {
    char *result = (char *) malloc(9 * sizeof(char));
    memset(result, '0', 8);

    int current = (int) character;

    for (int i = 7; i >= 0; i--) {
        if (current % 2 == 1)
            result[i] = '1';
        current /= 2;
    }

    return result;
}
#endif