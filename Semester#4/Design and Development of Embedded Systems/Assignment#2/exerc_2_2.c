
/*
 
 File name: exerc_x_y.c (or cpp)
 
 Date: 2017-01-23
 
 Group Number:  #nr 4
 
 Members of students contributed:
 
 Rafael Antonino Sauleo
 
 Filip Isakovski
 
 Maria-Bianca Cindroi
 
 Demonstration code: [<Examen code> <xxxx>] PENDING
 
 
 Create an array of integers, array[MAX], and fill it with MAX no of random numbers. Let then the
 program print out the following:
 The value of the label array (address) is: xxxxxxxxxx
 First integer in the array is (array[0]) : xxxxxxxxxx
 The size of an integer (number of bytes) is : xxxxxxxxx
 The size of the whole array is : xxxxxxxxx
 End the program by printing out the array, then double all values in the array by use of a pointer and
 print it out again.
 */


#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define MAX 10 //define the size of the array


int main(int argc, char **argv) {
    int array[MAX]; //fixed size of an array of integers with value MAX
    srand(time(NULL)); //initialize the random number generator.
    int *labelPtr; //assign pointers this case is an int pointer (*'s).
    labelPtr = &array; // store address of var in pointer variable
    int i;
    for (i = 0; i < MAX; i++){
        array[i] = (rand() % 101); //it will reset the random generator when time changes. (numbers from 0 to 100)
    }
    printf("The value of the label array (address) is: %x %x\n", labelPtr, &array); //allocate memory address
    printf("First integer in the array is: %d\n", array[0]);
    printf("The size of an integer (number of bytes) is: %ld \n", sizeof(array[0])); //FIX
    printf("The size of the whole array is : %d\n", MAX);
    printf("The size of the whole array is :");

    for (i = 0; i < MAX; i++){
        printf("%d ", array[i]);
    }

    printf("\nThe size of the whole double array is :");
    for (i = 0; i < MAX; i++){
        array[i] = *(labelPtr + i) * 2;
        printf("%d ", array[i]);
    }
    return(0);
}
