/*File to start the program*/
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "analysis.c"
extern void semantics(char input_words[500][20], int num_of_words);
extern void sentiment(char input_words[500][20], int num_of_words);

void remove_symbols(char arr[])
{
	// Use to replace symbols with a space from the arrays of char.

	for (int i = 0; i < strlen(arr); i++)
	{
		// TODO Clean this if-else block
		if ((0 <= arr[i] && arr[i] <= 47) || (58 <= arr[i] && arr[i] <= 64))
		{
			arr[i] = ' ';
		}
		else if (
			(91 <= arr[i] && arr[i] <= 96) ||
			(123 <= arr[i] && arr[i] <= 127))
		{
			arr[i] = ' ';
		}
		else if (arr[i] == '|')
		{
			// Can't remove "|" as we are using as stop symbol.
			break;
		}
	}
}

int get_words(char arr[][20])
{
	char words[500][20]; //['word','hello']
	int num_of_words = 0;

	printf(
		"\n!! Try to use punctuation only at the end of the word and put the "
		"space after them.\n");
	printf("\n!! Enter words(to stop use 'space+|'): \n");
	fflush(stdin);

	for (int i = 0; i < 500; i++)
	{
		char letters[20]; // ['w','o','r','d']
		scanf("%s", letters);
		// If current inputted word is '|' then stop reading
		if (*letters == '|')
		{
			break;
		}
		remove_symbols(letters);
		strcpy(words[i], letters);
		for (int j = 0; j <= 10; j++)
		{
			//? Why is "j<=10" ?
			words[i][j] = tolower(words[i][j]);
		}
		// TODO Can't I directly copy into the passed array.
		strcpy(arr[i], words[i]);
		num_of_words += 1;
	}
	return num_of_words;
}

int main(void)
{
	char user_words[500][20];
	int total_words, index, never = 0;

	printf("\n\t<< Welcome >>");
	printf("\n\t<< Semantic and Sentiment Analysis of Text >>");

	while (never == 0)
	{
		printf("\nAnalysis on:\n->1.Semantics\n->2.Sentiment\n->3.Quit");
		printf("\nInput index number ->");
		scanf("%d", &index);
		sleep(1);
		switch (index)
		{
		case 1:

			printf("\nCurrently semantics analysis is only limited for\n "
				   "--Computer Science, Physics, Biology, and Chemistry\n");
			total_words = get_words(user_words);
			semantics(user_words, total_words);
			break;

		case 2:
			printf("\nCurrently sentiment analysis is only limited to "
				   "Positivity and Negativity.\n");
			total_words = get_words(user_words);
			sentiment(user_words, total_words);
			break;

		case 3:
			printf("!! Exiting...\n");
			never = 1;
			break;

		default:
			printf("\t<<main-switch-default>>");
			break;
		}
	}
	exit(0);
}