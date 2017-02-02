/*
 
 File name: exerc_2_6.c (or cpp)
 
 Date: 2017-01-24
 
 Group Number:  #nr 4
 
 Members of students contributed:
 
 Rafael Antonino Sauleo
 
 Filip Isakovski
 
 Maria-Bianca Cindroi
 
 Demonstration code: [<Examen code> <10693>]
 
 */

#include <stdio.h>
#include <stdlib.h>

#define MAX 5

void initQue(int list[], int max)
{
	int i = 0;
	for (i=0; i < max; i++)
	{
		list[i] = -1;
	}
}

int input(int list[], int number, int max)
{
	int toggle = 0;

	int i = 0;
	for (i=0; i < max; i++)
	{
		if(list[i] == -1 && toggle == 0)
		{
			list[i] = number;
			toggle = 1;
		}
	}

	return toggle;
}

int output(int list[], int max)
{
	int res = 0;
	if(list[0] != -1)
	{
		res = list[0];

		int i = 0;
		for (i=0; i < max-1; i++)
		{
			list[i] = list[i+1];
		}
		list[max-1] = -1;

		return res;
	}
	return res;
}

int main(int argc, char *argv[]) {

	int list[MAX];
	int input_res, output_res;
	int num = 0;

	initQue(list, MAX);

	int i = 0;
	for (i=0; i < MAX; i++)
	{
		printf(" %d", list[i]);
	}

	int check = 0;
	for (int h = 0; h < MAX; h++)
	{
		printf("\n");
		printf("Enter a postive integer:\n");
		scanf("%d", &num);
		input_res = input(list, num, MAX);

		i = 0;
		for (i=0; i < MAX; i++)
		{
			printf(" %d", list[i]);
		}
		check++;
	}

	for (int h=0; h < check+1; h++)
	{
		output_res = output(list, MAX);
		if (output_res != 0){
			printf("\nRemove: %d\n", output_res);
		}
		else
			printf("\n");

		i = 0;
		for (i=0; i < MAX; i++)
		{
			printf(" %d", list[i]);
		}

	}

	return 0;
}
