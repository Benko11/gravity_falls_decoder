#ifndef IS_ALL_BINARY_H
#define IS_ALL_BINARY_H

int is_all_binary(char *text) {
    while (*text != '\0') {
        if (*text != '0' && *text != '1')
            return 0;
        text++;
    }

    return 1;
}
#endif