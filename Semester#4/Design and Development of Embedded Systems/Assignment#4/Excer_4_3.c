/* *******************************
Program file : bit_manage_function.c
Peter Lundin / 2016-01-97
For test IO program function

******************************** */

/*

 File name: exerc_4_3a.c (or cpp)

 Date: 2017-02-20

 Group Number:  #nr 4

 Members of students contributed:

 Rafael Antonino Sauleo

 Filip Isakovski

 Maria-Bianca Cindroi

 Demonstration code: [<Examen code> <PENDING>]
 */

#include <time.h>
#include <stdio.h>
#include <stdlib.h>

void f_delay(int);
unsigned char random_inport( void);
void printport( int);

struct s1 {
    unsigned char fourthbit : 1;
} s;

int main(){
    int nr;
    unsigned char port;
    srand(time(0));
    unsigned int k = 0;
    port = 3;
    s.fourthbit = port>>3;
    printf("Inbit 4 is %d ", s.fourthbit);
    printport(port);
    for ( nr=1; nr < 10; nr++){
        port = random_inport();
        printport( port);
        f_delay(5);
    }
    return(0);
}


void f_delay( int tenth_sec){

    clock_t start_t, end_t;
    long int i;
    start_t = clock();
    do{
        for(i=0; i< 10000000; i++);
        end_t = clock();
    }while ((end_t - start_t) < (tenth_sec*CLOCKS_PER_SEC)/10);
    return;
}

unsigned char random_inport( void){
    unsigned int inport = 0;
    unsigned int k = 0;
    inport=  rand() % 256;
    s.fourthbit = inport>> 3;
    printf("Inbit 4 is %d ", s.fourthbit);
    //printf("before inport %d ", inport);
    if(s.fourthbit == 1){
        k = inport<<1;
        //printf("after inport% d \n", k);
        return (k);
    }

    return (inport);
}

void printport( int portvalue){
    int binchar[8], rest,j, i=0;
    rest = portvalue;
    while(rest!=0){
        binchar[i++]= rest % 2;
        rest = rest / 2;
    }
    // Fill to 8 bits
    while( i<8){
        binchar[i++]=0;
    }
    // Print bits and at the end corresponding decimal value
    for(j =i-1 ;j > -1;j--)
        printf("  %d",binchar[j]);
    printf(" --------Porten value = %d  \n", portvalue);
    return ;
}


