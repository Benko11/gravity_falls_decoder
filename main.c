#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "crappy_string.h"
#include "cyclic_array.h"
#include "atbash.h"
#include "binary.h"
#include "caesar.h"
#include "vigenere.h"
#include "utils/strtouppercase.h"

#define MIN_OPTION '1'
#define MAX_OPTION '7'

void welcome(void);
void help(int error);
char menu(void);
void draw_bill_easter_egg(void);

int main(int argc, char const *argv[]) {
    if (argc == 2 && strcmp(argv[1], "help") == 0) {
        help(0);
        return EXIT_SUCCESS;
    }

    if (argc == 2 || argc > 4) {
        help(1);
        return EXIT_FAILURE;
    }

    cyclic_array out, *alphabet;
    alphabet = &out;
    char items[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    c_arr_init(alphabet, items);
    
    if (argc == 4) {
        char *type = (char *) argv[1];
        const size_t length = strlen(argv[2]);
        if (strcmp(type, "1") == 0 || strcmp(type, "vigc") == 0) {
            char *upper_key = strtouppercase((char *) argv[3]);
            char *text = (char *) argv[2];
            char *result = vigenere_cipher(text, alphabet, upper_key);
            printf("%s\n", result);
            c_arr_destroy(alphabet);
            return EXIT_SUCCESS;
        }

        if (strcmp(type, "2") == 0 || strcmp(type, "vigd") == 0) {
            char *upper_key = strtouppercase((char *) argv[3]);
            char *text = (char *) argv[2];
            char *result = vigenere_decipher(text, alphabet, upper_key);
            printf("%s\n", result);
            c_arr_destroy(alphabet);
            return EXIT_SUCCESS;
        }

        help(1);
        return EXIT_FAILURE;
    }

    if (argc == 3) {
        char *type = (char *) argv[1];
        const size_t length = strlen(argv[2]);

        if (strcmp(type, "3") == 0 || strcmp(type, "caec") == 0) {
            char *text = (char *) argv[2];
            char *result = caesar_cipher(text, alphabet);
            printf("%s\n", result);
            c_arr_destroy(alphabet);
            return EXIT_SUCCESS;
        }

        if (strcmp(type, "4") == 0 || strcmp(type, "caed") == 0) {
            char *text = (char *) argv[2];
            char *result = caesar_decipher(text, alphabet);
            printf("%s\n", result);
            c_arr_destroy(alphabet);
            return EXIT_SUCCESS;
        }

        if (strcmp(type, "5") == 0 || strcmp(type, "binc") == 0) {
            char *text = (char *) argv[2];
            char *result = binary_cipher(text);
            printf("%s\n", result);
            c_arr_destroy(alphabet);
            return EXIT_SUCCESS;
        }

        if (strcmp(type, "6") == 0 || strcmp(type, "bind") == 0) {
            char *text = (char *) argv[2];
            char *result = binary_decipher(text);
            printf("%s\n", result);
            c_arr_destroy(alphabet);
            return EXIT_SUCCESS;
        }

        if (strcmp(type, "7") == 0 || strcmp(type, "atbash") == 0) {
            char *text = (char *) argv[2];
            char *result = atbash_move(text, alphabet);
            printf("%s\n", result);
            c_arr_destroy(alphabet);
            return EXIT_SUCCESS;
        }

        help(1);
        return EXIT_FAILURE;
    }

    welcome();

    char selection;
    while (1) {
        if (selection == 10) continue;

        selection = menu();

        if (selection >= MIN_OPTION && selection <= MAX_OPTION) break;

        printf("\033[1;31m");
        puts("Incorrect option selected, please try again.");
        printf("\033[0m");
    }

    switch (selection) {
        case '1': {
            char text[512];
            memset(text, 0, 512);

            char key[512];
            memset(key, 0, 512);

            char *result = (char *) malloc(512 * sizeof(char));

            printf("Text: ");
            fscanf(stdin, " %s", text);

            printf("Key: ");
            fscanf(stdin, " %s", key);

            char *upper_key = strtouppercase(key);

            result = vigenere_cipher(text, alphabet, upper_key);

            puts("");

            printf("%s\n", result);

            free(result);
        }
            break;
        case '2': {
            

            char text[512];
            memset(text, 0, 512);

            char key[512];
            memset(key, 0, 512);

            char *result = (char *) malloc(512 * sizeof(char));

            printf("Text: ");
            fscanf(stdin, " %s", text);

            printf("Key: ");
            fscanf(stdin, " %s", key);

            char *upper_key = strtouppercase(key);

            result = vigenere_decipher(text, alphabet, upper_key);

            puts("");

            printf("%s\n", result);

            free(result);
        }
            break;
        case '3': {
            char text[512];
            memset(text, 0, 512);

            printf("Text: ");
            fscanf(stdin, " %s", text);

            char *result = (char *) malloc(512 * sizeof(char));
            result = caesar_cipher(text, alphabet);

            printf("%s\n", result);

            free(result);
        }
            break;
        case '4': {
            char text[512];
            memset(text, 0, 512);

            printf("Text: ");
            fscanf(stdin, " %s", text);

            char *result = (char *) malloc(512 * sizeof(char));
            result = caesar_cipher(text, alphabet);

            printf("%s\n", result);

            free(result);
        }
            break;
        case '5': {
            char text[512];
            memset(text, 0, 512);

            printf("Text: ");
            fscanf(stdin, " %s", text);

            char *upper_text = strtouppercase(text);
            if (strcmp(upper_text, "TRIANGULUM,ENTANGULUM,METEFORIS_DOMINUS_VENTIUM.METEFORIS_VENETISARIUM!") == 0){
                draw_bill_easter_egg();
            } else {
                char *result = (char *) malloc(512 * 8 * sizeof(char));
                result = binary_cipher(text);

                printf("%s\n", result);
                free(result);

            }
        }
            break;
        case '6': {
            char text[512];
            memset(text, 0, 512);

            printf("Text: ");
            fscanf(stdin, " %s", text);

            char *result = (char *) malloc(512 * 8 * sizeof(char));
            result = binary_decipher(text);

            printf("%s\n", result);

            free(result);
        }
            break;
        case '7': {
            char text[512];
            memset(text, 0, 512);

            printf("Text: ");
            fscanf(stdin, " %s", text);

            char *result = (char *) malloc(512 * sizeof(char));
            result = atbash_move(text, alphabet);

            printf("%s\n", result);

            free(result);
        }
            break;
        default:
            break;
    }

    c_arr_destroy(alphabet);
    
    return EXIT_SUCCESS;
}

void welcome(void) {
    printf("\033[1m");
    puts("Welcome to Gravity Falls decoder!");
    printf("\033[0m");
}

char menu(void) {
    char selection;
    puts("1) Vigenere (cipher)");
    puts("2) Vigenere (decipher)");
    puts("3) Caesar (cipher)");
    puts("4) Caesar (decipher)");
    puts("5) Binary (cipher)");
    puts("6) Binary (decipher)");
    puts("7) Atbash");
    printf("Select a cipher for your text: ");
    fscanf(stdin, " %c", &selection);
    
    return selection;
}

void help(int error) {
    fprintf(error == 1 ? stderr : stdout, "usage: ./main.out <cipher_type> <text> <key>\n");
    fprintf(error == 1 ? stderr : stdout, "<cipher_type> - numerical value of the cipher or its abbreviation\n");
    fprintf(error == 1 ? stderr : stdout, "<text> - desired user input without spaces\n");
    fprintf(error == 1 ? stderr : stdout, "<key> - (optional) hashing key for selected ciphers (Vigenere)\n\n");
    fprintf(error == 1 ? stderr : stdout, "Cipher types:\n");
    fprintf(error == 1 ? stderr : stdout, "Vigenere cipher: 1 | vigc\n");
    fprintf(error == 1 ? stderr : stdout, "Vigenere decipher: 2 | vigd\n");
    fprintf(error == 1 ? stderr : stdout, "Caesar cipher: 3 | caec\n");
    fprintf(error == 1 ? stderr : stdout, "Caesar decipher: 4 | caed\n");
    fprintf(error == 1 ? stderr : stdout, "Binary cipher: 5 | binc\n");
    fprintf(error == 1 ? stderr : stdout, "Binary decipher: 6 | bind\n");
    fprintf(error == 1 ? stderr : stdout, "Atbash: 7 | atbash\n\n");
    fprintf(error == 1 ? stderr : stdout, "usage: ./main.out - enters the CLI\n");
}

void draw_bill_easter_egg(void) {
    puts("\n");

puts("                                                                      hmddhhyyyhh:                                                                    ");
puts("                                                                      dMMMMMMMMMM/                                                                    ");
puts("                                                                      hMMMMMMMMMM/                                                                    ");
puts("                                                                      yMMMMMMMMMM-                                                                    ");
puts("                                                                      sMMMMMMMMMM.                                                                    ");
puts("                                                                      sMMMMMMMMMM                                                                     ");
puts("                                                                      +MMMMMMMMMN                                                                     ");
puts("                                                                      /MMMMMMMMMN                                                                     ");
puts("                                                                      -MMMMMMMMMm                                                                     ");
puts("                                                                      `MMMMMMMMMm                                                                     ");
puts("                                                                       NMMMMMMMMm                                                                     ");
puts("                                                                       dMMMMMMMMh                                                                     ");
puts("                                                                ///////dMMMMMMMMd+++++/.                                                              ");
puts("                                                               .MMMMMMMMMMMMMMMMMMMMMMM+                                                              ");
puts("                                                                .-:::::----------------`                                                              ");
    printf("\033[1;33m");                                                                                                       

puts("                                                                         `smm:                                                                        ");
puts("                                                                        `yMymN/                                                                       ");
puts("                                                                       .hNs-:mN/                                                                      ");
puts("                                                                      -dNo---/mN:                                                                     ");
puts("                                                                     :mN+-----/mN:                                                                    ");
puts("                                                                    /Nm/-------/mN+                                                                   ");
puts("                                                                   oMd:---------:dMs                                                                  ");
puts("                                                                  sMh-------------yMy`                                                                ");
puts("                                                                 yMy---------------sMd.                                                               ");
puts("                                                               `hMy-----------------+NN-                                                              ");
puts("                                                              `dMs------+------/-----/mN/                                                             ");
puts("                       -/                                    .dNo-/-----d------y-----/:mN+                                    +:                      ");
puts("                       dM:                                  .mN+--oo----d/----/s----oo-:dMo                                   NN                      ");
puts("                  `oo- +Mm:    :do                         -mN+----os+oydhyyysdy+/:s+---:hMs`                        .ho`    oMd  :h/                 ");
puts("                  `hMNhsdMNh+/oNN/                        :Nm/---+yhho/-...+-..-:+sho+:---yMy`                       `smds+/hMNosdNh-                 ");
puts("                   `:+shNMMMMmds-                        /Nm/-:ohy/.      .No      `-/ss+--yMh`                        .+yNMMMMmyo-`                  ");
puts("                  `yyyhdmmmMM:`                         +Nd:-+dy-         +Mm          .oy+-sMh.                          yMMNNmysyh`                 ");
puts("                  `/ooo/:.sMN`                         oMd:-sd:           oMM.           .ss-sNd.                         /MM::+oso:                  ");
puts("                          yMm                        `sMh--dm.            oMM-             +s-oNm-                        .MM.                        ");
puts("                          sMm                       `yMy---dy`            +MM:             -h--+Nm-                       .MM`                        ");
puts("                          +Mm                      `dMs-----hh.           +MM-            /m/---/NN:                      .MN                         ");
puts("                          :MN                     .mMo-------+do`         +MN`          -hd:-----:mM/                     /Mh                         ");
puts("                          `MM.                   -NN/----------+hy:`      -My        `/hd+--------:dM+                    hM+                         ");
puts("                           dMs                `-+Nm/-------------:shy+:.   /.    .:oyhs/------------dMo.                 :Mm`                         ");
puts("                           -NMh/-`````..-:+oymNNMm:----------------sy+sydhyyyyhhhysm+----------------hMNmhso/:--.`     .+NN-                          ");
puts("                            -yNMNNNNNNNNNNmdhsmMd:----------------y+----h+::::oo---:y/----------------hMmsyhdmNNNNmddmmNNy.                           ");
puts("                              .:+ooo++/:-..``sMh-----------------:+-----d-----:y-----/-----------------yMy```.-:/osyyys+.                             ");
puts("                                           `yMy-------------------------+------/------------------------yMh`                                          ");
puts("                                          .hNs-----------------------------------------------------------sNd.                                         ");
puts("                                         .dNs::::::/://://////////++/+//+++o++++++++++++++++++++++++o+++//yNm-                                        ");
puts("                                        -mN+-------o--------------sho/-----o-----:ohh---------------o------/mN/                                       ");
puts("                                       :Nm/--------s--------------sMMNds/:-o--:ohNMMN---------------o-------/mN+                                      ");
puts("                                      /Nm/:::::::::s:::--------:::yMMMMMMmhyydMMMMMMN///+//+++++++++y++///////mMo                                     ");
puts("                                     +Md/::::::::::::://///////h//yMMMMMNds+ohNMMMMMM:::o::::::::::::::::::::::hMy`                                   ");
puts("                                    sMh------------------------y--yMMds+-------/shNMM:-:o-----------------------sMh`                                  ");
puts("                                  `hMy-------------------------y--+o:--------------/o--/s------------------------oMd.                                 ");
puts("                                 .dMy::////////////////////////y///////////////////////+y////:::::::::::::::::::::sMm.                             ");   
puts("                                .mNo:::------------h:::::::::::::::::::::::o/::::::::::::::::://////o///////////:::oNm-                            ");   
puts("                               :mN+----------------h-----------------------//-----------------------+---------------+Nm:                        ");      
puts("                              oNN/-----------------y-----------------------//-----------------------o----------------+NN/                    ");         
puts("                            `sMMdyyyhhhhhhhhhhyyyyymyyyyyyyyyyyyyyyyhhhhhhhddhhhhhhhhhhhhyyyyyysssooho++++//////////++yMNo                ");            
puts("                            `sysoo+++++++++++++++++++oooooooomMMMy+++++///////////////hMMmooooossyyyhhhhdddddddddddddhhys+             ");               
puts("                                                            sMMMy`                    `dMM+               ``````````                ");                  
puts("                                                           :MMMd`                      .NMN-                                     ");                     
puts("                                                          `mMMN.                        /MMd`                                 ");                        
puts("                                                          yMMM/                          sMMo                              ");                           
puts("                                                         :MMMh                           `mMM-                          ");                              
puts("                                                         dMMM-                            /MMh                       ");                                 
puts("                                                        `MMMm                              mMM.                   ");                                    
puts("                                                        -MMMy         `+mm:                sMM+                ");                                       
puts("                                                        `NMMm        /mMMMy                +MMs             ");                                          
puts("                                                         +MMMy:...:omMMMMMh  -s+.          +MMs          ");                                             
puts("                                                          +mMMNNmNNNd/dMMMs  yMMNy-       .mMM/       ");                                                
puts("                                                           .:oyhhy+-` sMMM+  sMMMMNy:.``./dMMy`    ");                                                   
puts("                                                                      oMMM.  oMMMyyNMmddmMMmo`  ");                                                      
puts("                                                                      /MMh   /MMM+ .+yhddy/.");                                                         
puts("                                                                       +s.   -MMM/");                                                                    
puts("                                                                              mMN.");                                                                    
puts("                                                                              .+-");
printf("\033[1;34m");
puts("\nAs your eyes are glowing blue");
puts("You find you wish not to see the truth");
puts("The omnipotent being appears in front of your eyes");
puts("You are learning that he is most divinely wise\n\n");

printf("\033[1;31m");
puts("HA-HA-HA-HA-HA-HA-HA!");
puts("NAME'S BILL CIPHER! AND I TAKE IT YOU'RE SOME KIND OF VENTRILOQUIST DUMMY?");
puts("HA-HA!");
puts("I'M JUST KIDDING, I KNOW WHO YOU ARE!\n");
puts("WELL, WELL, WELL, WELL, WELL, WELL, WELL, WELL, WELL ... !");
puts("AREN'T YOU A SIGHT FOR SORE EYES?\n");
puts("HA-HA-HA-HA-HA-HA-HA!");
puts("PHYSICAL FORM DON'T MIND IF I DO!");
puts("FOR ONE TRILLION YEARS I'VE BEEN TRAPPED IN MY OWN DECAYING DIMENSION, WAITING FOR A NEW UNIVERSE TO CALL MY OWN!");
puts("NAME'S BILL! BUT YOU CAN CALL ME YOUR LORD AND MASTER FOR ALL ETERNITY!");
puts("THIS PARTY NEVER STOPS! TIME IS DEAD AND MEANING HAS NO MEANING! EXISTENCE IS UPSIDE DOWN AND I REIGN SUPREME!");
}