#include <stdlib.h>
#include <ctype.h>
#include "crappy_string.h"
#include "cyclic_array.h"

#ifndef CAESAR_H
#define CAESAR_H
char *caesar_cipher(char *text, cyclic_array *alphabet) {
    crappy_string out, *res;
    res = &out;
    str_init(res);

    int i = 0;
    while (*text != '\0') {
        int letter_check = is_letter(*text);

        if (letter_check == 1)
            *text = toupper(*text);

        char aux[2];
        aux[0] = letter_check == 1 ? c_arr_move(alphabet, *text, 3) : *text;
        aux[1] = '\0';

        str_add(res, aux);
        text++;
    }

    return str_get(res);
}
#endif