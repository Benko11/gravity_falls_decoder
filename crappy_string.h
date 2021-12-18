#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef CRAPPY_STRING_H
#define CRAPPY_STRING_H
typedef struct {
    char *buffer;
    size_t capacity;
} crappy_string;

void str_init(crappy_string *str) {
    str->buffer = (char *) malloc(2 * sizeof(char));
    str->capacity = 1; // excludes '\0'
}

void str_assign(crappy_string *str, char *value) {
    size_t length = strlen(value);

    while (length > str->capacity) {
        str->capacity *= 2;
    }

    str->buffer = (char *) realloc(str->buffer, str->capacity + 1);
    char *buffer = str->buffer;
    char *aux_ptr = value;
    while (*aux_ptr != '\0') {
        *(buffer++) = *(aux_ptr++);
    }
    *(buffer++) = '\0';
}

char *str_get(crappy_string *str) {
    return str->buffer;
}

void str_destroy(crappy_string *str) {
    free(str->buffer);
}
#endif