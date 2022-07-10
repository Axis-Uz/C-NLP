#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>

int lineCount(char *file_name)
{
    // Count the number of line in files.
    char temp;
    int num_of_line;
    FILE *file_pointer = fopen(file_name, "r");
    if (file_pointer == NULL)
    {
        printf("\n!!(analysis.c)<lineCount>--File is Missing.");
    }
    else
    {
        temp = fgetc(file_pointer);
        while (temp != EOF)
        {
            if (temp == '\n')
            {
                num_of_line += 1;
            }
            temp = fgetc(file_pointer);
        }
    }

    fclose(file_pointer);
    return num_of_line + 2;
}

void readFile(char *file_name, int end_line, char arr_words[][20])
{
    // Open the file and store the words in a array.
    char temp_str[20];
    FILE *file_pointer = fopen(file_name, "r");
    if (file_pointer == NULL)
    {
        printf("\n!!(analysis.c)<readFile>--File is Missing.");
    }
    else
    {
        for (int f = 0; f < end_line; f++)
        {
            fscanf(file_pointer, "%s", temp_str);
            strcpy(&arr_words[f][20], temp_str);
        }
    }
    fclose(file_pointer);
}

int compareArr(char arr[][20], int end_line, char input[][20], int total_words)
{
    // It compare second array with first array and return the number of same words in both array.
    int compare;
    int result = 0;
    for (int i = 0; i < total_words; i++)
    {
        for (int loop = 0; loop < end_line; loop++)
        {
            compare = strcmp(input[i], arr[loop]);
            if (compare == 0)
            {
                result += 1;
            }
        }
    }
    return result;
}

void semantics(char user_words[500][20], int num_of_words)
{
    // Semantics analysis of text, categorizing text according the topic.
    int result[5] = {0, 0, 0, 0, 0},
        unkown_words, exclusion[500];
    float unkown_percent, percent[5] = {0, 0, 0, 0, 0};

    int fun_line, comp_line, phy_line, bio_line, chem_line;
    fun_line = lineCount("fun.csv");
    comp_line = lineCount("comp.csv");
    phy_line = lineCount("phy.csv");
    bio_line = lineCount("bio.csv");
    chem_line = lineCount("chem.csv");
    char fun_words[fun_line][20], comp_words[comp_line][20],
        phy_words[phy_line][20], bio_words[bio_line][20], chem_words[chem_line][20];

    readFile("fun.csv", fun_line, fun_words);
    readFile("comp.csv", comp_line, comp_words);
    readFile("phy.csv", phy_line, phy_words);
    readFile("bio.csv", bio_line, bio_words);
    readFile("chem.csv", chem_line, chem_words);

    result[0] = compareArr(fun_words, fun_line, user_words, num_of_words);
    result[1] = compareArr(comp_words, comp_line, user_words, num_of_words);
    result[2] = compareArr(phy_words, phy_line, user_words, num_of_words);
    result[3] = compareArr(bio_words, bio_line, user_words, num_of_words);
    result[4] = compareArr(chem_words, chem_line, user_words, num_of_words);

    for (int i = 0; i < 5; i++)
    {
        percent[i] = result[i] * 100 / num_of_words;
    }

    unkown_words = num_of_words - (result[0] + result[1] + result[2] + result[3] + result[4]);
    unkown_percent = 100 - (percent[0] + percent[1] + percent[2] + percent[3] + percent[4]);

    printf("\n  Function    : %.2f%% (%d)", percent[0], result[0]);
    printf("\n  CS          : %.2f%% (%d)", percent[1], result[1]);
    printf("\n  Physics     : %.2f%% (%d)", percent[2], result[2]);
    printf("\n  Biology     : %.2f%% (%d)", percent[3], result[3]);
    printf("\n  Chemistry   : %.2f%% (%d)", percent[4], result[4]);
    printf("\n  Unknown     : %.2f%% (%d)", unkown_percent, unkown_words);
    printf("\n  Total Words : %d", num_of_words);

    printf("\n The sentence seems to be related to: ");
    if (percent[1] > percent[2] && percent[1] > percent[3] && percent[1] > percent[4])
    {
        printf("Computer Science.\n");
    }
    else if (percent[2] > percent[1] && percent[2] > percent[3] && percent[2] > percent[4])
    {
        printf("Physics.\n");
    }
    else if (percent[3] > percent[2] && percent[3] > percent[1] && percent[3] > percent[4])
    {
        printf("Biology.\n");
    }
    else if (percent[4] > percent[2] && percent[4] > percent[3] && percent[4] > percent[1])
    {
        printf("Chemistry.\n");
    }
    else if (percent[1] == percent[2] == percent[3] == percent[4])
    {
        printf("All topics.\n");
    }
    else
    {
        printf("UNKOWN.\n");
        printf("Sorry.. can't figure it out.\nPlease try something else.");
    }
}

void sentiment(char user_words[500][20], int num_of_words)
{
}