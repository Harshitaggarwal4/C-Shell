#include "headers.h"
#include "cd.h"
#include "clear.h"
#include "discover.h"
#include "echo.h"
#include "history.h"
#include "ls.h"
#include "pinfo.h"
#include "pwd_my.h"
#include "random_functions.h"
#include "input.h"
#include "display.h"
#include "tokenization.h"
#include "foreground.h"
#include "background.h"
#include "my_dll.h"
#include "node.h"
#include "jobs.h"
#include "bg.h"
#include "sig.h"
#include "autocompletion.h"
#include "fg.h"
struct utsname unameData;
char *hostname;
char *buf;
char path_to_home[PATH_MAX];
int size_of_path_to_home;
char print_in_terminal[1000] = "\0";
dll *background_processes;
int fgrunning = 0;
int max_number_of_processes = 0;
char fgname[1000];
void handler(int sig)
{
    pid_t chpid;
    int status;
    while ((chpid = waitpid(-1, &status, WNOHANG)) > 0)
    {
        if (fgrunning != 0)
        {
            fgrunning = 0;
            strcpy(fgname, "");
            return;
        }
        char name_of_process[1000];
        int process_number = 0;
        int i = find(background_processes, chpid, name_of_process, &process_number);
        if (i == 0)
        {
            return;
        }
        printf("\n%s with pid = %d exited normally\n", name_of_process, chpid);
        harshit_display(buf, hostname, path_to_home, size_of_path_to_home, print_in_terminal);
        fflush(stdout);
        delete (background_processes, chpid);
        find_max(background_processes, &max_number_of_processes);
    }
}
void ctrlchandler(int sig)
{
    if (fgrunning == 0)
    {
        printf("\n");
        harshit_display(buf, hostname, path_to_home, size_of_path_to_home, print_in_terminal);
    }
    else
    {
        kill(fgrunning, SIGINT);
    }
    return;
}
void ctrlzhandler(int sig)
{
    // signal(SIGTSTP, ctrlzhandler);
    if (fgrunning == 0)
    {
        printf("\n");
        harshit_display(buf, hostname, path_to_home, size_of_path_to_home, print_in_terminal);
    }
    else
    {
        // kill(fgrunning, SIGSTOP);
        kill(fgrunning, SIGTSTP);
        setpgid(fgrunning, fgrunning);
        (max_number_of_processes)++;
        insert(background_processes, fgrunning, fgname, (max_number_of_processes));
        fgrunning = 0;
        strcpy(fgname, "");
    }
    return;
}
int main()
{
    signal(SIGCHLD, handler);
    signal(SIGINT, ctrlchandler);
    signal(SIGTSTP, ctrlzhandler);
    // signal(SIGTSTP, SIG_IGN);
    background_processes = (dll *)malloc(sizeof(dll));
    background_processes->last = NULL;
    background_processes->root = NULL;
    background_processes->root = (node *)malloc(sizeof(node));
    background_processes->root->next = NULL;
    uname(&unameData);
    hostname = (char *)malloc(sizeof(char) * 1000);
    hostname = unameData.nodename;
    buf = (char *)malloc(10 * sizeof(char));
    buf = getlogin();
    getcwd(path_to_home, sizeof(path_to_home));
    size_of_path_to_home = strlen(path_to_home);
    char prev_directory[PATH_MAX] = "\0";
    char **history = (char **)malloc(__SIZEOF_POINTER__ * 20);
    for (int o = 0; o < 20; o++)
    {
        history[o] = (char *)malloc(sizeof(char) * 10000);
    }
    history[0][0] = '\0';
    int number_of_history_stored = 0;
    history_input(history, &number_of_history_stored);
    while (1)
    {
        char input[10000];
        int size = 10000;
        char **tokenize_for_semicolon = (char **)malloc(__SIZEOF_POINTER__ * 20);
        for (int o = 0; o < 20; o++)
        {
            tokenize_for_semicolon[o] = (char *)malloc(sizeof(char) * 10000);
        }
        char t[2] = ";";
        char *tokenize;
        int number_of_inputs_for_semicolon = 0;
        harshit_display(buf, hostname, path_to_home, size_of_path_to_home, print_in_terminal);
        int returned = raw_input(input, &number_of_history_stored, history, buf, hostname, path_to_home, size_of_path_to_home, print_in_terminal, background_processes);
        if (returned == 1)
        {
            continue;
        }
        harshit_tokenize_for_semicolon(tokenize, input, t, tokenize_for_semicolon, &number_of_inputs_for_semicolon);
        int output_redirection = 0;
        int input_redirection = 0;
        for (int z = 0; z < number_of_inputs_for_semicolon; z++)
        {
            if (input_redirection != 0)
            {
                dup2(input_redirection, 0);
                close(input_redirection);
                input_redirection = 0;
            }
            if (output_redirection != 0)
            {
                dup2(output_redirection, 1);
                close(output_redirection);
                output_redirection = 0;
            }
            int number_of_pipes_found = 0;
            for (int yo = 0; yo < strlen(tokenize_for_semicolon[z]); yo++)
            {
                if (tokenize_for_semicolon[z][yo] == '|')
                {
                    number_of_pipes_found++;
                }
            }
            char **tokenize_for_pipe = (char **)malloc(__SIZEOF_POINTER__ * 20);
            for (int i = 0; i < 20; i++)
            {
                tokenize_for_pipe[i] = (char *)malloc(sizeof(char) * 1000);
            }
            char *token_for_pipe;
            int number_of_pipes = 0;
            harshit_tokenize_for_pipe(token_for_pipe, tokenize_for_pipe, &number_of_pipes, tokenize_for_semicolon[z]);
            if (number_of_pipes != number_of_pipes_found + 1)
            {
                printf("Error! Invalid input\n");
                continue;
            }
            int pipefds0[2];
            int pipefds1[2];
            for (int yo = 0; yo < number_of_pipes; yo++)
            {
                if (input_redirection != 0)
                {
                    dup2(input_redirection, 0);
                    close(input_redirection);
                    input_redirection = 0;
                }
                if (output_redirection != 0)
                {
                    dup2(output_redirection, 1);
                    close(output_redirection);
                    output_redirection = 0;
                }
                if (number_of_pipes != 1)
                {
                    if (yo % 2 == 0)
                    {
                        if (pipe(pipefds0) == -1)
                        {
                            perror("pipe");
                        }
                    }
                    else
                    {
                        if (pipe(pipefds1) == -1)
                        {
                            perror("pipe");
                        }
                    }
                    if (yo == 0)
                    {
                        strcpy(tokenize_for_semicolon[z], tokenize_for_pipe[yo]);
                        // strcat(tokenize_for_semicolon[z], " >.pipe");
                        output_redirection = dup(1);
                        if (yo % 2 == 1)
                        {
                            int check = dup2(pipefds1[1], 1);
                            if (check == -1)
                            {
                                printf("Error!\n");
                            }
                            close(pipefds1[1]);
                        }
                        else
                        {
                            int check = dup2(pipefds0[1], 1);
                            if (check == -1)
                            {
                                printf("Error!\n");
                            }
                            close(pipefds0[1]);
                        }
                    }
                    else if (yo == number_of_pipes - 1)
                    {
                        strcpy(tokenize_for_semicolon[z], tokenize_for_pipe[yo]);
                        // strcat(tokenize_for_semicolon[z], " <.pipe");
                        input_redirection = dup(0);
                        if (yo % 2 == 1)
                        {
                            int check1 = dup2(pipefds0[0], 0);
                            if (check1 == -1)
                            {
                                printf("Error!\n");
                            }
                            close(pipefds0[0]);
                        }
                        else
                        {
                            int check1 = dup2(pipefds1[0], 0);
                            if (check1 == -1)
                            {
                                printf("Error!\n");
                            }
                            close(pipefds1[0]);
                        }
                    }
                    else
                    {
                        strcpy(tokenize_for_semicolon[z], tokenize_for_pipe[yo]);
                        // strcat(tokenize_for_semicolon[z], " <.pipe>.pipe");
                        input_redirection = dup(0);
                        output_redirection = dup(1);
                        if (yo % 2 == 1)
                        {
                            int check = dup2(pipefds0[0], 0);
                            if (check == -1)
                            {
                                printf("Error!\n");
                            }
                            close(pipefds0[0]);
                            int check1 = dup2(pipefds1[1], 1);
                            if (check1 == -1)
                            {
                                printf("Error!\n");
                            }
                            close(pipefds1[1]);
                        }
                        else
                        {
                            int check = dup2(pipefds1[0], 0);
                            if (check == -1)
                            {
                                printf("Error!\n");
                            }
                            close(pipefds1[0]);
                            int check1 = dup2(pipefds0[1], 1);
                            if (check1 == -1)
                            {
                                printf("Error!\n");
                            }
                            close(pipefds0[1]);
                        }
                    }
                }
                char **tokenize_for_and = (char **)malloc(__SIZEOF_POINTER__ * 20);
                for (int o = 0; o < 20; o++)
                {
                    tokenize_for_and[o] = (char *)malloc(sizeof(char) * 10000);
                }
                int count_of_and_in_string = 0;
                for (int j = 0; j < strlen(tokenize_for_semicolon[z]); j++)
                {
                    if (tokenize_for_semicolon[z][j] == '&')
                    {
                        count_of_and_in_string++;
                    }
                }
                char and[2] = "&";
                char *token_for_and;
                int number_of_inputs_for_and = 0;
                harshit_tokenize_for_and(token_for_and, tokenize_for_semicolon, z, and, tokenize_for_and, &number_of_inputs_for_and);
                int and_number = count_of_and_in_string;
                for (int an = 0; an < and_number; an++)
                {
                    char **tokenized = (char **)malloc(__SIZEOF_POINTER__ * 20);
                    for (int o = 0; o < 20; o++)
                    {
                        tokenized[o] = (char *)malloc(sizeof(char) * 10000);
                    }
                    char s[3] = " \t";
                    char *token;
                    int number_of_inputs = 0;
                    harshit_tokenize_for_spaces(token, tokenize_for_and, an, s, tokenized, &number_of_inputs);
                    harshit_background(number_of_inputs, tokenized, background_processes, &max_number_of_processes);
                }
                if (number_of_inputs_for_and != count_of_and_in_string)
                {
                    strcpy(tokenize_for_semicolon[z], tokenize_for_and[number_of_inputs_for_and - 1]);
                }
                else
                {
                    continue;
                }
                char **tokenize_for_input_output = (char **)malloc(__SIZEOF_POINTER__ * 20);
                for (int o = 0; o < 20; o++)
                {
                    tokenize_for_input_output[o] = (char *)malloc(sizeof(char) * 10000);
                }
                char *token_for_input_output;
                int err = harshit_tokenize_for_input_output(token_for_input_output, tokenize_for_semicolon[z], tokenize_for_input_output, &output_redirection, &input_redirection);
                if (err == -1)
                {
                    continue;
                }
                char **tokenized = (char **)malloc(__SIZEOF_POINTER__ * 20);
                for (int o = 0; o < 20; o++)
                {
                    tokenized[o] = (char *)malloc(sizeof(char) * 10000);
                }
                char s[3] = " \t";
                char *token;
                int number_of_inputs = 0;
                harshit_tokenize_for_spaces(token, tokenize_for_semicolon, z, s, tokenized, &number_of_inputs);
                if (strcmp(tokenized[0], "echo") == 0)
                {
                    harshit_echo(tokenized, number_of_inputs);
                    continue;
                }
                else if (strcmp(tokenized[0], "cd") == 0)
                {
                    harshit_cd(number_of_inputs, tokenized, path_to_home, prev_directory);
                    continue;
                }
                else if (strcmp(tokenized[0], "pwd") == 0)
                {
                    harshit_pwd(number_of_inputs, size_of_path_to_home);
                    continue;
                }
                else if (strcmp(tokenized[0], "ls") == 0)
                {
                    harshit_ls(number_of_inputs, tokenized, prev_directory, path_to_home);
                    continue;
                }
                else if (strcmp(tokenized[0], "history") == 0)
                {
                    harshit_history(number_of_inputs, number_of_history_stored, tokenized, history);
                    continue;
                }
                else if (strcmp(tokenized[0], "clear") == 0)
                {
                    harshit_clear(number_of_inputs);
                    continue;
                }
                else if (strcmp(tokenized[0], "pinfo") == 0)
                {
                    harshit_pinfo(number_of_inputs, tokenized, size_of_path_to_home, path_to_home, background_processes);
                    continue;
                }
                else if (strcmp(tokenized[0], "discover") == 0)
                {
                    harshit_discover(number_of_inputs, tokenized);
                    continue;
                }
                else if (strcmp(tokenized[0], "jobs") == 0)
                {
                    harshit_jobs(tokenized, number_of_inputs, background_processes);
                    continue;
                }
                else if (strcmp(tokenized[0], "bg") == 0)
                {
                    harshit_bg(tokenized, number_of_inputs, background_processes);
                    continue;
                }
                else if (strcmp(tokenized[0], "sig") == 0)
                {
                    harshit_sig(number_of_inputs, tokenized, background_processes);
                    continue;
                }
                else if (strcmp(tokenized[0], "fg") == 0)
                {
                    harshit_fg(tokenized, number_of_inputs, background_processes, &max_number_of_processes, print_in_terminal, &fgrunning, fgname);
                    continue;
                }
                struct timeval start_time, end_time;
                gettimeofday(&start_time, NULL);
                fgrunning = 1;
                strcat(fgname, tokenized[0]);
                for (int i = 1; i < number_of_inputs; i++)
                {
                    strcat(fgname, " ");
                    strcat(fgname, tokenized[i]);
                }
                harshit_foreground(number_of_inputs, tokenized, print_in_terminal, &fgrunning);
                fgrunning = 0;
                strcpy(fgname, "");
                gettimeofday(&end_time, NULL);
                double total_time = end_time.tv_sec - start_time.tv_sec;
                if (total_time >= 1)
                {
                    sprintf(print_in_terminal, "took %ds", (int)total_time);
                }
            }
        }
        if (input_redirection != 0)
        {
            dup2(input_redirection, 0);
            close(input_redirection);
            input_redirection = 0;
        }
        if (output_redirection != 0)
        {
            dup2(output_redirection, 1);
            close(output_redirection);
            output_redirection = 0;
        }
        char temporary[1000];
        getcwd(temporary, sizeof(temporary));
        char **temp = (char **)malloc(__SIZEOF_POINTER__ * 2);
        for (int i = 0; i < 2; i++)
        {
            temp[i] = (char *)malloc(sizeof(char) * 1000);
        }
        strcpy(temp[1], "~");
        char tempp[1000];
        harshit_cd(2, temp, path_to_home, tempp);
        history_output(history, &number_of_history_stored);
        strcpy(temp[1], temporary);
        harshit_cd(2, temp, path_to_home, tempp);
    }
}