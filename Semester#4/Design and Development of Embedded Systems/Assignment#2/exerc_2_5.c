/*
 
 File name: exerc_2_5.c (or cpp)
 
 Date: 2017-01-23
 
 Group Number:  #nr 4
 
 Members of students contributed:
 
 Rafael Antonino Sauleo
 
 Filip Isakovski
 
 Maria-Bianca Cindroi
 
 Demonstration code: [<Examen code> <xxxx>] PENDING
 
 You should develop a program that calculates some statistical values for an array of integers. Among
 other things, the program will plot a histogram for the frequency of the different input numbers in
 the array.
 To test it you need first to create an array of integers (table [MAX]) with MAX number of random
 numbers between 0 and MAXNUMBER. Then you should write a function that for each possible
 number between 0 – MAXNUMBER calculates how many times the number exists in the array. The
 result is then stored in a new array (frequency []).
 Finally, you write a function that given the array frequency [] draw a histogram as followed example:
 You should use the function and its function declaration below.
 Given an array table[]={ 1,2,12, 5,1,0,0,5,9,12, 0,2,3,0} thhe program will printout:
 0 xxxx
 1 xx
 2 xx
 3 x
 5 xx
 9 x
 12 xx
 Note: Numbers with frequency 0 in the array frequency[] is not printed out
 */

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <memory.h>

#define MAX 100
#define MAXNUMBER 20

void create_random( int tab[]) {
    srand(time(NULL)); //initialize the random number generator.
    for (int i = 0; i < MAX; i++){
        tab[i] = (rand() % (MAXNUMBER +1)); //it will reset the random generator when time changes. (numbers from 0 to MAXNUMBER)
    }
}

void count_frequency(int tab[], int freq[]){
    
    for(int i=0;i<MAX;i++){
        int count=1;
        for(int j=i+1;j<= MAX-1; j++){
            if(tab[i]==tab[j] && tab[i]!='\0'){
                count++;
                tab[j]='\0'; //0 and \0 is the same
            }
        }
        if(tab[i]!='\0'){
            freq[i] = count;
        }
    }
}



void bubbleSort(int tab[], int array_size) { //sorting method
    int temp;
    for(int i = 0; i < MAX; i++)
    {
        for(int j = 1; j < MAX-1; j++)
        {
            if(tab[j] < tab[i])
            {
                //swap them
                temp = tab[i];
                tab[i] = tab[j];
                tab[j] = temp;
            }
        }
    }
    
}


void draw_histogram(int freq[], int tab[]){
    char stringX[100];
    
    for(int i=0;i<MAX;i++){
        if(tab[i]!='\0'){
            int count = freq[i];
            memset(stringX, 0, sizeof(stringX)); //clean the string character before entering next digit.
            for(int i=0;i<count;i++){
                strcat(stringX, "X");
            }
            printf("%d is %s times.\n",tab[i],stringX);
            
            
        }
    }
}

int main(int argc, char **argv) {
    int table[MAX]; //fixed size of an array of integers with value MAX
    int frequency[MAX] = {0};
    create_random(table);
    
    for (int i = 0; i < MAX; i++){      //HERE RUN FUNCTION FOR FREQ
        printf("%d\n", table[i]);
    }
    
    printf("new \n");
    
    /*
     * FIRST WE SORT THE ARRAY
     */
    bubbleSort(table, MAX);
    for (int i = 0; i < MAX; i++){
        printf("%d\n", table[i]);
    }
    
    /*
     * We run the function to detect duplicates. If they are we count them. Here 0 is ignored
     */
    
    count_frequency(table, frequency);
    
    
    draw_histogram(frequency, table);
    
    
    
    return(0);
}
