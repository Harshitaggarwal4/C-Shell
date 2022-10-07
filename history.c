#include "history.h"
#include "headers.h"
#include "random_functions.h"
void harshit_history(int number_of_inputs, int number_of_history_stored, char **tokenized, char **history)
{
    if (number_of_inputs > 2)
    {
        printf("Error! Extra arguments\n");
        return;
    }
    int show = number_of_history_stored > 10 ? 10 : number_of_history_stored;
    if (strcmp(tokenized[1], "") != 0)
    {
        int number = atoi(tokenized[1]);
        if (number < 0 || (number == 0 && strcmp(tokenized[1], "0") != 0))
        {
            printf("Error! Invalid Input.\n");
            return;
        }
        show = show < atoi(tokenized[1]) ? show : atoi(tokenized[1]);
    }
    for (int z = show - 1; z > -1; z--)
    {
        printf("%s\n", history[z]);
    }
    return;
}
void history_input(char **history, int *number_of_history_stored)
{
    FILE *fp = fopen(".history", "r");
    if (fp == NULL)
    {
        FILE *f = fopen(".history", "w");
        fclose(f);
        fp = fopen(".history", "r");
    }
    char str[1000];
    while (fgets(str, 1000, fp) != NULL)
    {
        for (int d = 1; d < 20; d++)
        {
            swap(history[0], history[d]);
        }
        strcpy(history[0], str);
        history[0][strlen(history[0]) - 1] = '\0';
        (*number_of_history_stored)++;
    }
    fclose(fp);
}
void history_output(char **history, int *number_of_history_stored)
{
    FILE *fp = fopen(".history", "w");
    for (int d = (*number_of_history_stored) - 1; d > -1; d--)
    {
        fprintf(fp, "%s\n", history[d]);
    }
    fclose(fp);
}