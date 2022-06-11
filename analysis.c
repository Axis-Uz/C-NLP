#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>

int lineCount(int index)
{
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
    printf("\nCounted lines for -> (%d)", index);

    /* +1 for last line i.e '\n' and another +1 for array size*/
    num_of_line += 2;

    return num_of_line;
}

void read_arr(char *file_name, int end_line, char arr_words[][20])
{
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

void semantics(char user_words[500][20], int num_of_words)
{

    char temp_str[20];
    int compare, loop;
    int cal[5] = {0, 0, 0, 0, 0};
    float percent[5] = {0, 0, 0, 0, 0};

    int fun_line, comp_line, phy_line, bio_line, chem_line;
    fun_line = lineCount(0);
    comp_line = lineCount(1);
    phy_line = lineCount(2);
    bio_line = lineCount(3);
    chem_line = lineCount(4);
    printf("\n%d-%d-%d-%d-%d", fun_line, comp_line, phy_line, bio_line, chem_line);

    char fun_words[fun_line][20], comp_words[comp_line][20], phy_words[phy_line][20], bio_words[bio_line][20], chem_words[chem_line][20];

    read_arr("fun.csv", fun_line, fun_words);
    printf("\n> Compiled Function Words");

    read_arr("comp.csv", comp_line, comp_words);
    printf("\n> Compiled Computer Words");

    read_arr("phy.csv", phy_line, phy_words);
    printf("\n> Compiled Physics Words");

    read_arr("bio.csv", bio_line, bio_words);
    printf("\n> Compiled Biology Words");

    read_arr("fun.csv", fun_line, fun_words);
    printf("\n> Compiled Chemistry Words");
}

void sentiment(char user_words[500][20], int num_of_words)
{
}