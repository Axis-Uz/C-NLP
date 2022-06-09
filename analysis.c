#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>

int lineCount(int index)
{
    // To count the lines in the text file to create proper sized word arrays.
    char temp_char;
    FILE *file_pointer = NULL;
    int num_of_lines = 0;
    int flag = 0;
    switch (index)
    {
    case -2:
        file_pointer = fopen("negative.csv", "r");
        flag = -2;
        break;

    case -1:
        file_pointer = fopen("positive.csv", "r");
        flag = -1;
        break;

    case 0:
        file_pointer = fopen("funwrd.csv", "r");
        break;

    case 1:
        file_pointer = fopen("comp.csv", "r");
        flag = 1;
        break;

    case 2:
        file_pointer = fopen("phy.csv", "r");
        flag = 2;
        break;

    case 3:
        file_pointer = fopen("bio.csv", "r");
        flag = 3;
        break;

    case 4:
        file_pointer = fopen("chem.csv", "r");
        flag = 4;
        break;

    default:
        printf("\n!!<lineCount>--switch default hit");
        break;
    }

    if (file_pointer == NULL)
    {
        printf("\n!!<lineCount>--File missing %d", flag);
    }
    else
    {
        temp_char = fgetc(file_pointer);
        while (temp_char != EOF)
        {
            if (temp_char == '\n')
            {
                num_of_lines += 1;
            }
            temp_char = fgetc(file_pointer);
        }
    }
    fclose(file_pointer);
    /* [+1] for last line '\n' which doesn't exist,
    another [+1] for array */
    num_of_lines = num_of_lines + 2;
    return num_of_lines;
}

void semantics(char input_words[500][20], int num_of_words)
{
    // Semantic Analysis.
    int compare, loop, i, cal[5] = {0, 0, 0, 0, 0};
    float percent[5] = {0, 0, 0, 0, 0};
    char str[15];

    int comp_line, phy_line, bio_line, chem_line, fun_line;
    fun_line = lineCount(0);
    comp_line = lineCount(1);
    phy_line = lineCount(2);
    bio_line = lineCount(3);
    chem_line = lineCount(4);

    char words_comp[comp_line][20], words_phy[phy_line][20], words_chem[chem_line][20], words_bio[bio_line][20], words_fun[fun_line][20];

    FILE *fp_fun = fopen("funwrd.csv", "r");
    if (fp_fun == NULL)
    {
        printf("\n!!(analysis.c)<semantics>--Function is missing.");
    }
    for (int f = 0; f < fun_line; f++)
    {
        fscanf(fp_fun, "%s", str);
        strcpy(&words_fun[f][20], str);
    }
    fclose(fp_fun);

    FILE *fp_comp = fopen("comp.csv", "r");
    if (fp_comp == NULL)
    {
        printf("\n!!(analysis.c)<semantics>--Computer is missing.");
    }
    for (int f = 0; f < comp_line; f++)
    {
        fscanf(fp_comp, "%s", str);
        strcpy(&words_comp[f][20], str);
    }
    fclose(fp_comp);

    FILE *fp_phy = fopen("phy.csv", "r");
    if (fp_phy == NULL)
    {
        printf("\n!!(analysis.c)<semantics>--Physics is missing.");
    }
    for (int f = 0; f < phy_line; f++)
    {
        fscanf(fp_phy, "%s", str);
        strcpy(&words_phy[f][20], str);
    }
    fclose(fp_phy);

    FILE *fp_bio = fopen("bio.csv", "r");
    if (fp_bio == NULL)
    {
        printf("\n!!(analysis.c)<semantics>--Biology is missing.");
    }
    for (int f = 0; f < bio_line; f++)
    {
        fscanf(fp_bio, "%s", str);
        strcpy(&words_bio[f][20], str);
    }
    fclose(fp_bio);

    FILE *fp_chem = fopen("chem.csv", "r");
    if (fp_chem == NULL)
    {
        printf("\n!!(analysis.c)<semantics>--Chemistry is missing.");
    }
    for (int f = 0; f < chem_line; f++)
    {
        fscanf(fp_chem, "%s", str);
        strcpy(&words_chem[f][20], str);
    }
    fclose(fp_chem);

    for (i = 0; i < num_of_words; i++)
    {
        for (loop = 0; loop < fun_line; loop++)
        {
            compare = strcmp(input_words[i], words_fun[loop]);
            if (compare == 0)
            {
                cal[0] += 1;
            }
        }
        for (loop = 0; loop < comp_line; loop++)
        {
            compare = strcmp(input_words[i], words_comp[loop]);
            if (compare == 0)
            {
                cal[1] += 1;
            }
        }
        for (loop = 0; loop < phy_line; loop++)
        {
            compare = strcmp(input_words[i], words_phy[loop]);
            if (compare == 0)
            {
                cal[2] += 1;
            }
        }
        for (loop = 0; loop < bio_line; loop++)
        {
            compare = strcmp(input_words[i], words_phy[loop]);
            if (compare == 0)
            {
                cal[3] += 1;
            }
        }
        for (loop = 0; loop < chem_line; loop++)
        {
            compare = strcmp(input_words[i], words_chem[loop]);
            if (compare == 0)
            {
                cal[4] += 1;
            }
        }
    }

    for (i = 0; i < 6; i++)
    {
        percent[i] = (cal[i] / num_of_words) * 100;
        switch (i)
        {
        case 0:
            printf("\nFunction Word     |%4f", percent[i]);
            break;

        case 1:
            printf("\nComputer Science  |%4f", percent[i]);
            break;

        case 2:
            printf("\nPhysics           |%4f", percent[i]);
            break;

        case 3:
            printf("\nBiology           |%4f", percent[i]);
            break;

        case 4:
            printf("\nChemistry         |%4f", percent[i]);
            break;

        case 5:
            percent[5] = 100 - (percent[4] + percent[3] + percent[2] + percent[1] + percent[0]);
            printf("\nUnknowns          |%4f", percent[i]);
            break;

        default:
            printf("\n!!(analysis.c)<semantics>--switch_default");
            break;
        }
    }
    printf("\n Results of Semantic Analysis: ");
    printf("\n The sentence seems to be related to ");
    if (percent[1] > percent[2] && percent[1] > percent[3] && percent[1] > percent[4])
    {
        printf("Computer Science.");
    }
    else if (percent[2] > percent[1] && percent[2] > percent[3] && percent[2] > percent[4])
    {
        printf("Physics.");
    }
    else if (percent[3] > percent[2] && percent[3] > percent[1] && percent[3] > percent[4])
    {
        printf("Biology.");
    }
    else if (percent[4] > percent[2] && percent[4] > percent[3] && percent[4] > percent[4])
    {
        printf("Chemistry.");
    }
    else if (percent[1] == percent[2] == percent[3] == percent[4])
    {
        printf("all the topics.");
    }
    else
    {
        printf("\t!!Sorry..\n Can't figure out it\nPlease try something else\nMaybe multiple topics are infused in the text.");
    }
}
void sentiment(char arr[500][20], int num_of_words)
{
    // Sentiment Analysis.
    printf("Not Yet Completed");
}
