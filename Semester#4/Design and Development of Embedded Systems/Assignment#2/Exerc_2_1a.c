/*
File name: exerc_2_1a.c (or cpp)
 
 Date: 2017-01-24
 
 Group Number:  #nr 4
 
 Members of students contributed:
 
 Rafael Antonino Sauleo
 
 Filip Isakovski
 
 Maria-Bianca Cindroi
 
 Demonstration code: [<Examen code> <10503>]
 
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX 20

int main(void){
	char c, text[MAX], copiedText[100];
	int n= MAX;
	
	fflush(stdin);
	printf("Enter something:");
	fgets(text, MAX, stdin);

	/*
	while(((c=getchar())!='\n') && n==0){
		text[n]=c;
		n--;
	}
	 */

	strcpy(copiedText, text);
	printf("Text to be copied: %s\n", text);
	printf("Final copied string: %s\n", copiedText);

	return(0);
}
