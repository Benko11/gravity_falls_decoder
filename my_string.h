#include <stdlib.h>
#include "my_string_helpers.h"

#ifndef STRING_H
#define STRING_H

typedef struct string_t {
    char *buffer;
    size_t capacity;
} string;

void str_init(string*);
void str_assign(string*, char*);
void str_add(string*, char*);
void str_add_c(string*, char);
char *str_get(string*);

void str_init(string *str) {
    str->buffer = (char *) malloc(1 * sizeof(char));
    str->capacity = 1;
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

    size_t size = str->capacity + str_size(extra);
    while (size > str->capacity) {
        str->capacity *= 2;
    }

    char *backup = str->buffer;
    str->buffer = NULL;
    str->buffer = realloc(str->buffer, str->capacity);
    
    char *aux_ptr = str->buffer;
    while (*backup != '\0') {
        *aux_ptr = *backup;
        backup++;
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
    str_init(&backup);
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

char *str_get(string *str) {
    return str->buffer;
}

void str_destroy(string *str) {
    free(str);
}
#endif
