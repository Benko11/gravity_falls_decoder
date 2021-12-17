#include <stdlib.h>
#include "my_string_helpers.h"

#ifndef CYCLIC_ARRAY_H
#define CYCLIC_ARRAY_H

typedef struct cyclic_array_t {
    char *buffer;
} cyclic_array;

void c_arr_init(cyclic_array *c_arr, char *items) {
    size_t size = str_size(items);
    c_arr->buffer = (char *) malloc(size * sizeof(char));
    c_arr->buffer = items;
}

size_t c_arr_index(cyclic_array *c_arr, char letter) {
    size_t i = 1;
    while (i <= str_size(c_arr->buffer)) {
        if (c_arr->buffer[i - 1] == letter)
            return i;
        i++;
    }

    return 0;
}

char c_arr_char(cyclic_array *c_arr, size_t index) {
    if (index <= 0 || index > str_size(c_arr->buffer)) {
        fprintf(stderr, "Invalid index\n");
        exit(EXIT_FAILURE);
    }

    return c_arr->buffer[index - 1];
}

char c_arr_move(cyclic_array *c_arr, char start, int steps) {
    size_t completion = abs(steps);
    int current = 1;

    size_t current_char = c_arr_index(c_arr, start);
    
    for (; current <= completion; current++) {
        if (steps > 0)
            current_char++;
        else
            current_char--;

        if (current_char > str_size(c_arr->buffer)) {
            current_char = 1;
        } else if (current_char <= 0) {
            current_char = str_size(c_arr->buffer);
        }
    }

    return c_arr_char(c_arr, current_char);
}

void c_arr_destroy(cyclic_array *c_arr) {
    free(c_arr);
}
#endif