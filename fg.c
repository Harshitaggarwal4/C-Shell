#include "fg.h"
#include "headers.h"
#include "my_dll.h"
#include "node.h"
void harshit_fg(char **tokenized, int number_of_inputs, dll *background_processes, int *max_number_of_processes, char *print_in_terminal, int *fgrunning, char *fgname)
{
    if (number_of_inputs != 2)
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
    int piid = find_via_process_number(background_processes, process_number, fgname);
    if (piid == -1)
    {
        printf("Error! Process doesn't exist\n");
        return;
    }
    int status;
    setpgid(piid, getpgid(0));
    signal(SIGTTIN, SIG_IGN);
    signal(SIGTTOU, SIG_IGN);
    tcsetpgrp(0, piid);
    if (kill(piid, SIGCONT) < 0)
    {
        perror("Error");
    }
    struct timeval start_time, end_time;
    gettimeofday(&start_time, NULL);
    (*fgrunning) = piid;
    waitpid(piid, &status, WUNTRACED);
    gettimeofday(&end_time, NULL);
    double total_time = end_time.tv_sec - start_time.tv_sec;
    if (total_time >= 1)
    {
        sprintf(print_in_terminal, "took %ds", (int)total_time);
    }
    tcsetpgrp(0, getpgid(0));
    signal(SIGTTIN, SIG_DFL);
    signal(SIGTTOU, SIG_DFL);
    pid_t chpid = piid;
    char name_of_process[1000];
    int process_numb = 0;
    find(background_processes, chpid, name_of_process, &process_numb);
    delete (background_processes, chpid);
    find_max(background_processes, max_number_of_processes);
    return;
}