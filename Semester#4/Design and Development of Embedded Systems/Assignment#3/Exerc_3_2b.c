/*
Date: 2017-02-08

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

void sort(int number, int tab[]);

int main(int argc, char **argv)
{
    int test[] = { 1,2,34,5,67,3,23,12,13,10};
    sort(10,test);

}

/*
*Sorting function
*/void sort(int number, int tab[])
{
    int tmp;
    int minIndex;
    for(int i=0; i<number; i++)
    {
        minIndex = i;
        // Search for the minimum number
        for(int j=i+1; j<number; j++)
        {
            if(tab[j]<tab[minIndex]) minIndex = j;
        }
        tmp = tab[i];
        tab[i] = tab[minIndex];
        tab[minIndex] = tmp;
    }

    for(int i=0; i<number-1; i++)
    {
        printf("%d, ",tab[i]);
    }
    printf("%d\n", tab[number-1]);
}
