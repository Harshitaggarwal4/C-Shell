#include "discover.h"
#include "cd.h"
#include "headers.h"
void printfilespresent(char *directory, int d, int f, char **path_to_directories, char *file_to_be_found, int file, int *number_of_directories, char *path_to_home)
{
    struct stat fileStat;
    stat(directory, &fileStat);
    char cwd[PATH_MAX];
    getcwd(cwd, sizeof(cwd));
    strcat(cwd, "/");
    strcat(cwd, directory);
    if (S_ISDIR(fileStat.st_mode))
    {
        strcpy(path_to_directories[*number_of_directories], cwd);
        (*number_of_directories)++;
        if ((d == 0 && f == 0) || (d == 1))
        {
            if (file == 0)
            {
                if (strncmp(cwd, path_to_home, strlen(path_to_home)) != 0)
                {
                    printf("%s\n", cwd);
                }
                else
                {
                    printf(".%s\n", &cwd[strlen(path_to_home)]);
                }
            }
            else if (strcmp(file_to_be_found, directory) == 0)
            {
                if (strncmp(cwd, path_to_home, strlen(path_to_home)) != 0)
                {
                    printf("%s\n", cwd);
                }
                else
                {
                    printf(".%s\n", &cwd[strlen(path_to_home)]);
                }
            }
        }
    }
    else
    {
        if ((f == 0 && d == 0) || (f == 1))
        {
            if (file == 0)
            {
                if (strncmp(cwd, path_to_home, strlen(path_to_home)) != 0)
                {
                    printf("%s\n", cwd);
                }
                else
                {
                    printf(".%s\n", &cwd[strlen(path_to_home)]);
                }
            }
            else if (strcmp(file_to_be_found, directory) == 0)
            {
                if (strncmp(cwd, path_to_home, strlen(path_to_home)) != 0)
                {
                    printf("%s\n", cwd);
                }
                else
                {
                    printf(".%s\n", &cwd[strlen(path_to_home)]);
                }
            }
        }
    }
}
int discover(char **path_to_directories, char *file_to_be_found, int file, int d, int f, int *number_of_directories, int b, char *path_to_home)
{
    struct dirent *dirent_pointer;
    char cwd[PATH_MAX];
    getcwd(cwd, sizeof(cwd));
    DIR *dh = opendir(cwd);
    if (dh == NULL)
    {
        return -1;
    }
    dirent_pointer = readdir(dh);
    while (dirent_pointer != NULL)
    {
        if (dirent_pointer->d_name[0] == '.')
        {
            dirent_pointer = readdir(dh);
            continue;
        }
        printfilespresent(dirent_pointer->d_name, d, f, path_to_directories, file_to_be_found, file, number_of_directories, path_to_home);
        dirent_pointer = readdir(dh);
    }
    return 1;
}
int discover_call(int directory, int file, char **tokenized, int d, int f, char *path_to_home)
{
    char **path_to_directories = (char **)malloc(__SIZEOF_POINTER__ * 10000);
    for (int v = 0; v < 10000; v++)
    {
        path_to_directories[v] = (char *)malloc(sizeof(char) * 100000);
    }
    char file_to_be_found[1000];
    char original_cd[1000];
    getcwd(original_cd, sizeof(original_cd));
    char cwd[PATH_MAX] = "\0";
    if (directory != 0)
    {
        char temp[1000];
        harshit_cd(2, &tokenized[directory - 1], path_to_home, temp);
    }
    getcwd(cwd, sizeof(cwd));
    strcpy(path_to_directories[0], cwd);
    if (file == 0)
    {
        strcpy(file_to_be_found, "\0");
    }
    else
    {
        strcpy(file_to_be_found, &tokenized[file][1]);
        file_to_be_found[strlen(file_to_be_found) - 1] = '\0';
    }
    getcwd(cwd, sizeof(cwd));
    int name = 0;
    for (int m = strlen(cwd) - 1; m > -1; m--)
    {
        if (cwd[m] == '/')
        {
            name = m + 1;
            break;
        }
    }
    if ((d == 0 && f == 0) || (d == 1))
    {
        if (file == 0)
        {
            if (strncmp(cwd, path_to_home, strlen(path_to_home)) != 0)
            {
                printf("%s\n", cwd);
            }
            else
            {
                printf(".%s\n", &cwd[strlen(path_to_home)]);
            }
        }
        else if (strcmp(file_to_be_found, &cwd[name]) == 0)
        {
            if (strncmp(cwd, path_to_home, strlen(path_to_home)) != 0)
            {
                printf("%s\n", cwd);
            }
            else
            {
                printf(".%s\n", &cwd[strlen(path_to_home)]);
            }
        }
    }
    int number_of_directories = 1;
    int b = 0;
    while (number_of_directories != b)
    {
        char temp[1000];
        cd_call("/", path_to_home, temp);
        cd_call(path_to_directories[b], path_to_home, temp);
        discover(path_to_directories, file_to_be_found, file, d, f, &number_of_directories, b, path_to_home);
        b++;
    }
    char temp[1000];
    cd_call("/", path_to_home, temp);
    cd_call(original_cd, path_to_home, temp);
}
void harshit_discover(int number_of_inputs, char **tokenized)
{
    int d = 0, f = 0;
    for (int x = 1; x < number_of_inputs; x++)
    {
        int q = 0;
        if (strcmp(tokenized[x], "-df") == 0)
        {
            d = 1;
            f = 1;
            q++;
            continue;
        }
        if (strcmp(tokenized[x], "-fd") == 0)
        {
            d = 1;
            f = 1;
            q++;
            continue;
        }
        if (strcmp(tokenized[x], "-d") == 0)
        {
            d = 1;
            q++;
            continue;
        }
        if (strcmp(tokenized[x], "-f") == 0)
        {
            f = 1;
            q++;
            continue;
        }
        if (tokenized[x][0] == '-' && q == 0)
        {
            printf("Error! Incorrect flag.\n");
            return;
        }
    }
    char path_to_home[PATH_MAX];
    getcwd(path_to_home, sizeof(path_to_home));
    int file = 0;
    int directory = 0;
    // if (number_of_inputs != 1)
    // {
    //     if (tokenized[1][0] != '-')
    //     {
    //         struct stat fileStat;
    //         stat(tokenized[1], &fileStat);
    //         if (!S_ISDIR(fileStat.st_mode))
    //         {
    //             file = 1;
    //             if (number_of_inputs > 2)
    //             {
    //                 printf("Error! Extra arguments.\n");
    //                 return;
    //             }
    //         }
    //         else
    //         {
    //             directory = 1;
    //             for (int x = 2; x < number_of_inputs - 1; x++)
    //             {
    //                 if (tokenized[x][0] != '-')
    //                 {
    //                     printf("Error! Invalid arguments.\n");
    //                     return;
    //                 }
    //             }
    //             if (tokenized[number_of_inputs - 1][0] != '-')
    //             {
    //                 if (number_of_inputs != 2)
    //                 {
    //                     file = number_of_inputs - 1;
    //                 }
    //             }
    //         }
    //     }
    //     else
    //     {
    //         for (int x = 2; x < number_of_inputs - 1; x++)
    //         {
    //             if (tokenized[x][0] != '-')
    //             {
    //                 printf("Error! Invalid arguments.\n");
    //                 return;
    //             }
    //         }
    //         if (tokenized[number_of_inputs - 1][0] != '-')
    //         {
    //             file = number_of_inputs - 1;
    //         }
    //     }
    // }
    if (tokenized[1][0] == '-' || tokenized[1][0] == '"')
    {
        for (int i = 1; i < number_of_inputs; i++)
        {
            if (tokenized[i][0] == '-')
            {
                continue;
            }
            else if (tokenized[i][0] != '"')
            {
                printf("Error! Invalid arguments.\n");
                return;
            }
            else
            {
                if (i != number_of_inputs - 1)
                {
                    printf("Error! Invalid arguments.\n");
                    return;
                }
                else
                {
                    if (tokenized[i][strlen(tokenized[i]) - 1] != '"')
                    {
                        printf("Error! Invalid arguments.\n");
                        return;
                    }
                    else
                    {
                        file = i;
                    }
                }
            }
        }
    }
    else
    {
        directory = 1;
        for (int i = 2; i < number_of_inputs; i++)
        {
            if (tokenized[i][0] == '-')
            {
                continue;
            }
            else if (tokenized[i][0] != '"')
            {
                printf("Error! Invalid arguments.\n");
                return;
            }
            else
            {
                if (i != number_of_inputs - 1)
                {
                    printf("Error! Invalid arguments.\n");
                    return;
                }
                else
                {
                    if (tokenized[i][strlen(tokenized[i]) - 1] != '"')
                    {
                        printf("Error! Invalid arguments.\n");
                        return;
                    }
                    else
                    {
                        file = i;
                    }
                }
            }
        }
    }
    discover_call(directory, file, tokenized, d, f, path_to_home);
    return;
}