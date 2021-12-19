// Copyright 2005, Google Inc.
// All rights reserved.
#include <iostream>
#include "gtest/gtest.h"
#include <string.h>
#include "cyclic_array.h"
#include "atbash.h"

using namespace ::testing;

TEST(TestAtbash, Characters) {
    cyclic_array out, *alphabet;
    alphabet = &out;

    char items[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    c_arr_init(alphabet, items);
    
    ASSERT_EQ(atbash_char_move('A', alphabet), 'Z');
    ASSERT_EQ(atbash_char_move('B', alphabet), 'Y');
    ASSERT_EQ(atbash_char_move('M', alphabet), 'N');
    ASSERT_EQ(atbash_char_move('N', alphabet), 'M');
    ASSERT_EQ(atbash_char_move('Y', alphabet), 'B');
    ASSERT_EQ(atbash_char_move('Z', alphabet), 'A');
    c_arr_destroy(alphabet);
}

TEST(TestAtbash, OneWordUppercase) {
    cyclic_array out, *alphabet;
    alphabet = &out;

    char items[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    c_arr_init(alphabet, items);

    char text[] = "GRAVITY";
    char cipher[] = "TIZERGB";
    char *generated = atbash_move(text, alphabet);
    ASSERT_EQ(strcmp(cipher, generated), 0);

    c_arr_destroy(alphabet);
}

TEST(TestAtbash, OneWord) {
    cyclic_array out, *alphabet;
    alphabet = &out;

    char items[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    c_arr_init(alphabet, items);

    char text[] = "Benjamin";
    char cipher[] = "YVMQZNRM";
    char *generated = atbash_move(text, alphabet);
    ASSERT_EQ(strcmp(cipher, generated), 0);

    c_arr_destroy(alphabet);
}

TEST(TestAtbash, Sentences) {
    cyclic_array out, *alphabet;
    alphabet = &out;

    char items[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    c_arr_init(alphabet, items);

    char text[86] = "Gravity Falls";
    char cipher[86] = "TIZERGB UZOOH";
    char *generated = atbash_move(text, alphabet);
    ASSERT_EQ(strcmp(cipher, generated), 0);

    strcpy(text, "Stanley is represented on the Zodiac wheel as the crescent symbol present on his fez.");
    strcpy(cipher, "HGZMOVB RH IVKIVHVMGVW LM GSV ALWRZX DSVVO ZH GSV XIVHXVMG HBNYLO KIVHVMG LM SRH UVA.");
    generated = atbash_move(text, alphabet);
    ASSERT_EQ(strcmp(cipher, generated), 0);

    c_arr_destroy(alphabet);
}

TEST(TestAtbash, SymmetryTest) {
    cyclic_array out, *alphabet;
    alphabet = &out;

    char items[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    c_arr_init(alphabet, items);

    char text[19] = "GRAVITY FALLS";
    char *generated = atbash_move(atbash_move(text, alphabet), alphabet);
    ASSERT_EQ(strcmp(text, generated), 0);

    strcpy(text, "BENJAMIN BERGSTROM");
    generated = atbash_move(atbash_move(text, alphabet), alphabet);
    ASSERT_EQ(strcmp(text, generated), 0);

    strcpy(text, "I CRAVE GAY SEX!!!");
    generated = atbash_move(atbash_move(text, alphabet), alphabet);
    ASSERT_EQ(strcmp(text, generated), 0);

    c_arr_destroy(alphabet);
}