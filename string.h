#include <stdlib.h>
#include "string_helpers.h"

#ifndef STRING_H
#define STRING_H

typedef struct string_t {
    char *buffer;
    size_t capacity;
} string;

void str_init(string*, size_t);
void str_assign(string*, char*);
void str_add(string*, char*);
void str_add_c(string*, char);
char *str_print(string*);

void str_init(string *str, size_t capacity) {
    str->buffer = (char *) malloc(capacity * sizeof(char));
    str->capacity = capacity;
}

void str_assign(string *str, char *value) {
    size_t size = str_size(value);

    while (size > str->capacity) {
        str->capacity *= 2;
    }

    str->buffer = realloc(str->buffer, str->capacity);
    str->buffer = value;
}

void str_add(string *str, char *extra) {
    if (str->buffer == "") {
        str_assign(str, extra);
        return;
    }

    string backup;
    str_init(&backup, 1);
    str_assign(&backup, str->buffer);

    size_t size = str->capacity + str_size(extra);
    while (size > str->capacity) {
        str->capacity *= 2;
    }

    str->buffer = NULL;
    str->buffer = (char *) malloc(str->capacity * sizeof(char));

    char *aux_ptr = str->buffer;
    while (*backup.buffer != '\0') {
        *aux_ptr = *backup.buffer;
        backup.buffer++;
        aux_ptr++;
    }

    while (*extra != '\0') {
        *aux_ptr = *extra;
        extra++;
        aux_ptr++;
    }
}

void str_add_c(string *str, char extra) {
    string backup;
    str_init(&backup, 1);
    str_assign(&backup, str->buffer);

    size_t size = str->capacity + 1;
    while (size > str->capacity) {
        str->capacity *= 2;
    }

    str->buffer = NULL;
    str->buffer = realloc(str->buffer, str->capacity);

    char *aux_ptr = str->buffer;
    while (*backup.buffer != '\0') {
        *aux_ptr = *backup.buffer;
        backup.buffer++;
        aux_ptr++;
    }

    *aux_ptr = extra;
    aux_ptr++;
    *aux_ptr = '\0';
}

char *str_print(string *str) {
    return str->buffer;
}

void str_destroy(string str) {
    free(str.buffer);
}
#endif
