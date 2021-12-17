#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "../my_string.h"
#include "../cyclic_array.h"
#include "../ciphers.h"

void assign_to_string() {   
    string name;
    str_init(&name);
    str_assign(&name, "Benjamin");
    assert(strcmp(name.buffer, "Benjamin") == 0);
    str_destroy(&name);

    string text;
    str_init(&text);
    str_assign(&text, "B Bergstrom Hello Howdy Whatup Grunkle Stan");
    assert(strcmp(text.buffer, "B Bergstrom Hello Howdy Whatup Grunkle Stan") == 0);
    str_destroy(&text);

    string gf;
    str_init(&gf);
    str_assign(&gf, "Gravity Falls is an American mystery-comedy animated television series created by Alex Hirsch for Disney Channel and Disney XD.");
    assert(strcmp(gf.buffer, "Gravity Falls is an American mystery-comedy animated television series created by Alex Hirsch for Disney Channel and Disney XD.") == 0);
    str_destroy(&gf);

    string long_text;
    str_init(&long_text);
    char *filename = "long_text.txt";
    
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        fprintf(stderr, "File not found\n");
        exit(EXIT_FAILURE);
    }

    fseek(fp, 0, SEEK_END);
    long filesize = ftell(fp);
    rewind(fp);

    char *buffer = (char *) malloc(filesize);
    fread(buffer, 1, filesize, fp);

    str_assign(&long_text, buffer);
    assert(strcmp(long_text.buffer, buffer) == 0);
    str_destroy(&long_text);
    buffer = NULL;
    free(buffer);

    puts("✔️ Assignment to string");
}

void add_to_string() {
    string str;
    str_init(&str);
    str_assign(&str, "a");

    assert(str.buffer == "a");

    str_add(&str, "bc");
    assert(strcmp(str.buffer, "abc") == 0);
    // str_destroy(&str);

    string str2;
    str_init(&str2);
    str_assign(&str2, "Benjamin ");
    str_add(&str2, "Bergstrom");
    assert(strcmp(str2.buffer, "Benjamin Bergstrom") == 0);
    // str_destroy(&str2);

    string str3;
    str_init(&str3);
    str_add(&str3, "Hello");
    assert(strcmp(str3.buffer, "Hello") == 0);
    // str_destroy(&str3);

    string str4;
    str_init(&str4);
    str_add(&str4, "a");
    str_add(&str4, "b");
    str_add(&str4, "c");
    assert(strcmp(str4.buffer, "abc") == 0);
    // str_destroy(&str4);

    string str5;
    str_init(&str5);
    str_add(&str5, "Gravity Falls ");
    str_add(&str5, "is an American mystery-comedy animated television series created by ");
    str_add(&str5, "Alex Hirsch for Disney Channel and Disney XD");
    str_add(&str5, "?!!!>>::");
    char *aux = "Gravity Falls is an American mystery-comedy animated television series created by Alex Hirsch for Disney Channel and Disney XD?!!!>>::";
    assert(strcmp(str5.buffer, aux) == 0);
    // str_destroy(&str5);

    string long_text;
    str_init(&long_text);
    const char *filename = "long_text.txt";

    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        fprintf(stderr, "File not found\n");
        exit(EXIT_FAILURE);
    }

    fseek(fp, 0, SEEK_END);
    long filesize = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    char *everything = (char *) malloc(filesize);
    fread(everything, 1, filesize, fp);

    rewind(fp);
    char *buffer = (char *) malloc(filesize);
    while (fgets(buffer, filesize, fp)) {
        str_add(&long_text, buffer);
    }

    printf("%d\n", strcmp(long_text.buffer, everything));
    // assert(strcmp(long_text.buffer, everything) == 0);
    // fclose(fp);

    puts("✔️ Add to string");
}

void get_string() {
    string name;
    str_init(&name);
    str_assign(&name, "Benjamin Bergstrom");
    char *my_name = str_get(&name);
    assert(my_name == "Benjamin Bergstrom");

    string long_text;
    str_init(&long_text);
    
    FILE *fp = fopen("long_text.txt", "r");
    if (fp == NULL) {
        fprintf(stderr, "File not found\n");
        exit(EXIT_FAILURE);
    }

    fseek(fp, 0, SEEK_END);
    long filesize = ftell(fp);

    rewind(fp);
    char *buffer = (char *) malloc(filesize);
    fread(buffer, 1, filesize, fp);
    str_assign(&long_text, buffer);

    char *aux = str_get(&long_text);
    assert(strcmp(long_text.buffer, aux) == 0);

    // fclose(fp);

    puts("✔️ Get string");
}

void cyclic_clock_indices() {
    cyclic_array clock;
    c_arr_init(&clock, "123456789abc");
    assert(c_arr_index(&clock, 'a') == 10);
    assert(c_arr_index(&clock, 'c') == 12);
    assert(c_arr_index(&clock, '1') != 0);
    assert(c_arr_index(&clock, '1') != 12);

    for (int i = 0; i < 1; i++) {
        const char item = clock.buffer[i];
        assert(item - 48 == i + 1);
    }

    // c_arr_destroy(&clock);

    puts("✔️ Clock indexes");
}

void cyclic_clock_chars() {
    cyclic_array clock2;
    c_arr_init(&clock2, "123456789abc");
    assert(c_arr_char(&clock2, 2) == '2');
    assert(c_arr_char(&clock2, 12) == 'c');
    
    // c_arr_destroy(&clock2);

    puts("✔️ Clock chars");
}

void cyclic_clock_moving() {
    cyclic_array clock3;
    c_arr_init(&clock3, "123456789abc");

    assert(c_arr_move(&clock3, '1', 2) == '3');
    assert(c_arr_move(&clock3, 'c', 3) == '3');
    assert(c_arr_move(&clock3, 'c', 20) == '8');
    assert(c_arr_move(&clock3, 'c', 40) == '4');
    assert(c_arr_move(&clock3, 'c', 500) == '8');
    assert(c_arr_move(&clock3, 'c', -3) == '9');
    assert(c_arr_move(&clock3, '1', -9) == '4');
    assert(c_arr_move(&clock3, 'c', -500) == '4');

    // c_arr_destroy(&clock3);

    puts("✔️ Clock moving indexes");
}

void aiz26_cipher() {
    cyclic_array letters;
    c_arr_init(&letters, "ABCDEFGHIJKLMNOPQRSTUVWXYZ");

    string str;
    str_init(&str);
    str_assign(&str, "ba");
    char *cipher = at_bash_cipher(&str, &letters);

    printf("cipher: %c\n", *cipher);
    // assert(strcmp(cipher, "2") == 0);

    // string jibberish;
    // str_init(&jibberish, 1);
    // str_add(&jibberish, ",,,");

    // assert(strcmp(at_bash_cipher(&jibberish, &letters), ",,,") == 0);

    // string name;
    // str_init(&name, 1);
    // str_add(&name, "Benjamin");
    
    // assert(strcmp(at_bash_cipher(&name, &letters), "2-5-14-10-1-13-9-14") == 0);

    // string name2;
    // str_init(&name2, 1);
    // str_add(&name2, "BENJAMIN ");
    // assert(strcmp(at_bash_cipher(&name2, &letters), "2-5-14-10-1-13-9-14 ") == 0);

    // string name3;
    // str_init(&name3, 1);
    // str_add(&name2, "BENJAMIN a");
    // assert(strcmp(at_bash_cipher(&name3, &letters), "2-5-14-10-1-13-9-14 1") == 0);


    // string full_name;
    // str_init(&full_name, 1);
    // str_add(&full_name, "Benjamin Bergstrom");
    // assert(strcmp(at_bash_cipher(&full_name, &letters), "2-5-14-10-1-13-9-14 2-5-18-7-19-20-18-15-13") == 0);

    // string text;
    // str_init(&text, 1);
    // str_add(&name, "Gravity Falls is an American mystery-comedy animated television series created by Alex Hirsch for Disney Channel and Disney XD");
    // assert(strcmp(at_bash_cipher(&name, &letters), "7-18-1-22-9-20-25 6-1-12-12-19 9-19 1-14 1-13-5-18-9-3-1-14 13-25-19-20-5-18-25-3-15-13-5-4-25 1-14-9-13-1-20-5-4 20-5-12-5-22-9-19-9-15-14 19-5-18-9-5-19 3-18-5-1-20-5-4 2-25 1-12-5-24 8-9-18-19-3-8 6-15-18 4-9-19-14-5-25 3-8-1-14-14-5-12 1-14-4 4-9-19-14-5-25 24-4") == 0);

    puts("✔️ AIZ26 cipher");
}

void aiz26_decipher() {
    cyclic_array letters;
    c_arr_init(&letters, "ABCDEFGHIJKLMNOPQRSTUVWXYZ");

    string text;
    str_init(&text);
    str_assign(&text, "2-5-14-10-1-13-9-14");

    char *a = at_bash_decipher(&text, &letters);
    printf("%s\n", a);
}

void test_caeser_cipher() {
    cyclic_array letters;
    c_arr_init(&letters, "ABCDEFGHIJKLMNOPQRSTUVWXYZ");

    string name;
    str_init(&name);
    str_add(&name, "Benjamin Bergstrom");

    assert(strcmp(caesar_cipher(&name, &letters), "EHQMDPLQ EHUJVWURP") == 0);
    str_destroy(&name);

    string text;
    str_init(&text);
    str_add(&text, "Gravity Falls is an American mystery-comedy animated television series created by Alex Hirsch for Disney Channel and Disney XD.");

    assert(strcmp(caesar_cipher(&text, &letters), "JUDYLWB IDOOV LV DQ DPHULFDQ PBVWHUB-FRPHGB DQLPDWHG WHOHYLVLRQ VHULHV FUHDWHG EB DOHA KLUVFK IRU GLVQHB FKDQQHO DQG GLVQHB AG.") == 0);
    str_destroy(&text);

    puts("✔️ Ceaser cipher");
}

void test_caesar_decipher() {
    cyclic_array letters;
    c_arr_init(&letters, "ABCDEFGHIJKLMNOPQRSTUVWXYZ");

    string name;
    str_init(&name);
    str_add(&name, "Ehqmdplq Ehujvwurp");

    assert(strcmp(caesar_decipher(&name, &letters), "BENJAMIN BERGSTROM") == 0);

    string text;
    str_init(&text);
    str_add(&text, "Judylwb Idoov lv dq Dphulfdq pbvwhub-frphgb dqlpdwhg whohylvlrq vhulhv fuhdwhg eb Doha Kluvfk iru Glvqhb Fkdqqho dqg Glvqhb AG.");

    assert(strcmp(caesar_decipher(&text, &letters), "GRAVITY FALLS IS AN AMERICAN MYSTERY-COMEDY ANIMATED TELEVISION SERIES CREATED BY ALEX HIRSCH FOR DISNEY CHANNEL AND DISNEY XD.") == 0);

    puts("✔️ Ceaser decipher");
}

int main(int argc, char const *argv[]) {
    assign_to_string();
    add_to_string();
    get_string();
    cyclic_clock_indices();
    cyclic_clock_chars();
    cyclic_clock_moving();
    // aiz26_cipher();
    test_caeser_cipher();
    test_caesar_decipher();
    // aiz26_decipher();

    puts("All tests passed!");

    return EXIT_SUCCESS;
}
