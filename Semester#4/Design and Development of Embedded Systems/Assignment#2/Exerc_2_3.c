/*

 File name: exerc_2_3.c (or cpp)

 Date: 2017-01-24

 Group Number:  #nr 4

 Members of students contributed:

 Rafael Antonino Sauleo

 Filip Isakovski

 Maria-Bianca Cindroi

 Demonstration code: [<Examen code> <10550>]

 */

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

int main(int argc, char *argv[]) {

	char *string1 = argv[1];
	char *string2 = argv[2];
	int res=0, i=0, trigger=0;

	printf("String 1: %s\n", string1);

	printf("String 2: %s\n", string2);

	int str1length = 0;
	int str2length = 0;

	//Getting the lengths of the strings
	str1length = strlen(string1);
	str2length = strlen(string2);

	//Checking it our way
	if(str1length > str2length)
	{
		printf("Our result: The strings are different!\n");
	}
	else if(str1length < str2length)
	{
		printf("Our result: The strings are different!\n");
	}
	else
	{
		while(string1[i] != '\0')
		{
			if((string1[i] != string2[i]) && trigger == 0){
				trigger = 1;
			}
			i++;
		}

		if(trigger == 1)
		{
			printf("Our result: The strings are different!\n");
		}
		else
		{
			printf("Our result: The strings are identical!\n");
		}
	}

	//Checking with strcmp()
	res = strcmp(string1, string2);

	//Using result from strcmp()
	if(res == 0)
	{
		printf("strcmp result: The strings are identical!\n");
	}
	else
	{
		printf("strcmp result: The strings are different!\n");
	}



	return 0;
}
