#include "background.h"
#include "headers.h"
#include "my_dll.h"
#include "node.h"
void harshit_background(int number_of_inputs, char **tokenized, dll *background_processes, int *max_numer_of_processes)
{
    tokenized[number_of_inputs] = NULL;
    int return_of_fork = fork();
    if (return_of_fork == -1)
    {
        printf("Error! Unable to execute command\n");
        return;
    }
    if (return_of_fork == 0)
    {
        setpgid(getpid(), getpid());
        int check = execvp(tokenized[0], tokenized);
        if (check == -1)
        {
            printf("Error! Unable to execute command\n");
            kill(getpid(), SIGKILL);
            return;
        }
    }
    else
    {
        (*max_numer_of_processes)++;
        for (int i = 1; i < number_of_inputs; i++)
        {
            strcat(tokenized[0], " ");
            strcat(tokenized[0], tokenized[i]);
        }
        insert(background_processes, return_of_fork, tokenized[0], (*max_numer_of_processes));
        printf("[%d] %d\n", (*max_numer_of_processes), return_of_fork);
        return;
    }
    return;
}