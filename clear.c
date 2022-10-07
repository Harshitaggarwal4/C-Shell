#include "clear.h"
#include "headers.h"
void clear_call()
{
    printf("\e[1;1H\e[2J");
}
void harshit_clear(int number_of_inputs)
{
    if (number_of_inputs > 1)
    {
        printf("Error! Extra arguments\n");
        return;
    }
    clear_call();
    return;
}