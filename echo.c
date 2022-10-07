#include "echo.h"
#include "headers.h"
int echo_call(char **input, int number_of_inputs)
{
    for (int i = 1; i < number_of_inputs; i++)
    {
        printf("%s ", input[i]);
    }
    printf("\n");
    return 1;
}
void harshit_echo(char **tokenized, int number_of_inputs)
{
    if (number_of_inputs == 1)
    {
        printf("\n");
        return;
    }
    echo_call(tokenized, number_of_inputs);
    return;
}