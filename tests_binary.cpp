// Copyright 2005, Google Inc.
// All rights reserved.
#include <iostream>
#include "gtest/gtest.h"
#include <string.h>
#include <stdlib.h>
#include "cyclic_array.h"
#include "binary.h"
#include "utils/binary_conversion.h"
#include "utils/binary_conversion_int.h"

using namespace ::testing;

TEST(TestBinary, BinaryConversion) {
    char cipher[] = "01100001";
    char *res = binary_conversion('a'); 
    ASSERT_EQ(strcmp(cipher, res), 0);

    strcpy(cipher, "01000001");
    res = binary_conversion('A');
    ASSERT_EQ(strcmp(cipher, res), 0);

    strcpy(cipher, "01111000");
    res = binary_conversion('x');
    ASSERT_EQ(strcmp(cipher, res), 0);

    strcpy(cipher, "00101111");
    res = binary_conversion('/');
    ASSERT_EQ(strcmp(cipher, res), 0);

    strcpy(cipher, "00000000");
    res = binary_conversion(0x00);
    ASSERT_EQ(strcmp(cipher, res), 0);

    strcpy(cipher, "11111111");
    res = binary_conversion(0xff);
    ASSERT_EQ(strcmp(cipher, res), 0);

    strcpy(cipher, "11111110");
    res = binary_conversion(0xfe);
    ASSERT_EQ(strcmp(cipher, res), 0);
}

TEST(TestBinary, BinaryCiphers) {
    char text[33] = "gravity falls";
    char cipher[257] = "01100111011100100110000101110110011010010111010001111001001000000110011001100001011011000110110001110011";

    char *generated = binary_cipher(text);
    ASSERT_EQ(strcmp(cipher, generated), 0);

    strcpy(text, "I CRAVE gay sex!");
    strcpy(cipher, "01001001001000000100001101010010010000010101011001000101001000000110011101100001011110010010000001110011011001010111100000100001");
    generated = binary_cipher(text);
    ASSERT_EQ(strcmp(cipher, generated), 0);

    strcpy(text, "Billie Eilish: !!!!!!!");
    strcpy(cipher, "01000010011010010110110001101100011010010110010100100000010001010110100101101100011010010111001101101000001110100010000000100001001000010010000100100001001000010010000100100001");
    generated = binary_cipher(text);
    ASSERT_EQ(strcmp(cipher, generated), 0);

    strcpy(text, "It is okay to be autistic.");
    strcpy(cipher, "0100100101110100001000000110100101110011001000000110111101101011011000010111100100100000011101000110111100100000011000100110010100100000011000010111010101110100011010010111001101110100011010010110001100101110");
    generated = binary_cipher(text);
    ASSERT_EQ(strcmp(cipher, generated), 0);

    strcpy(text, "It's ALWAYS been okay to be gay!");
    strcpy(cipher, "0100100101110100001001110111001100100000010000010100110001010111010000010101100101010011001000000110001001100101011001010110111000100000011011110110101101100001011110010010000001110100011011110010000001100010011001010010000001100111011000010111100100100001");
    generated = binary_cipher(text);
    ASSERT_EQ(strcmp(cipher, generated), 0);

    strcpy(text, ">>>:::<<$$$$$$$!!!!!!!????@\\");
    strcpy(cipher, "00111110001111100011111000111010001110100011101000111100001111000010010000100100001001000010010000100100001001000010010000100001001000010010000100100001001000010010000100100001001111110011111100111111001111110100000001011100");
    generated = binary_cipher(text);
    ASSERT_EQ(strcmp(cipher, generated), 0);
}

TEST(TestBinary, BinaryDeciphersInvalid) {
    char cipher[] = "110000110010111";
    
    char *result = binary_decipher(cipher);
    char *invalid = (char *) malloc(1 * sizeof(char));
    invalid[0] = 0x01;

    ASSERT_EQ(strcmp(binary_decipher(cipher), invalid), 0);
    
    strcpy(cipher, "11100040");
    result = binary_decipher(cipher);
    ASSERT_EQ(strcmp(binary_decipher(cipher), invalid), 0);
}

TEST(TestBinary, BinaryDeconversion) {
    char cipher[] = "01100001";
    ASSERT_EQ(binary_conversion_int(cipher), 'a');

    strcpy(cipher, "0110000");
    ASSERT_EQ(binary_conversion_int(cipher), 0xff);

    strcpy(cipher, "11111111");
    ASSERT_EQ(binary_conversion_int(cipher), 0xff);

    strcpy(cipher, "01100010");
    ASSERT_EQ(binary_conversion_int(cipher), 'b');

    strcpy(cipher, "00100001");
    ASSERT_EQ(binary_conversion_int(cipher), '!');

    strcpy(cipher, "00100011");
    ASSERT_EQ(binary_conversion_int(cipher), '#');

    strcpy(cipher, "01010100");
    ASSERT_EQ(binary_conversion_int(cipher), 'T');

    strcpy(cipher, "11111110");
    ASSERT_EQ(binary_conversion_int(cipher), 0xfe);
}

TEST(TestBinary, BinaryDeciphers) {
    char cipher[1257] = "0110001001100010";
    char text[158] = "bb";

    char *generated = binary_decipher(cipher);
    ASSERT_EQ(strcmp(text, generated), 0);

    strcpy(cipher, "01000111011100100110000101110110011010010111010001111001001000000100011001100001011011000110110001110011");
    strcpy(text, "Gravity Falls");
    generated = binary_decipher(cipher);
    ASSERT_EQ(strcmp(text, generated), 0);

    strcpy(cipher, "01010011010101000100000101001110001000000100100101010011001000000100111001001111010101000010000001010111010010000100000101010100001000000100100001000101001000000101001101000101010001010100110101010011");
    strcpy(text, "STAN IS NOT WHAT HE SEEMS");
    generated = binary_decipher(cipher);
    ASSERT_EQ(strcmp(text, generated), 0);

    strcpy(cipher, "01000110011011110111001001100100001001110111001100100000011010010110010001100101011011100111010001101001011101000111100100100000011000010110111001100100001000000111011101101000011001010111001001100101011000010110001001101111011101010111010001110011001000000111011101100101011100100110010100100000011000010010000001100011011001010110111001110100011100100110000101101100001000000110110101111001011100110111010001100101011100100111100100100000011000010110111001100100001000000110010101101100011001010110110101100101011011100111010000100000011011110110011000100000011001100110111101110010011001010111001101101000011000010110010001101111011101110110100101101110011001110010000001101111011001100010000001110100011010000110010100100000010001110111001001100001011101100110100101110100011110010010000001000110011000010110110001101100011100110010000001110011011001010111001001101001011001010111001100100000011101010110111001110100011010010110110000100000011101000110100001100101001000000110110101101001011001000110010001101100011001010010000001101111011001100010000001110100011010000110010100100000011100110110100001101111011101110010011101110011001000000111001101100101011000110110111101101110011001000010000001110011011001010110000101110011011011110110111000101110");
    strcpy(text, "Ford's identity and whereabouts were a central mystery and element of foreshadowing of the Gravity Falls series until the middle of the show's second season.");
    generated = binary_decipher(cipher);
    ASSERT_EQ(strcmp(text, generated), 0);

    strcpy(cipher, "00111110001111100011111000111010001110100011101000111100001111000010010000100100001001000010010000100100001001000010010000100001001000010010000100100001001000010010000100100001001111110011111100111111001111110100000001011100");
    strcpy(text, ">>>:::<<$$$$$$$!!!!!!!????@\\");
    generated = binary_decipher(cipher);
    ASSERT_EQ(strcmp(text, generated), 0);
}