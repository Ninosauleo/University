#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>


/*
 *
 *
 * Pack and unpack variables into a byte. You need to store 4 different values in a byte. The values are:
Name Range Bits Info
engine_on 0..1 1 Is engine on or off
gear_pos 0..4 3 What gear position do we have
key_pos 0..2 2 What position is the key in
brake1 0..1 1 Are we breaking (told by sensor 1)
brake2 0..1 1 Are we breaking (told by sensor 2) = bit nr 0
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
        printf("Hello World! argc=%d arg %d is %s\n", argc, j, argv[j]);
    }

    printf("%d\n", argc);
//(person[4]-'0')

    if(argc != 6 || isdigit((*argv[1] - '0')) || isdigit((*argv[2] - '0')) || isdigit((*argv[3] - '0'))
       || isdigit((*argv[4] - '0')) || isdigit((*argv[5] - '0'))) {

        printf("error");
        exit(2);

    } else {
        s.engine_on = (unsigned char) (*argv[1] - '0');
        s.gear_pos = (unsigned char) (*argv[2] - '0');
        s.key_pos = (unsigned char) (*argv[3] - '0');
        s.brake1 = (unsigned char) (*argv[4] - '0');
        s.brake2 = (unsigned char) (*argv[5] - '0');

        unsigned int i = 0;

        i |= s.brake2; //same as i = i |(brake1 << 1)
        i |= (s.brake1 << 1); //same as i = i |(brake1 << 1)
        i |= (s.key_pos << 2);
        i |= (s.gear_pos << 4);
        i |= (s.engine_on << 7);

        printf("Sizeof i : %d\n", sizeof(i));
        printf(" i : %d\n", i); //1 010 10 11
        printf(" i : \"%02x\"\n", i);
    }

    return 0;
}