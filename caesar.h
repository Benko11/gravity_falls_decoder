#include <stdlib.h>
#include <ctype.h>
#include "crappy_string.h"
#include "cyclic_array.h"

#ifndef CAESAR_H
#define CAESAR_H

char *caesar_move(char *text, cyclic_array *alphabet, int forwards) {
    crappy_string out, *res;
    res = &out;
    str_init(res);

    int direction = forwards == 1 ? 3 : -3;
    int i = 0;
    while (*text != '\0') {
        int letter_check = is_letter(*text);

        if (letter_check == 1)
            *text = toupper(*text);

        char aux[2];
        aux[0] = letter_check == 1 ? c_arr_move(alphabet, *text, direction) : *text;
        aux[1] = '\0';

        str_add(res, aux);
        text++;
    }

    return str_get(res);
}

char *caesar_cipher(char *text, cyclic_array *alphabet) {
   return caesar_move(text, alphabet, 1);
}

char *caesar_decipher(char *text, cyclic_array *alphabet) {
   return caesar_move(text, alphabet, 0);
}
#endif