# Gravity Falls Decoder

This project is inspired by [http://themysteryofgravityfalls.com](http://themysteryofgravityfalls.com/), a website, which allows user to input text and cipher it according to miscellaneous ciphers, such as [Vigenere](https://en.wikipedia.org/wiki/Vigen%C3%A8re_cipher), [Caesar](https://en.wikipedia.org/wiki/Caesar_cipher), [Atbash](https://en.wikipedia.org/wiki/Atbash), AIZ26 (mapping letters to numbers), Binary (binary representation of each character from ASCII), etc. The aim of this project is to replicate that functionality while using low-level programming languages, namely `C` and `C++` for `GoogleTest` framework.

**IMPORTANT:** If you haven't watched [Gravity Falls](https://www.imdb.com/title/tt1865718/?ref_=fn_al_tt_1), you really ought to do so pronto.

![Gravity Falls](https://wallpaperaccess.com/full/5989762.jpg)

## Structure

All the logic of the programme is stored in `.h` files in the root directory, such as `cyclic_array.h`. `.c` files in the root directory serve as potential entry points for the user interacting with the application.

Test files are stored in the root directory in a form of `tests_<feature>.cpp`. Running these tests and their passing ensures proper functionality of the application.

`utils` directory contains helper functions whose purpose was considered too general to be included in the root directory.

The rest of the files represent a scaffolding for a `GoogleTest` application, and they are necessary for the tests to run properly.

## Launching

`main.c` represents the executable file. Assumed platform is Linux, other platforms may generate unexpected results in printing routines. Recommended way of compiling the file is described in the Makefile under `make run`.

Programme can operate in two CLI modes. One mode represents the user with an intuitive text interface. Other mode allows immediate execution of the programme for a given cipher by passing in command-line arguments. To learn about more about them, use `./main.out help`. Below is the transcipt of help:

```
usage: ./main.out <cipher_type> <text> <key>
<cipher_type> - numerical value of the cipher or its abbreviation
<text> - desired user input without spaces
<key> - (optional) hashing key for selected ciphers (Vigenere)

Cipher types:
Vigenere cipher: 1 | vigc
Vigenere decipher: 2 | vigd
Caesar cipher: 3 | caec
Caesar decipher: 4 | caed
Binary cipher: 5 | binc
Binary decipher: 6 | bind
Atbash: 7 | atbash

usage: ./main.out - enters the CLI
```

## Programme logic

### `crappy_string.h`

Somewhat unflattering name is inspired by the everlasting strife the author encountered while trying to make it work.

String capacity is thought to be the largest theoretical number of characters, until memory has been reallocated.

`void str_init(crappy_string *str)` - takes a pointer to a structure of type `crappy_string` and initializes buffer for writing. By default, two bytes are allocated, for a 1-character string. String's max capacity is also set to `1`, ignoring the `\0` character. These values cannot be overriden.

`void str_assign(crappy_string *str, char *value)` - works to assign a value to the string structure, based on the paramater `char *value`.
This should usually be done right after `str_init()` has been called, but based on tests, it should work on a string that already has some value in it, overriding everything. String's capacity is updated accordingly, along with dynamically-sized buffer.

`void str_add(crappy_string *str, char *value)` - adds character array passed in `char *value` to the buffer, and updates string's capacity, along with dynamically-sized buffer. It also works right after `str_init()` call.

`char *str_get(crappy_string *str)` - helper function that returns the current value of the string's buffer.

`void str_destroy(crappy_string *str)` - frees up dynamically allocated buffer.

### `cyclic_array.h`

Represents a cyclic array data structure, whose values are all characters. It takes any index in the array's range and allows to traverse over it in a metaphorical 'circle'. (After end has been reached, we are at the beginning of the array, and vice versa.)

`void c_arr_init(cyclic_array *c_arr, char *items)` - initializes the array buffer by dynamically allocating number of bytes based on the size of `char *items`. It returns an error when there are duplicate elements in `*items`.

`char *c_arr_all_items(cyclic_array *c_arr)` - helper function that returns the entire buffer, or array of characters in a string.

`char c_arr_move(cyclic_array *c_arr, char start, int steps)` - moves in a cyclic_array `*c_arr` (pointer to it is passed to preserve changes), it starts at `start`, which is a character in the array (assuming each item in the array is unique) and moves by `steps` steps. Negative direction implies moving in the opposite direction (anti-clockwise in a circle).

`int c_arr_number(cyclic_array *c_arr, char seek)` - each element in the array is represented by a numerical index. First item is `1`, second is `2`, and so on. It seeks a `seek` character in the array and returns that index.

`char c_arr_at(cyclic_array *c_arr, size_t index)` - returns a character, which is at index `size_t index`. Same rules as for `c_arr_number()` are used for indexing.

`void c_arr_destroy(cyclic_array *c_arr)` - frees up dynamically allocated buffer

### `caesar.h`

Uses cyclic array to determine Caesar cipher. As is originated from the series and the source website mentioned above, this cipher only moves a fixed number of steps to the right or left (3).

`char *caesar_move(char *text, cyclic_array *alphabet, int forwards)` - generic function, which takes the text, the alphabet in which it is going to be moving, and the direction `forwards`, where `1` represents forward movement, anything else is backwards.

`char *caesar_cipher(char *text, cyclic_array *alphabet)` - specific implementation of the `caesar_move()` function in forward movement.

`char *caesar_decipher(char *text, cyclic_array *alphabet)` - specific implementation of the `caesar_move()` function in backward movement.

### `vigenere.h`

Vigenere is similar to Caesar cipher, but for ciphering it takes an additional key, which determines offsets in the cyclic alphabet.

`char *vigenere_move(char *text, cyclic_array *alphabet, char *key, int forwards)` - generic function, which uses the key to cycle in the alphabet accordingly. `int forwards` parameter specifies the direction of the movement for ALL translations.

`char *vigenere_cipher(char *text, cyclic_array *alphabet, char *key)` - specific implementation of the `vigenere_move()` function in forward movement

`char *vigenere_decipher(char *text, cyclic_array *alphabet, char *key)` - specific implementation of the `vigenere_move()` function in backward movement

### `atbash.h`

Atbash cipher returns the 'opposite' (i.e. `'Z'` for `'A'`, `'B'` for `'Y'`, etc.) character in the alphabet for each letter in a string.

`char atbash_char_move(char character, cyclic_array *alphabet)` - helper function, which for each character returns the 'opposite' character, as specified above.

`char *atbash_move(char *text, cyclic_array *alphabet)` - returns a string, which has had the atbash cipher/decipher applied to it.

### `binary.h`

Binary cipher/decipher turns an ASCII string into binary and vice versa.

`char *binary_cipher(char *text)` - turns an ASCII string into binary string and returns it. ASCII rule is assumed, but not explicitly enforced or handled.

`char *binary_decipher(char *cipher)` - turns a binary string into ASCII. It also checks whether a binary string is valid (its length must be a multiple of 8, as each character is represented with 8 bits, and it must not contain non-binary characters).

### `utils/`

`unsigned char binary_conversion_int(char *numeric)` - function returns a character number from the binary string in `char *numeric`.

`char *binary_conversion(unsigned char character)` - function returns a binary string from the character `unsigned char character`.

`int is_all_binary(char *text)` - checks whether a given string `char *text` presumed to be binary is really binary.

`int is_letter(char character)` - checks whether a given character `char character` is a letter.

`char *strtouppercase(char *word)` - turns the word into one with all uppercase letters and returns it.
