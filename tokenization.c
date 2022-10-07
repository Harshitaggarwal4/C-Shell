#include "tokenization.h"
#include "headers.h"
void harshit_tokenize_for_semicolon(char *tokenize, char *input, char *t, char **tokenize_for_semicolon, int *number_of_inputs_for_semicolon)
{
    tokenize = strtok(input, t);
    strcpy(tokenize_for_semicolon[0], tokenize);
    while (tokenize != NULL)
    {
        strcpy(tokenize_for_semicolon[*number_of_inputs_for_semicolon], tokenize);
        (*number_of_inputs_for_semicolon)++;
        tokenize = strtok(NULL, t);
    }
    tokenize_for_semicolon[*number_of_inputs_for_semicolon][0] = '\0';
}
void harshit_tokenize_for_spaces(char *token, char **tokenize_for_semicolon, int z, char *s, char **tokenized, int *number_of_inputs)
{
    token = strtok(tokenize_for_semicolon[z], s);
    strcpy(tokenized[0], token);
    while (token != NULL)
    {
        strcpy(tokenized[*number_of_inputs], token);
        (*number_of_inputs)++;
        token = strtok(NULL, s);
    }
    tokenized[*number_of_inputs][0] = '\0';
    return;
}
void harshit_tokenize_for_and(char *token_for_and, char **tokenize_for_semicolon, int z, char *and, char **tokenize_for_and, int *number_of_inputs_for_and)
{
    token_for_and = strtok(tokenize_for_semicolon[z], and);
    strcpy(tokenize_for_and[0], token_for_and);
    while (token_for_and != NULL)
    {
        strcpy(tokenize_for_and[*number_of_inputs_for_and], token_for_and);
        (*number_of_inputs_for_and)++;
        token_for_and = strtok(NULL, and);
    }
    tokenize_for_and[*number_of_inputs_for_and][0] = '\0';
    return;
}
int harshit_tokenize_for_input_output(char *token, char *tokenized, char **tokenize, int *output, int *input_backup)
{
    int append = 0;
    for (int i = 1; i < strlen(tokenized); i++)
    {
        if (tokenized[i] == '>' && tokenized[i - 1] == '>')
        {
            append = 1;
        }
    }
    int input = 0;
    char tokenize_for_input[1000][1000];
    char tok[2] = "<";
    token = strtok(tokenized, tok);
    strcpy(tokenize_for_input[0], token);
    int number = 0;
    while (token != NULL)
    {
        strcpy(tokenize_for_input[number], token);
        (number)++;
        token = strtok(NULL, tok);
    }
    tokenize_for_input[number][0] = '\0';
    if (number > 2)
    {
        printf("Error! Invalid Input\n");
        return -1;
    }
    if (number == 2)
    {
        (input) = 1;
    }
    strcpy(tok, ">");
    token = strtok(tokenize_for_input[0], tok);
    strcpy(tokenize[0], token);
    int number2 = 0;
    number = 0;
    while (token != NULL)
    {
        strcpy(tokenize[number], token);
        (number)++;
        number2++;
        token = strtok(NULL, tok);
    }
    tokenize[number][0] = '\0';
    int number1 = 0;
    if ((input) == 1)
    {
        token = strtok(tokenize_for_input[1], tok);
        strcpy(tokenize[number2], token);
        while (token != NULL)
        {
            strcpy(tokenize[number2], token);
            (number2)++;
            number1++;
            token = strtok(NULL, tok);
        }
        tokenize[number2][0] = '\0';
    }
    if (number2 > 3)
    {
        printf("Error! Invalid input\n");
        return -1;
    }
    if ((number2 == 3 && (input) == 1) || (number2 == 2 && (input) == 0))
    {
        (*output) = 1;
    }
    int out = 0, in = 0;
    if ((*output) == 1)
    {
        if (number == 2)
        {
            out = 1;
            if ((input) == 1)
            {
                in = 2;
            }
        }
        else
        {
            out = 2;
            in = 1;
        }
    }
    if ((input) == 1 && (*output) == 0)
    {
        in = 1;
    }
    if ((input) == 1)
    {
        char space[3] = " \t";
        char *t = (char *)malloc(sizeof(char) * 1000);
        t = strtok(tokenize[in], space);
        // strcpy(tokenize[in], t);
        FILE *fp;
        char str[1000];
        fp = fopen(t, "r");
        if (fp == NULL)
        {
            printf("Error! Check if the file exists\n");
            return -1;
        }
        *input_backup = dup(0);
        int check = dup2(fileno(fp), 0);
        if (check == -1)
        {
            printf("Error!\n");
        }
        fclose(fp);
        strcpy(tokenized, tokenize[0]);
    }
    if ((*output) == 1)
    {
        char space[3] = " \t";
        char *t = (char *)malloc(sizeof(char) * 1000);
        t = strtok(tokenize[out], space);
        strcpy(tokenize[out], t);
        int fp = 0;
        if (append == 0)
        {
            FILE *ffp = fopen(tokenize[out], "w");
            fp = fileno(ffp);
        }
        if (append == 1)
        {
            FILE *fpp = fopen(tokenize[out], "a");
            fp = fileno(fpp);
        }
        *output = dup(1);
        int check = dup2(fp, 1);
        if (check == -1)
        {
            printf("Error!\n");
            return -1;
        }
        close(fp);
        if (input == 0)
        {
            strcpy(tokenized, tokenize[0]);
        }
    }
    return 0;
}
void harshit_tokenize_for_pipe(char *token, char **tokenize_for_pipe, int *number, char *input)
{
    char temp[2] = "|";
    token = strtok(input, temp);
    while (token != NULL)
    {
        strcpy(tokenize_for_pipe[(*number)], token);
        (*number)++;
        token = strtok(NULL, temp);
    }
    tokenize_for_pipe[(*number)] = "\0";
}