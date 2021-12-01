#include <stdlib.h>

#ifndef STRING_HELPERS_H
#define STRING_HELPERS_H

size_t str_size(char *value) {
    size_t size = 0;
    char *aux = value;
    while (*aux != '\0') {
        size++;
        aux++;
    }

    return size;
}

void str_remove_trailing_newline(char *str) {
    size_t last_index = str_size(str) - 1;
    if ((str_size(str) > 0) && (str[last_index] == '\n'))
        str[last_index] = '\0';
}

#endif
