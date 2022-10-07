#include "pinfo.h"
#include "headers.h"
#include "my_dll.h"
#include "node.h"
int pinfo_call(char *piid, int size_of_path_to_home, char *path_to_home, dll *background_processes)
{
    char information[1000] = "/proc/";
    strcat(information, piid);
    strcat(information, "/stat");
    FILE *f = fopen(information, "r");
    if (!f)
    {
        return -1;
    }
    int pid, pgrp, tpgid;
    long unsigned int vsize;
    char stat;
    char temp[1000];
    int temporary[20];
    fscanf(f, "%d %s %c %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %lu", &pid, temp, &stat, &temporary[0], &pgrp, &temporary[1], &temporary[2], &tpgid, &temporary[3], &temporary[4], &temporary[5], &temporary[6], &temporary[7], &temporary[8], &temporary[9], &temporary[10], &temporary[11], &temporary[12], &temporary[13], &temporary[14], &temporary[15], &temporary[16], &vsize);
    printf("pid : %d\n", pid);
    char h;
    h = stat == 'T' ? 'S' : 'R';
    if (stat == 'Z')
    {
        h = 'Z';
    }
    printf("process Status : %c", h);
    char plus = ' ';
    if (pgrp == tpgid)
    {
        plus = '+';
    }
    int i = find(background_processes, pid, temp, &temporary[0]);
    if (i != 0)
    {
        plus = ' ';
    }
    printf("%c\n", plus);
    printf("memory : %lu\n", vsize);
    fclose(f);
    strcpy(information, "/proc/");
    strcat(information, piid);
    strcat(information, "/exe");
    char executable_path[1001];
    int size_of_executable_path = readlink(information, executable_path, 1000);
    executable_path[size_of_executable_path] = '\0';
    printf("executable path : ");
    if (strncmp(executable_path, path_to_home, strlen(path_to_home)) != 0)
    {
        printf("%s\n", executable_path);
    }
    else
    {
        printf("~%s\n", &executable_path[size_of_path_to_home]);
    }
}
void harshit_pinfo(int number_of_inputs, char **tokenized, int size_of_path_to_home, char *path_to_home, dll *background_processes)
{
    if (number_of_inputs > 2)
    {
        printf("Error! Extra arguments\n");
        return;
    }
    pid_t piid;
    if (number_of_inputs == 1)
    {
        piid = getpid();
    }
    else
    {
        piid = atoi(tokenized[1]);
    }
    int piid_int = piid;
    char piid_string[1000];
    sprintf(piid_string, "%d", piid_int);
    int checking = pinfo_call(piid_string, size_of_path_to_home, path_to_home, background_processes);
    if (checking == -1)
    {
        printf("Error! This process doesn't exist.\n");
    }
    return;
}