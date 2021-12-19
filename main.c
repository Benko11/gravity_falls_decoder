#include <stdio.h>
#include <stdlib.h>
#include "cyclic_array.h"

int main(int argc, char const *argv[]) {
    cyclic_array out, *alphabet;
    alphabet = &out;
    c_arr_init(alphabet, "ABCDEFGHIJKLMNOPQRSTUVWXYZ");
    printf("%c\n", c_arr_move(alphabet, 'Y', 15));
    c_arr_destroy(alphabet);
    
    return EXIT_SUCCESS;
}
