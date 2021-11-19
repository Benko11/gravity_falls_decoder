#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "string.h"
#include "cyclic_array.h"
#include "ciphers.h"

#define MAX_SIZE 1024 * 1024 * 1024

char cipher_menu(void);

cyclic_array letters;

int main(int argc, char const *argv[]) {
    c_arr_init(&letters, "ABCDEFGHIJKLMNOPQRSTUVWXYZ");

    char *input = (char *) malloc(MAX_SIZE);
    if (input == NULL) {
        fprintf(stderr, "Memory has not been allocated.\n");
        exit(EXIT_FAILURE);
    }

    printf("Text: ");
    fgets(input, MAX_SIZE, stdin);
    str_remove_trailing_newline(input);
    
    string text;
    str_init(&text);
    str_assign(&text, input);

    
    while (1) {
        char selection = cipher_menu();

        if (selection == '1') {
            printf("%s\n", caesar_cipher(&text, &letters));
            puts("");
        } else if (selection == '2') {

        } else if (selection == '3') {
            printf("%s\n", at_bash_cipher(&text, &letters));
        } else if (selection == '4') {

        } else if (selection == '5') {

        } else if (selection == '6') {

        } else if (selection == '7') {

        } else if (selection == '8') {

        } else if (selection == '9') {

        } else if (selection == 'q') {
            break;
        } else {
            puts("");
            puts("Invalid choice, please try again.");
        }
    }

    free(input);

    return EXIT_SUCCESS;
}

char cipher_menu() {
    char input;

    puts("(1) - Caesar (cipher)");
    puts("(2) - Caesar (decipher)");
    puts("(3) - AIZ26 (cipher)");
    puts("(4) - AIZ26 (decipher)");
    puts("(5) - Atbash");
    puts("(6) - Binary (cipher)");
    puts("(7) - Binary (decipher)");
    puts("(8) - Vigenere (cipher)");
    puts("(9) - Vigenere (decipher)");
    puts("(q) - quit");
    puts("NOTE: You will be asked for a key in Vigenere ciphers.");
    puts("");
    printf("Select which cipher you want to apply to the text (1-9): ");

    fscanf(stdin, "%1s", &input);

    puts("");

    return input;
}

