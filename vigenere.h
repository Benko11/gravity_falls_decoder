#include <stdlib.h>
#include <ctype.h>
#include "crappy_string.h"
#include "cyclic_array.h"

#ifndef VIGENERE_H
#define VIGENERE_H
char *vigenere_move(char *text, cyclic_array *alphabet, char *key, int forwards) {
    crappy_string out, *res;
    res = &out;
    str_init(res);

    const int LIMIT = strlen(key);
    int key_index = 0;

    while (*text != '\0') {
        int letter_check = is_letter(*text);
        char aux[2];
        
        if (letter_check == 1) {
            *text = toupper(*text);
            char current_key = key[key_index];
            while (is_letter(current_key) != 1) {
                current_key = key[++key_index];

                if (key_index >= LIMIT) {
                    key_index = -1;
                }
            }

        
            if (++key_index >= LIMIT) {
                key_index = 0;
            }

            int alphabet_index = c_arr_number(alphabet, current_key) - 1;
            if (forwards != 1) {
                alphabet_index *= -1;
            }

            aux[0] = c_arr_move(alphabet, *text, alphabet_index);
        } else {
            aux[0] = *text;
        }

        aux[1] = '\0';

        str_add(res, aux);
        text++;
    }

    return str_get(res);
}

char *vigenere_cipher(char *text, cyclic_array *alphabet, char *key) {
    return vigenere_move(text, alphabet, key, 1);
}

char *vigenere_decipher(char *text, cyclic_array *alphabet, char *key) {
    return vigenere_move(text, alphabet, key, 0);
}
#endif