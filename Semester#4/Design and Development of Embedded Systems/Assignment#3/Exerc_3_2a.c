/*

 File name: exerc_3_2a.c (or cpp)

 Date: 2017-02-04

 Group Number:  #nr 4

 Members of students contributed:

 Rafael Antonino Sauleo

 Filip Isakovski

 Maria-Bianca Cindroi

 Demonstration code: [<Examen code> <20296>]


b) There are a lot of ways to sort a field. For example, bubble sort which not is the fastest but easy to
understand and implement. Write a sorting routine that uses the following algorithm to sort an array
of integers.
• Find the minimum value in the list.
• Swap the minimum with the first in list.
• Repeat this but exclude the previous minimum on top of the list and search only in the rest of the
list.
Implement the sorting function using the function declaration:
void sort (int number, int tab []);
Test the function by use of a main program and an initiated array as above. For checking purpose
print out the sorted array.

 */

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <memory.h>

#define MAX 100
#define MAXNUMBER 20



int table[MAX]; //fixed size of an array of integers with value MAX


void create_random( int tab[]) {
    srand(time(NULL)); //initialize the random number generator.
    for (int i = 0; i < MAX; i++){
        tab[i] = (rand() % 100); //it will reset the random generator when time changes.
    }
}

int searchstring(int number, int tab[], int size) {
    int count = 0;
    for(int i = 0; i < size; i++){
        if(number == tab[i]){
            printf("Found at index: %d\n", count); //if you want count + 1 also works :)
            return count;
        }
        count++;
    }
    return -1;
}

void bubbleSort(int tab[], int array_size) { //sorting method
    int temp;
    for(int i = 0; i < array_size; i++) {
        for(int j = 1; j < array_size-1; j++) {
            if(tab[j] > tab[i]) {
                //swap them
                temp = tab[i];
                tab[i] = tab[j];
                tab[j] = temp;
            }
        }
    }

}

char readInput(char *pointer){
    fgets(pointer, MAX, stdin);
    fseek(stdin,0,SEEK_END); //we need to flush the buffer
    fflush(stdin);
}

int main(int argc, char **argv) {

    int number;
    int index;

    create_random(table);

    for (int i = 0; i < MAX; i++){      //HERE print the array
        printf("%d\n", table[i]);
    }


    printf("ENTER A NUMBER YOU WANT TO FIND IN THE ARRAY \n");
    char userInput[MAX];
    char *userPointer = userInput;
    readInput(userPointer);
    number =atoi(userInput);
    printf("number is %d\n", number);
    index = searchstring(number, table, MAX);
    printf("Index is %d\n", index);

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



    return(0);
}
