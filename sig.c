#include "sig.h"
#include "headers.h"
#include "my_dll.h"
#include "node.h"
void harshit_sig(int number_of_inputs, char **tokenized, dll *list)
{
    if (number_of_inputs != 3)
    {
        printf("Error! Invalid input\n");
        return;
    }
    int process_number = atoi(tokenized[1]);
    if (process_number == -1)
    {
        printf("Error! Invalid input\n");
        return;
    }
    int signal_number = atoi(tokenized[2]);
    if (signal_number == -1)
    {
        printf("Error! Invalid input\n");
        return;
    }
    char temp[1000];
    int piid = find_via_process_number(list, process_number, temp);
    if (piid == -1)
    {
        printf("Error! Process doesn't exist\n");
        return;
    }
    if (kill(piid, signal_number) != 0)
    {
        perror("error");
    }
}