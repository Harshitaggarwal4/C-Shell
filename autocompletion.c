#include "autocompletion.h"
#include "display.h"
#include "headers.h"
int alphasorting(const struct dirent **a, const struct dirent **b)
{
    return strcasecmp((*a)->d_name, (*b)->d_name);
}
int auto_printfilecharacteristics(char *input, char **to_be_printed, int count)
{
    struct stat fileStat;
    int h = stat(input, &fileStat);
    if (h == -1)
    {
        return -1;
    }
    strcpy(to_be_printed[count], input);
    if (S_ISDIR(fileStat.st_mode))
    {
        strcat(to_be_printed[count], "/");
    }
    else
    {
        strcat(to_be_printed[count], " ");
    }
    return 0;
}
char *harshit_autocompletion(char *inputt, char *buf, char *hostname, char *path_to_home, int size_of_path_to_home, char *print_to_terminal, int *done)
{
    char input[1000];
    strcpy(input, inputt);
    char *token;
    char t[2] = " ";
    char temp[1000];
    token = strtok(input, t);
    while (token != NULL)
    {
        strcpy(temp, token);
        token = strtok(NULL, t);
    }
    strcpy(input, temp);
    int count = 0;
    char **to_be_printed = (char **)malloc(__SIZEOF_POINTER__ * 1000);
    for (int i = 0; i < 1000; i++)
    {
        to_be_printed[i] = (char *)malloc(sizeof(char) * 1000);
    }
    int no_of_files = 0;
    struct dirent **file_list_temp;
    char cwd[PATH_MAX];
    getcwd(cwd, sizeof(cwd));
    no_of_files = scandir(cwd, &file_list_temp, NULL, alphasorting);
    for (int h = 0; h < no_of_files; h++)
    {
        if (file_list_temp[h]->d_name[0] == '.')
        {
            continue;
        }
        if (strncmp(input, file_list_temp[h]->d_name, strlen(input)) == 0)
        {
            auto_printfilecharacteristics(file_list_temp[h]->d_name, to_be_printed, count);
            count++;
        }
    }
    if (count == 0)
    {
        printf("\n");
        harshit_display(buf, hostname, path_to_home, size_of_path_to_home, print_to_terminal);
        (*done) = 1;
        return NULL;
    }
    if (count == 1)
    {
        return &to_be_printed[0][strlen(input)];
    }
    else
    {
        (*done) = 1;
        printf("\n");
        int min = 1000;
        for (int i = 0; i < count; i++)
        {
            int c = 0;
            for (int j = 0; j < strlen(to_be_printed[0]); j++)
            {
                if (to_be_printed[0][j] == to_be_printed[i][j])
                {
                    c++;
                }
                else
                {
                    break;
                }
            }
            min = min < c ? min : c;
            printf("%s\n", to_be_printed[i]);
        }
        harshit_display(buf, hostname, path_to_home, size_of_path_to_home, print_to_terminal);
        char *print = (char *)malloc(sizeof(char) * 1000);
        strcpy(print, to_be_printed[0]);
        print[min] = '\0';
        return &print[strlen(input)];
    }
}