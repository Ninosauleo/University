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
#include <unistd.h>
#include <math.h>
#include <ctype.h>
#define MAX 11

/*
 * This method will just read the input and fill the personal number. If the input is not valid it exits.
 */
void readPersnr(char *person){
    fgets(person, MAX, stdin);
}

/*
 * This method is used to count the number of digits in an array
 */
int countDigits(const char* person){
    int count = 0;
    for (int i = 0; i < strlen(person); i ++) { //This method checks the day of the personal number
        count++;
        printf("count %d\n", count);
    }
    return count;
}


/*
 * Algorith to check someone's birthday
 */
long controlDigit(const char* person) { //algorithm MAYBE DECLARE IT AS INT
    int sum = 0;
    int temp = (person[0]-'0') * 2;
    int tempSum = temp / 10 + temp % 10;
    
    tempSum += (person[1]-'0');
    
    temp = (person[2]-'0') * 2;
    tempSum += temp / 10 + temp % 10;
    tempSum += (person[3]-'0');
    
    temp = (person[4]-'0') * 2;
    tempSum += temp / 10 + temp % 10;
    tempSum += (person[5]-'0');
    
    temp = (person[6]-'0') * 2;
    tempSum += temp / 10 + temp % 10;
    tempSum += (person[7]-'0');
    
    temp = (person[8]-'0') * 2;
    tempSum += temp / 10 + temp % 10;
    
    sum = 10 - (tempSum % 10);
    return sum;
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
    
    if(day>0 && day <32){
        return day;
    }
    printf("the day you entered is not valid\n");
    return 0;
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
    
    if(month>0 && month <13){
        return month;
    }
    printf("the month you entered is not valid\n");
    return 0;
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
    int year = atoi(yearChar);
    if(year>=0 && year <100){
        return year;
    }
    printf("the year you entered is not valid\n");
    return 0;
}

int main() {
    char person[MAX];
    char *pointer = person;
    int personal_number;
    int day;
    int month;
    int year;
    
    do {
        printf("Introduce a personal number!\n");
        readPersnr(pointer);
        
        personal_number = controlDigit(pointer);//check this algorithm
        printf("control %ld\n", personal_number); //this returns 6?
        printf("last digit %c\n", person[9]);
        
        if(personal_number == (person[9] - '0')) {
            year = takeYear(pointer);
            printf("The year of your birthday is: %d\n", year);
            
            month = takeMonth(pointer);
            printf("The month of your birthday is: %d\n", month);
            
            day = takeDay(pointer);
            printf("The day of your birthday is: %d\n", day);
        }
        
        fseek(stdin,0,SEEK_END); //we need to flush the input of before.
        
    } while(person[0] != 'q');
    
    
    return 0;
}
