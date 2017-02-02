/*
File name: exerc_2_1b.c

 Date: 2017-01-24

 Group Number:  #nr 4

 Members of students contributed:

 Rafael Antonino Sauleo

 Filip Isakovski

 Maria-Bianca Cindroi

 Demonstration code: [<Examen code> <10503>]

 */#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX 20
void copyString(char* text, char* textCopied);

int main(void){
	char c, text[MAX], copiedText[100];
	int n= MAX;

	fflush(stdin);
	printf("Enter something:");
	fgets(text, MAX, stdin);

	copyString(text, copiedText);

	printf("Text to be copied: %s\n", text);
	printf("Final copied string: %s\n",copiedText);

	return 0;
}

void copyString(char* text, char* copiedText){

	int check=0;
	while(check<=MAX){
		copiedText[check]=text[check];
		check++;
	}

	return;
}
