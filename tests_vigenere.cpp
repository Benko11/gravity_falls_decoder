// Copyright 2005, Google Inc.
// All rights reserved.
#include <iostream>
#include "gtest/gtest.h"
#include <string.h>
#include "cyclic_array.h"
#include "vigenere.h"

TEST(TestVigenere, UppercaseStrings) {
    cyclic_array out, *alphabet;
    alphabet = &out;

    char key[10] = "AB";
    char items[27];
    strcpy(items, "ABCDEFGHIJKLMNOPQRSTUVWXYZ");

    char text[19] = "GRAVITY FALLS";
    char cipher[19] = "GSAWIUY GAMLT";

    c_arr_init(alphabet, items);
    char *res = vigenere_cipher(text, alphabet, key);

    ASSERT_EQ(strcmp(cipher, res), 0);

    strcpy(key, "JEWISH");
    strcpy(text, "BENJAMIN BERGSTROM");
    strcpy(cipher, "KIJRSTRR XMJNBXNWE");
    res = vigenere_cipher(text, alphabet, key);

    ASSERT_EQ(strcmp(cipher, res), 0);

    c_arr_destroy(alphabet);
}

TEST(TestVigenere, ComplexKeys) {
    cyclic_array out, *alphabet;
    alphabet = &out;

    char key[] = "BILL CIPHER";
    char items[27];
    strcpy(items, "ABCDEFGHIJKLMNOPQRSTUVWXYZ");

    char text[19] = "GRAVITY FALLS";
    char cipher[19] = "HZLGKBN MECMA";

    c_arr_init(alphabet, items);
    char *res = vigenere_cipher(text, alphabet, key);
    ASSERT_EQ(strcmp(cipher, res), 0);

    c_arr_destroy(alphabet);
}

TEST(TestVigenere, ComplexKeys2) {
    cyclic_array out, *alphabet;
    alphabet = &out;

    char key[] = "BILL       $";
    char items[27];
    strcpy(items, "ABCDEFGHIJKLMNOPQRSTUVWXYZ");

    char text[19] = "GRAVITY FALLS";
    char cipher[19] = "HZLGJBJ QBTWD";

    c_arr_init(alphabet, items);
    char *res = vigenere_cipher(text, alphabet, key);
    ASSERT_EQ(strcmp(cipher, res), 0);

    c_arr_destroy(alphabet);
}

TEST(TestVigenere, ComplexKeys3) {
    cyclic_array out, *alphabet;
    alphabet = &out;

    char key[] = "--666-- BILL-";
    char items[27];
    strcpy(items, "ABCDEFGHIJKLMNOPQRSTUVWXYZ");

    char text[19] = "GRAVITY FALLS";
    char cipher[19] = "HZLGJBJ QBTWD";

    c_arr_init(alphabet, items);
    char *res = vigenere_cipher(text, alphabet, key);
    ASSERT_EQ(strcmp(cipher, res), 0);

    c_arr_destroy(alphabet);
}

TEST(TestVigenereDecipher, UppercaseStrings) {
    cyclic_array out, *alphabet;
    alphabet = &out;

    char key[10] = "AB";
    char items[27];
    strcpy(items, "ABCDEFGHIJKLMNOPQRSTUVWXYZ");

    char text[19] = "GSAWIUY GAMLT";
    char cipher[19] = "GRAVITY FALLS";

    c_arr_init(alphabet, items);
    char *res = vigenere_decipher(text, alphabet, key);

    ASSERT_EQ(strcmp(cipher, res), 0);

    strcpy(key, "JEWISH");
    strcpy(text, "KIJRSTRR XMJNBXNWE");
    strcpy(cipher, "BENJAMIN BERGSTROM");
    res = vigenere_decipher(text, alphabet, key);

    ASSERT_EQ(strcmp(cipher, res), 0);

    c_arr_destroy(alphabet);
}

TEST(TestVigenereDecipher2, ComplexKeys) {
    cyclic_array out, *alphabet;
    alphabet = &out;

    char key[] = "BILL CIPHER";
    char items[27];
    strcpy(items, "ABCDEFGHIJKLMNOPQRSTUVWXYZ");

    char text[19] = "HZLGKBN MECMA";
    char cipher[19] = "GRAVITY FALLS";

    c_arr_init(alphabet, items);
    char *res = vigenere_decipher(text, alphabet, key);
    ASSERT_EQ(strcmp(cipher, res), 0);

    c_arr_destroy(alphabet);
}

TEST(TestVigenereDecipher3, ComplexKeys2) {
    cyclic_array out, *alphabet;
    alphabet = &out;

    char key[] = "BILL       $";
    char items[27];
    strcpy(items, "ABCDEFGHIJKLMNOPQRSTUVWXYZ");

    char text[19] = "HZLGJBJ QBTWD";
    char cipher[19] = "GRAVITY FALLS";

    c_arr_init(alphabet, items);
    char *res = vigenere_decipher(text, alphabet, key);
    ASSERT_EQ(strcmp(cipher, res), 0);

    c_arr_destroy(alphabet);
}

TEST(TestVigenereDecipher4, ComplexKeys3) {
    cyclic_array out, *alphabet;
    alphabet = &out;

    char key[] = "--666-- BILL-";
    char items[27];
    strcpy(items, "ABCDEFGHIJKLMNOPQRSTUVWXYZ");

    char text[19] = "HZLGJBJ QBTWD";
    char cipher[19] = "GRAVITY FALLS";

    c_arr_init(alphabet, items);
    char *res = vigenere_decipher(text, alphabet, key);
    ASSERT_EQ(strcmp(cipher, res), 0);

    c_arr_destroy(alphabet);
}