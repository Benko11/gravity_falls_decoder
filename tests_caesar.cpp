// Copyright 2005, Google Inc.
// All rights reserved.
#include <iostream>
#include "gtest/gtest.h"
#include <string.h>
#include "cyclic_array.h"
#include "caesar.h"

using namespace ::testing;
TEST(TestCaesar, OneWordUppercaseStrings) {
    cyclic_array out, *alphabet;
    alphabet = &out;

    char items[27];
    strcpy(items, "ABCDEFGHIJKLMNOPQRSTUVWXYZ");

    char text[12];
    strcpy(text, "GRAVITY");

    char cipher[12];
    strcpy(cipher, "JUDYLWB");

    c_arr_init(alphabet, items);
    char *generated = caesar_cipher(text, alphabet);
    ASSERT_EQ(strcmp(cipher, generated), 0);
    
    strcpy(text, "FALLS");
    strcpy(cipher, "IDOOV");
    generated = caesar_cipher(text, alphabet);
    ASSERT_EQ(strcmp(cipher, generated), 0);

    strcpy(text, "HELLO");
    strcpy(cipher, "KHOOR");
    generated = caesar_cipher(text, alphabet);
    ASSERT_EQ(strcmp(cipher, generated), 0);

    strcpy(text, "CONFIELD");
    strcpy(cipher, "FRQILHOG");
    generated = caesar_cipher(text, alphabet);
    ASSERT_EQ(strcmp(cipher, generated), 0);

    strcpy(text, "GAY");
    strcpy(cipher, "JDB");
    generated = caesar_cipher(text, alphabet);
    ASSERT_EQ(strcmp(cipher, generated), 0);

    c_arr_destroy(alphabet);
}

TEST(TestCaesar, OneWordStrings) {
    cyclic_array out, *alphabet;
    alphabet = &out;

    char items[27];
    strcpy(items, "ABCDEFGHIJKLMNOPQRSTUVWXYZ");

    char text[12];
    strcpy(text, "Gravity");

    char cipher[12];
    strcpy(cipher, "JUDYLWB");

    c_arr_init(alphabet, items);
    char *generated = caesar_cipher(text, alphabet);
    ASSERT_EQ(strcmp(cipher, generated), 0);
    
    strcpy(text, "falls");
    strcpy(cipher, "IDOOV");
    generated = caesar_cipher(text, alphabet);
    ASSERT_EQ(strcmp(cipher, generated), 0);

    strcpy(text, "hellO");
    strcpy(cipher, "KHOOR");
    generated = caesar_cipher(text, alphabet);
    ASSERT_EQ(strcmp(cipher, generated), 0);

    strcpy(text, "CoNfIeLd");
    strcpy(cipher, "FRQILHOG");
    generated = caesar_cipher(text, alphabet);
    ASSERT_EQ(strcmp(cipher, generated), 0);

    strcpy(text, "gay");
    strcpy(cipher, "JDB");
    generated = caesar_cipher(text, alphabet);
    ASSERT_EQ(strcmp(cipher, generated), 0);

    c_arr_destroy(alphabet);
}

TEST(TestCaesar, Sentences) {
    cyclic_array out, *alphabet;
    alphabet = &out;

    char items[27];
    strcpy(items, "ABCDEFGHIJKLMNOPQRSTUVWXYZ");

    char text[63];
    strcpy(text, "Gravity Falls");

    char cipher[63];
    strcpy(cipher, "JUDYLWB IDOOV");

    c_arr_init(alphabet, items);
    char *generated = caesar_cipher(text, alphabet);
    ASSERT_EQ(strcmp(cipher, generated), 0);
    
    strcpy(text, "Billie Eilish makes pretty good music.");
    strcpy(cipher, "ELOOLH HLOLVK PDNHV SUHWWB JRRG PXVLF.");
    generated = caesar_cipher(text, alphabet);
    ASSERT_EQ(strcmp(cipher, generated), 0);

    strcpy(text, "Radiohead make out-of-this-world music!");
    strcpy(cipher, "UDGLRKHDG PDNH RXW-RI-WKLV-ZRUOG PXVLF!");
    generated = caesar_cipher(text, alphabet);
    ASSERT_EQ(strcmp(cipher, generated), 0);

    strcpy(text, "I CRAVE gay sex");
    strcpy(cipher, "L FUDYH JDB VHA");
    generated = caesar_cipher(text, alphabet);
    ASSERT_EQ(strcmp(cipher, generated), 0);

    strcpy(text, "It is time to GROW UP and take course of life into your hands.");
    strcpy(cipher, "LW LV WLPH WR JURZ XS DQG WDNH FRXUVH RI OLIH LQWR BRXU KDQGV.");
    generated = caesar_cipher(text, alphabet);
    ASSERT_EQ(strcmp(cipher, generated), 0);

    c_arr_destroy(alphabet);
}

TEST(TestCaesarDecipher, OneWordUppercaseStrings) {
    cyclic_array out, *alphabet;
    alphabet = &out;

    char items[27];
    strcpy(items, "ABCDEFGHIJKLMNOPQRSTUVWXYZ");

    char text[12];
    strcpy(text, "JUDYLWB");

    char cipher[12];
    strcpy(cipher, "GRAVITY");

    c_arr_init(alphabet, items);
    char *generated = caesar_decipher(text, alphabet);
    ASSERT_EQ(strcmp(cipher, generated), 0);

    strcpy(text, "IDOOV");
    strcpy(cipher, "FALLS");
    generated = caesar_decipher(text, alphabet);
    ASSERT_EQ(strcmp(cipher, generated), 0);

    strcpy(text, "FRQILHOG");
    strcpy(cipher, "CONFIELD");
    generated = caesar_decipher(text, alphabet);
    ASSERT_EQ(strcmp(cipher, generated), 0);

    strcpy(text, "JDB");
    strcpy(cipher, "GAY");
    generated = caesar_decipher(text, alphabet);
    ASSERT_EQ(strcmp(cipher, generated), 0);

    c_arr_destroy(alphabet);
}

TEST(TestCaesarDecipher2, OneWordStrings) {
    cyclic_array out, *alphabet;
    alphabet = &out;

    char items[27];
    strcpy(items, "ABCDEFGHIJKLMNOPQRSTUVWXYZ");

    char text[12];
    strcpy(text, "judylwb");

    char cipher[12];
    strcpy(cipher, "GRAVITY");

    c_arr_init(alphabet, items);
    char *generated = caesar_decipher(text, alphabet);
    ASSERT_EQ(strcmp(cipher, generated), 0);

    strcpy(text, "iDOOv");
    strcpy(cipher, "FALLS");
    generated = caesar_decipher(text, alphabet);
    ASSERT_EQ(strcmp(cipher, generated), 0);

    strcpy(text, "fRQILhog");
    strcpy(cipher, "CONFIELD");
    generated = caesar_decipher(text, alphabet);
    ASSERT_EQ(strcmp(cipher, generated), 0);

    strcpy(text, "jdb");
    strcpy(cipher, "GAY");
    generated = caesar_decipher(text, alphabet);
    ASSERT_EQ(strcmp(cipher, generated), 0);

    c_arr_destroy(alphabet);
}

TEST(TestCaesarDecipher3, Sentences) {
    cyclic_array out, *alphabet;
    alphabet = &out;

    char items[27];
    strcpy(items, "ABCDEFGHIJKLMNOPQRSTUVWXYZ");

    char text[63];
    strcpy(text, "Judylwb idoov");

    char cipher[63];
    strcpy(cipher, "GRAVITY FALLS");

    c_arr_init(alphabet, items);
    char *generated = caesar_decipher(text, alphabet);
    ASSERT_EQ(strcmp(cipher, generated), 0);
    
    strcpy(text, "eloolh hlolvk pdnhv SUHWWB JRRG pxvlf.");
    strcpy(cipher, "BILLIE EILISH MAKES PRETTY GOOD MUSIC.");
    generated = caesar_decipher(text, alphabet);
    ASSERT_EQ(strcmp(cipher, generated), 0);

    strcpy(text, "Udglrkhdg pdnh rxw-ri-wklv-zruog pxvlf!");
    strcpy(cipher, "RADIOHEAD MAKE OUT-OF-THIS-WORLD MUSIC!");
    generated = caesar_decipher(text, alphabet);
    ASSERT_EQ(strcmp(cipher, generated), 0);

    strcpy(text, "L FUDYH jdb vha");
    strcpy(cipher, "I CRAVE GAY SEX");
    generated = caesar_decipher(text, alphabet);
    ASSERT_EQ(strcmp(cipher, generated), 0);

    strcpy(text, "Lw lv wlph wr JURZ XS dqg wdnh frxuvh ri olih lqwr brxu kdqgv.");
    strcpy(cipher, "IT IS TIME TO GROW UP AND TAKE COURSE OF LIFE INTO YOUR HANDS.");
    generated = caesar_decipher(text, alphabet);
    ASSERT_EQ(strcmp(cipher, generated), 0);

    c_arr_destroy(alphabet);
}
