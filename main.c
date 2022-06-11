#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>
#include "analysis.c"

extern void semantics(char user_words[500][20], int num_of_words);
extern void sentiment(char user_words[500][20], int num_of_words);

void print_array(char arr[][20], int end)
{
	// Print array which contains user words
	for (int i = 0; i < end; i++)
	{
		printf("|%s|\n", arr[i]);
	}
}

void remove_symbols(char arr[])
{
	// Replace symbols with spaces in the given array.
	for (int i = 0; i < strlen(arr); i++)
	{
		if ((0 <= arr[i] && arr[i] <= 47) || (58 <= arr[i] && arr[i] <= 64))
		{
			arr[i] = ' ';
		}
		else if ((91 <= arr[i] && arr[i] <= 96) || (123 <= arr[i] && arr[i] <= 127))
		{
			arr[i] = ' ';
		}
		else if (arr[i] == '|')
		{
			break;
		}
	}
}

int get_words(char arr[][20])
{
	// Get words from stdin, lowers them and then places them in the array and returns the total number of words inputted.
	char words[500][20]; //['someone','nowhere']
	int num_of_words = 0;
	printf("Enter words(to stop 'space+|'):\n  >");
	fflush(stdin);
	for (int i = 0; i < 500; i++)
	{
		char letters[20];
		scanf("%s", letters);
		if (*letters == '|')
		{
			break;
		}

		remove_symbols(letters);
		strcpy(words[i], letters);
		for (int j = 0; j <= strlen(letters); j++)
		{
			words[i][j] = tolower(words[i][j]);
		}
		strcpy(arr[i], words[i]);
		num_of_words += 1;
	}
	return num_of_words;
}

int main(void)
{
	char user_words[500][20];
	int total_words = 0;
	semantics(user_words, total_words);
	// total_words = get_words(user_words);
	// print_array(user_words, total_words);
}