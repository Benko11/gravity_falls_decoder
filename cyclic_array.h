#include <stdio.h>
#include <string.h>

#ifndef CYCLIC_ARRAY_H
#define CYCLIC_ARRAY_H
typedef struct {
    char *buffer;
} cyclic_array;

void c_arr_init(cyclic_array *c_arr, char *items);
char *c_arr_all_items(cyclic_array *c_arr);
char c_arr_move(cyclic_array *c_arr, char start, int steps);
int c_arr_number(cyclic_array *c_arr, char seek);
char c_arr_at(cyclic_array *c_arr, size_t index);
void c_arr_destroy(cyclic_array *c_arr);

void c_arr_init(cyclic_array *c_arr, char *items) {
    size_t length = strlen(items) + 1;
    c_arr->buffer = (char *) malloc(length * sizeof(char));
    strcpy(c_arr->buffer, items);

    printf("Items: %s\n", c_arr->buffer);
}

char *c_arr_all_items(cyclic_array *c_arr) {
    return c_arr->buffer;
}

// indices start at 1
char c_arr_at(cyclic_array *c_arr, size_t index) {
    size_t length = strlen(c_arr->buffer);
    
    if (index <= 0 || index > length)
        return 0;

    return c_arr->buffer[index - 1];
}

int c_arr_number(cyclic_array *c_arr, char seek) {
    char *buffer = c_arr_all_items(c_arr);

    for (int i = 0; i < strlen(buffer); i++) {
        if (buffer[i] == seek)
            return i + 1;
    }

    return -1;
}

char c_arr_move(cyclic_array *c_arr, char start, int steps) {
    if (steps == 0) return start;

    size_t length = strlen(c_arr->buffer);
    size_t move = abs(steps) % length;
    
    int index = c_arr_number(c_arr, start);
    if (index == -1)
        return 0;
        
    int change = steps > 0 ? 1 : -1;

    for (int i = 0; i < move; i++) {
        index += change;
        if (index <= 0) {
            index = length;
            continue;
        }

        if (index > length) {
            index = 1;
        }
    }

    return c_arr_at(c_arr, index);
}

void c_arr_destroy(cyclic_array *c_arr) {
    free(c_arr->buffer);
}
#endif