/*
File name: exerc_2_7.c

 Date: 2017-01-25

 Group Number:  #nr 4

 Members of students contributed:

 Rafael Antonino Sauleo

 Filip Isakovski

 Maria-Bianca Cindroi

 Demonstration code: [<Examen code> <xxxx>] PENDING

 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define MAX 9

/*
 * This method will just read the input and fill the personal number. If the input is not valid it exits.
 */
void readPersnr(char *person){
    fgets(person, MAX, stdin);
    if(person[0] == 'q'){
        exit(0);
    } else if (strlen(person) != MAX-1 || atol(person) == NULL) {
        fseek(stdin,0,SEEK_END); //we need to flush the input
        printf("Input not valid!\n");
        exit(0);
    }
}

/*
 * Algorith to check someone's birthday
 */
long controlDigit(const char* person) { //algorithm MAYBE DECLARE IT AS INT
    long controlD = 10 -(atol(person) %10); //atol() takes a bigger number.
    return controlD;
}

/*
*Method used to take the introduced month
*/
int takeDay(char *person) {
    char dayChar[1];
    int i;
    int j =0; //j is used for the index of the temporary array
    for (i = 4; i < 6; i ++) { //This method checks the day of the personal number
        dayChar[j] = person[i];
        j++;
    }

    int day = atoi(dayChar);
    return day;
}


/*
*Method used to take the introduced month
*/
int takeMonth(char *person) {
    char monthChar[1];
    int i;
    int j =0; //j is used for the index of the temporary array
    for (i = 2; i < 4; i ++) { //This method checks the month of the personal number
        monthChar[j] = person[i];
        j++;
    }

    int month = atoi(monthChar);
    return month;
}
/*
 * Method used to take the introduced year
 */
int takeYear(char *person) {
    char yearChar[1];
    int i;
    int j =0; //j is used for the index of the temporary array
    for (i = 0; i < 2; i ++) { //This method checks the year of the personal number
        yearChar[j] = person[i];
        j++;
    }

    int month = atoi(yearChar);
    return month;
}

int main() {
    char person[MAX];
    char exit[1];
    char *pointer = person;
    long personal_number;
    int day;
    int month;
    int year;

    do {
        printf("Introduce a personal number!\n");
        readPersnr(pointer);
        exit[0] = person[0];

        year = takeYear(pointer);
        printf("The year of your birthday is: %d\n", year);

        month = takeMonth(pointer);
        printf("The month of your birthday is: %d\n", month);

        day = takeDay(pointer);
        printf("The day of your birthday is: %d\n", day);

        personal_number = controlDigit(person);//check this algorithm
        printf("%ld\n", personal_number); //this returns 6?
        fseek(stdin,0,SEEK_END); //we need to flush the input of before.

    } while(exit[0] != 'q');


    return 0;
}
