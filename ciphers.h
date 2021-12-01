#include <stdio.h>
#include <ctype.h>
#include "string.h"
#include "cyclic_array.h"

char *at_bash_cipher(string *text, cyclic_array *letters) {
    string res;
    str_init(&res);

    char *aux_ptr = text->buffer;
    while (*aux_ptr != '\0') {
        // change to number and add a dash
        if (*aux_ptr >= 'a' && *aux_ptr <= 'z' || *aux_ptr >= 'A' && *aux_ptr <= 'Z') {
            const size_t current_index = c_arr_index(letters, toupper(*aux_ptr));
            printf("Current index: %lu\n", current_index);
            const int RESERVE = current_index > 9 ? 3 : 2;
            printf("Reserve: %d\n", RESERVE);
            char temp[RESERVE];
            sprintf(temp, "%lu", current_index);
            printf("Temp: %s\n", temp);
            printf("Capacity: %s\n", text->buffer);
            str_add(&res, temp);
        } else {
            str_add_c(&res, *aux_ptr);
        }
        *aux_ptr++;
    }

    return res.buffer;
}

char *caesar_cipher(string *text, cyclic_array *letters) {
    string res;
    str_init(&res);

    while (*text->buffer != '\0') {
        if (*text->buffer >= 'a' && *text->buffer <= 'z' || *text->buffer >= 'A' && *text->buffer <= 'Z') {
            str_add_c(&res, c_arr_move(letters, toupper(*text->buffer), 3));
        } else {
            str_add_c(&res, *text->buffer);
        }
        text->buffer++;
    }

    return res.buffer;
}

char *caesar_decipher(string *text, cyclic_array *letters) {
    string res;
    str_init(&res);

    while (*text->buffer != '\0') {
        if (*text->buffer >= 'a' && *text->buffer <= 'z' || *text->buffer >= 'A' && *text->buffer <= 'Z') {
            str_add_c(&res, c_arr_move(letters, toupper(*text->buffer), -3));
        } else {
            str_add_c(&res, *text->buffer);
        }
        text->buffer++;
    }

    return res.buffer;
}