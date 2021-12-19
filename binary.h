#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "crappy_string.h"
#include "utils/is_letter.h"
#include "utils/binary_conversion.h"
#include "utils/binary_conversion_int.h"
#include "utils/is_all_binary.h"

char *binary_cipher(char *text) {
    crappy_string out, *res;
    res = &out;
    str_init(res);

    while (*text != '\0') {
        str_add(res, binary_conversion(*text));
        text++;
    }

    return str_get(res);
}

char *binary_decipher(char *cipher) {
    const size_t size = strlen(cipher);
    if (size % 8 != 0 || is_all_binary(cipher) != 1) {
        char *aux = (char *) malloc (1 * sizeof(char));
        aux[0] = 0x01;
        return aux;
    }

    crappy_string out, *res;
    res = &out;
    str_init(res);

    char *current = (char *) malloc(9 * sizeof(char));
    memset(current, '0', 8);
    current[8] = '\0';

    for (int i = 0; i < size; i += 8) {
        for (int j = 0; j < 8; j++) {
            current[j] = cipher[i + j]; 
        }

        unsigned char character = binary_conversion_int(current);
        char aux[2];
        aux[1] = '\0';
        aux[0] = character;

        str_add(res, aux);
    }

    return str_get(res);
}