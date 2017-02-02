/*
File name: exerc_2_4.c (or cpp)
 
 Date: 2017-01-24
 
 Group Number:  #nr 4
 
 Members of students contributed:
 
 Rafael Antonino Sauleo
 
 Filip Isakovski
 
 Maria-Bianca Cindroi
 
 Demonstration code: [<Examen code> <10688>]
 
 */
#include <stdio.h>
#include <string.h>

void reverse_string(char *str);
void palindrome(char *str, char *strr);

int main(void)
{
	char string[100], stringReversed[100];
	printf("Insert a string: ");
	scanf("%s", string);
	
	strcpy(stringReversed, string);
	reverse_string(stringReversed);

	palindrome(string,stringReversed);
	return 0;
}

//return the reversed version of the inputed string (stackOverflow)
void reverse_string(char *str)
	{
	char *start=str;
	char *end=start + strlen(str) -1;		
	char temp;
	//null string
	if (str == 0){
		return;	
	}
	
	//empty string
	if (*str == 0)
	{
		return;	
	}
	
	//considering that it reverses only from the middle of the word
	//as long as there is more left from the back of it than from 
    //the beginning of the word, move the end of the word
	while (end>start)
	{
		temp = *start;
		*start = *end;
		*end = temp;

		++start;
		--end;
	}
}

//compare the string and its reversed, and output if it is a palindrome or not
void palindrome(char *str, char *strr)
{
	//
	if (strcmp(str, strr) == 0)
	{
		printf("The word is a palindrome.\n");
	}
	else
	{
		printf("The word is not a palindrome.\n");	
	}
}
