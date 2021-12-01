#include <stdio.h>
#include <ctype.h>
#include "string.h"
#include "cyclic_array.h"
#include <math.h>

char *at_bash_cipher(string *text, cyclic_array *letters) {
    string res;
    str_init(&res);

    char *aux_ptr = text->buffer;
    while (*aux_ptr != '\0') {
        // change to number and add a dash
        if (*aux_ptr >= 'a' && *aux_ptr <= 'z' || *aux_ptr >= 'A' && *aux_ptr <= 'Z') {
            const size_t current_index = c_arr_index(letters, toupper(*aux_ptr));
            const int RESERVE = current_index > 9 ? 3 : 2;
            char temp[RESERVE];
            sprintf(temp, "%lu", current_index);
            str_add(&res, temp);
            // str_add(&res, "-");
        } else {
            str_add_c(&res, *aux_ptr);
        }
        
        *aux_ptr++;
    }

    return res.buffer;
}

char *at_bash_decipher(string *text, cyclic_array *letters) {
    string res;
    str_init(&res);

    int *numbers = (int *) malloc(50 * sizeof(char));
    int current_number = 0;
    char *aux_ptr = text->buffer;
    char *item = (char *) malloc(3 * sizeof(char));

    size_t current_index = 0;
    while (*aux_ptr != '\0') {
        if ('0' <= *aux_ptr && *aux_ptr <= '9') {
            item[current_index++] = *aux_ptr;
        } else {
            item[current_index++] = '\0';
            char *aux_index_ptr = &item[current_index - 1];
            int power = 0;
            numbers[current_number] = 0;

            while (*aux_index_ptr != '\0') {
                numbers[current_number] += (*aux_index_ptr - 48) * pow(10, power);
                printf("c: %d\n", *aux_index_ptr);
                power++;
                aux_index_ptr--;
            }
            current_index = 0;
        }
        aux_ptr++;
    }

    for (int i = 0; i <= 9; i++) {
        printf("%d\n", numbers[i]);
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