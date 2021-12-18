#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef CRAPPY_STRING_H
#define CRAPPY_STRING_H
typedef struct {
    char *buffer;
    size_t capacity;
} crappy_string;

void str_init(crappy_string *str);
void str_assign(crappy_string *str, char *value);
void str_add(crappy_string *str, char *value);
char *str_get(crappy_string *str);
void str_destroy(crappy_string *str);

void str_init(crappy_string *str) {
    str->buffer = (char *) malloc(2 * sizeof(char));
    str->capacity = 1; // excludes '\0'
}

void str_assign(crappy_string *str, char *value) {
    size_t length = strlen(value);

    if (str->capacity > length) {
        str->capacity = 1;
        str->buffer = (char *) realloc(str->buffer, 2 * sizeof(char));
    }

    while (length > str->capacity) {
        str->capacity *= 2;
    }

    str->buffer = (char *) realloc(str->buffer, str->capacity + 1);
    memset(str->buffer, 0x00, str->capacity + 1);

    char *buffer = str->buffer;
    char *aux_ptr = value;
    while (*aux_ptr != '\0') {
        *(buffer++) = *(aux_ptr++);
    }
    *(buffer++) = '\0';
}

void str_add(crappy_string *str, char *value) {
    if (str->buffer[0] == '\0') {
        str_assign(str, value);
        return;
    }

    size_t length = strlen(value) + strlen(str_get(str));

    while (length > str->capacity) {
        str->capacity *= 2;
    }

    str->buffer = (char *) realloc(str->buffer, str->capacity + 1);
    char *aux_ptr = str->buffer;
    while (*aux_ptr != '\0') {
        aux_ptr++;
    }

    while (*value != '\0') {
        *(aux_ptr++) = *(value++);
    }

    *(aux_ptr++) = '\0';
}

char *str_get(crappy_string *str) {
    return str->buffer;
}

void str_destroy(crappy_string *str) {
    memset(str->buffer, 0x00, str->capacity + 1);
    free(str->buffer);
}
#endif