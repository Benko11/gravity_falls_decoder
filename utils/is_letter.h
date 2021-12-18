#ifndef IS_LETTER_H
#define IS_LETTER_H
int is_letter(char character) {
    if (('a' <= character && character <= 'z') || ('A' <= character && character <= 'Z'))
        return 1;
    return 0;
}
#endif