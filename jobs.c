#include "jobs.h"
#include "headers.h"
#include "my_dll.h"
#include "node.h"
void swap_all(char *naa, char *nab, int *na, int *nb, int *pa, int *pb, char *sa, char *sb)
{
    char tempp[1000];
    strcpy(tempp, naa);
    strcpy(naa, nab);
    strcpy(nab, tempp);
    int temp;
    temp = (*na);
    (*na) = (*nb);
    (*nb) = temp;
    temp = (*pa);
    (*pa) = (*pb);
    (*pb) = temp;
    char tem;
    tem = (*sa);
    (*sa) = (*sb);
    (*sb) = tem;
}
void bubblesort(char **names, int n, int number[], int pids[], char status[])
{
    int i, j;
    for (i = 0; i < n - 1; i++)
    {
        for (j = 0; j < n - i - 1; j++)
        {
            if (strcmp(names[j], names[j + 1]) >= 0)
            {
                swap_all(names[j], names[j + 1], &number[j], &number[j + 1], &pids[j], &pids[j + 1], &status[j], &status[j + 1]);
            }
        }
    }
}
void jobs_call(dll *list, int l, int a)
{
    char **names = (char **)malloc(__SIZEOF_POINTER__ * 1000);
    for (int i = 0; i < 1000; i++)
    {
        names[i] = (char *)malloc(sizeof(char) * 1000);
    }
    int number[1000];
    int pids[1000];
    char status[1000];
    int count = 0;
    node *temp = list->last;
    if (temp == NULL)
    {
        printf("\n");
        return;
    }
    while (1)
    {
        if (temp->prev == NULL)
        {
            break;
        }
        find(list, temp->data, names[count], &number[count]);
        pids[count] = temp->data;
        char information[1000] = "/proc/";
        char piid[1000];
        sprintf(piid, "%d", pids[count]);
        strcat(information, piid);
        strcat(information, "/stat");
        FILE *f = fopen(information, "r");
        fscanf(f, "%*d %*s %c", &status[count]);
        fclose(f);
        temp = temp->prev;
        if (status[count] == 'T' && l == 1)
        {
            count++;
        }
        else if (a == 1 && status[count] != 'T')
        {
            count++;
        }
    }
    bubblesort(names, count, number, pids, status);
    for (int i = 0; i < count; i++)
    {
        printf("[%d] %s %s [%d]\n", number[i], status[i] == 'T' ? "Stopped" : "Running", names[i], pids[i]);
    }
    return;
}
void harshit_jobs(char **tokenized, int number_of_inputs, dll *list)
{
    int l = 0, a = 0, v = 0;
    for (int x = 1; x < number_of_inputs; x++)
    {
        int f = 0;
        if (strcmp(tokenized[x], "-rs") == 0)
        {
            l = 1;
            a = 1;
            f++;
            continue;
        }
        if (strcmp(tokenized[x], "-sr") == 0)
        {
            l = 1;
            a = 1;
            f++;
            continue;
        }
        if (strcmp(tokenized[x], "-s") == 0)
        {
            l = 1;
            f++;
            continue;
        }
        if (strcmp(tokenized[x], "-r") == 0)
        {
            a = 1;
            f++;
            continue;
        }
        if (tokenized[x][0] == '-' && f == 0)
        {
            printf("Error! Incorrect flag.\n");
            v++;
            break;
        }
    }
    if (v == 1)
    {
        return;
    }
    if (number_of_inputs != 1 + l + a)
    {
        printf("Error! Invalid input\n");
        return;
    }
    if (l == 0 && a == 0)
    {
        l++;
        a++;
    }
    jobs_call(list, l, a);
}