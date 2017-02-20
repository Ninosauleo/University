#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>


/*

 File name: exerc_4_2a.c (or cpp)

 Date: 2017-02-20

 Group Number:  #nr 4

 Members of students contributed:

 Rafael Antonino Sauleo

 Filip Isakovski

 Maria-Bianca Cindroi

 Demonstration code: [<Examen code> <PENDING>]
 */


struct s1 {
    unsigned char engine_on : 1;
    unsigned char gear_pos : 3;
    unsigned char key_pos : 2;
    unsigned char brake1 : 1;
    unsigned char brake2 : 1;
} s;


int main(int argc, char **argv ) {

    for (int j = 0; j < argc; j++) {
        printf("Decode argc=%d arg %d is %s\n", argc, j, argv[j]);
    }

    if(argc > 2 || (strlen(argv[1])>2)){
        printf("Error");
        exit(2);
    }

    printf("Binary form is : ");

    unsigned int k = 0;
    switch(*(argv[1] + 0)){
        case '0': k|= (0<<4); printf("0000"); break; //int 0
        case '1': k|= (1<<4); printf("0001"); break; //int 1
        case '2': k|= (2<<4); printf("0010"); break; //int 2
        case '3': k|= (3<<4); printf("0011"); break; //int 3
        case '4': k|= (4<<4); printf("0100"); break; //int 4
        case '5': k|= (5<<4); printf("0101"); break; //int 5
        case '6': k|= (6<<4); printf("0110"); break; //int 6
        case '7': k|= (7<<4); printf("0111"); break; //int 7
        case '8': k|= (8<<4); printf("1000"); break; //int 8
        case '9': k|= (9<<4); printf("1001"); break; //int 9
        case 'A': k|= (10<<4); printf("1010"); break; //int 10
        case 'B': k|= (11<<4); printf("1011"); break; //int 11
        case 'C': k|= (12<<4); printf("1100"); break; //int 12
        case 'D': k|= (13<<4); printf("1101"); break; //int 13
        case 'E': k|= (14<<4); printf("1110"); break; //int 14
        case 'F': k|= (15<<4); printf("1111"); break; //int 15
        case 'a': k|= (10<<4); printf("1010"); break; //int 10
        case 'b': k|= (11<<4); printf("1011"); break; //int 11
        case 'c': k|= (12<<4); printf("1100"); break; //int 12
        case 'd': k|= (13<<4); printf("1101"); break; //int 13
        case 'e': k|= (14<<4); printf("1110"); break; //int 14
        case 'f': k|= (15<<4); printf("1111"); break; //int 15
        default:  printf("\nInvalid hexadecimal digit %s \n",argv[1]); exit(2);
    }


    switch(*(argv[1] + 1)){
        case '0': k|= (0<<0); printf("0000"); break; //int 0
        case '1': k|= (1<<0); printf("0001"); break; //int 1
        case '2': k|= (2<<0); printf("0010"); break; //int 2
        case '3': k|= (3<<0); printf("0011"); break; //int 3
        case '4': k|= (4<<0); printf("0100"); break; //int 4
        case '5': k|= (5<<0); printf("0101"); break; //int 5
        case '6': k|= (6<<0); printf("0110"); break; //int 6
        case '7': k|= (7<<0); printf("0111"); break; //int 7
        case '8': k|= (8<<0); printf("1000"); break; //int 8
        case '9': k|= (9<<0); printf("1001"); break; //int 9
        case 'A': k|= (10<<0); printf("1010"); break; //int 10
        case 'B': k|= (11<<0); printf("1011"); break; //int 11
        case 'C': k|= (12<<0); printf("1100"); break; //int 12
        case 'D': k|= (13<<0); printf("1101"); break; //int 13
        case 'E': k|= (14<<0); printf("1110"); break; //int 14
        case 'F': k|= (15<<0); printf("1111"); break; //int 15
        case 'a': k|= (10<<0); printf("1010"); break; //int 10
        case 'b': k|= (11<<0); printf("1011"); break; //int 11
        case 'c': k|= (12<<0); printf("1100"); break; //int 12
        case 'd': k|= (13<<0); printf("1101"); break; //int 13
        case 'e': k|= (14<<0); printf("1110"); break; //int 14
        case 'f': k|= (15<<0); printf("1111"); break; //int 15
        default:  printf("\nInvalid hexadecimal digit %s \n",argv[1]); exit(2);
    }

    printf("\nName   -----   Value \n");
    printf("---------------------");
    s.engine_on = k>>7;
    printf("\nengine_on is %d\n", s.engine_on);
    s.gear_pos = k>>4;
    printf("gear_pos is %d\n", s.gear_pos);
    s.key_pos = k>>2;
    printf("key_pos is %d\n", s.key_pos);
    s.brake1 = k>>1;
    printf("brake1 is %d\n", s.brake1);
    s.brake2 = k>>0;
    printf("brake2 is %d\n", s.brake2);


    return 0;
}