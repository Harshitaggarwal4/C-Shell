#include "bg.h"
#include "headers.h"
#include "my_dll.h"
#include "node.h"
void harshit_bg(char **tokenized, int number_of_inputs, dll *list)
{
    if (number_of_inputs > 2)
    {
        printf("Error! Invalid input\n");
        return;
    }
    int piid;
    if (number_of_inputs == 1)
    {
        piid = getpid();
    }
    else
    {
        piid = atoi(tokenized[1]);
        if (piid == -1)
        {
            printf("Error! Invalid input\n");
            return;
        }
    }
    char temp[1000];
    piid = find_via_process_number(list, piid, temp);
    if (piid <= 0)
    {
        printf("Error! Process doesn't exist\n");
        return;
    }
    if (kill(piid, SIGCONT) < 0)
    {
        printf("Error! process doesn't exest\n");
    }
    return;
}