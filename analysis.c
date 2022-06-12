#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>

int lineCount(int index)
{
    // Count the number of lines in the file.
    char temp;
    FILE *file_pointer;
    int num_of_line = 0;
    switch (index)
    {
    case -2:
        file_pointer = fopen("negative.csv", "r");
        break;

    case -1:
        file_pointer = fopen("positive.csv", "r");
        break;

    case 0:
        file_pointer = fopen("fun.csv", "r");
        break;

    case 1:
        file_pointer = fopen("comp.csv", "r");
        break;

    case 2:
        file_pointer = fopen("phy.csv", "r");
        break;

    case 3:
        file_pointer = fopen("bio.csv", "r");
        break;

    case 4:
        file_pointer = fopen("chem.csv", "r");
        break;

    default:
        printf("\n!!(analysis.c)<lineCount>--Switch is Default(%d)", index);
        break;
    }

    if (file_pointer == NULL)
    {
        printf("\n!!(analysis.c)<lineCount>--File is Missing(%d)", index);
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

    /* +1 for last line i.e '\n' and another +1 for array size*/
    num_of_line += 2;

    return num_of_line;
}

void readFile(char *file_name, int end_line, char arr_words[][20])
{
    // Open the file and store the words in a array.
    char temp_str[20];
    FILE *file_pointer = fopen(file_name, "r");
    if (file_pointer == NULL)
    {
        printf("\n!!(analysis.c)<read_arr>--File is Missing.");
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

int compareArr(char arr[][20], int end_line, char input[][20], int total_words, int exclusion_list[])
{
    // It compare second array with first array and return the number of same words in both array.
    int compare;
    int result = 0;
    for (int i = 0; i < total_words; i++)
    {
        if (exclusion_list[i] == 1)
        {
            /* Excludes already compared words */
            // printf("\n%d\t%s--Excluded", i, input[i]);
            continue;
        }
        for (int loop = 0; loop < end_line; loop++)
        {
            compare = strcmp(input[i], arr[loop]);
            if (compare == 0)
            {
                result += 1;
                exclusion_list[i] = 1;
            }
        }
    }
    return result;
}

void semantics(char user_words[500][20], int num_of_words)
{

    int result[5] = {0, 0, 0, 0, 0},
        unkown_words, exclusion[500];
    float unkown_percent, percent[5] = {0, 0, 0, 0, 0};

    int fun_line, comp_line, phy_line, bio_line, chem_line;
    fun_line = lineCount(0);
    comp_line = lineCount(1);
    phy_line = lineCount(2);
    bio_line = lineCount(3);
    chem_line = lineCount(4);
    char fun_words[fun_line][20], comp_words[comp_line][20],
        phy_words[phy_line][20], bio_words[bio_line][20], chem_words[chem_line][20];

    readFile("fun.csv", fun_line, fun_words);
    readFile("comp.csv", comp_line, comp_words);
    readFile("phy.csv", phy_line, phy_words);
    readFile("bio.csv", bio_line, bio_words);
    readFile("chem.csv", chem_line, chem_words);

    result[0] = compareArr(fun_words, fun_line, user_words, num_of_words, exclusion);
    result[1] = compareArr(comp_words, comp_line, user_words, num_of_words, exclusion);
    result[2] = compareArr(phy_words, phy_line, user_words, num_of_words, exclusion);
    result[3] = compareArr(bio_words, bio_line, user_words, num_of_words, exclusion);
    result[4] = compareArr(chem_words, chem_line, user_words, num_of_words, exclusion);

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
    printf("\n  Total Words : %d",num_of_words);

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