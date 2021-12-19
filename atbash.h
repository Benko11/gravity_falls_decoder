#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "crappy_string.h"
#include "cyclic_array.h"
#include "utils/is_letter.h"

#ifndef ATBASH_H
#define ATBASH_H

char *atbash_move(char *text, cyclic_array *alphabet);
char atbash_char_move(char character, cyclic_array *alphabet);

char *atbash_move(char *text, cyclic_array *alphabet) {
    crappy_string out, *res;
    res = &out;
    str_init(res);

    while (*text != '\0') {
        int letter_check = is_letter(*text);
        char aux[2];
        if (letter_check == 1) {
            *text = toupper(*text);
            aux[0] = atbash_char_move(*text, alphabet);
        } else {
            aux[0] = *text;
        }

        aux[1] = '\0';
        str_add(res, aux);
        text++;
    }

    char *result = (char *) malloc((strlen(str_get(res)) + 1) * sizeof(char));
    strcpy(result, str_get(res));
    str_destroy(res);

    return result;
}

char atbash_char_move(char character, cyclic_array *alphabet) {
    const int index = c_arr_number(alphabet, character);
    const size_t size = strlen(c_arr_all_items(alphabet));
    return c_arr_at(alphabet, size - (index - 1));
}
#endif