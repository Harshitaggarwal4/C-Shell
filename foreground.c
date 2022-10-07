#include "foreground.h"
#include "headers.h"
void harshit_foreground(int number_of_inputs, char **tokenized, char *print_in_terminal, int *fgrunning)
{
    tokenized[number_of_inputs] = NULL;
    // signal(SIGTSTP, SIG_IGN);
    int return_of_fork = fork();
    if (return_of_fork == -1)
    {
        printf("Error! Unable to execute command\n");
        return;
    }
    if (return_of_fork == 0)
    {
        // setpgid(0, 0);
        // signal(SIGTSTP, SIG_DFL);
        int check = execvp(tokenized[0], tokenized);
        if (check == -1)
        {
            printf("Error! Unable to execute command\n");
            return;
        }
    }
    else
    {
        // tcsetpgrp(0, return_of_fork);
        (*fgrunning) = return_of_fork;
        int status;
        waitpid(return_of_fork, &status, WUNTRACED);
        // if (WIFEXITED(status))
        // {
        //     setpgid(fgrunning, fgrunning);
        //     (max_number_of_processes)++;
        //     insert(background_processes, fgrunning, fgname, (max_number_of_processes));
        //     fgrunning = 0;
        // }
        // tcsetpgrp(0, getpid());
        return;
    }
}