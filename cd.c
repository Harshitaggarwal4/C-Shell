#include "cd.h"
#include "headers.h"
int cd_call(char *input, char *path_to_home, char *prev_directory)
{
    char cwd[PATH_MAX];
    getcwd(cwd, sizeof(cwd));
    char prev_path_to_dir[PATH_MAX];
    getcwd(prev_path_to_dir, sizeof(prev_path_to_dir));
    if (strlen(input) == 0)
    {
        int check = chdir(path_to_home);
        if (check == -1)
        {
            return -1;
        }
        strcpy(prev_directory, cwd);
        return 1;
    }
    if (strcmp(input, "/") == 0)
    {
        int check = chdir(path_to_home);
        char path[PATH_MAX];
        strcpy(path, path_to_home);
        for (int v = 0; v < 100; v++)
        {
            strcat(path, "/..");
            chdir(path);
        }
        if (check == -1)
        {
            return -1;
        }
        strcpy(prev_directory, cwd);
        return 1;
    }
    else if (strcmp(input, "-") == 0)
    {
        if (prev_directory[0] == '\0')
        {
            return -2;
        }
        int check = chdir(prev_directory);
        if (check == -1)
        {
            return -1;
        }
        strcpy(prev_directory, cwd);
        return 1;
    }
    int i = 0;
    for (int x = 0; x < strlen(input) + 1; x++)
    {
        if (input[x] == '~' && (input[x + 1] == '\0' || input[x + 1] == '/') && (x == 0 || input[x - 1] == '/'))
        {
            int check;
            if (x != 0)
            {
                input[x] = '\0';
                check = chdir(input);
                if (check == -1)
                {
                    return -1;
                }
            }
            check = chdir(path_to_home);
            if (check == -1)
            {
                return -1;
            }
            if (input[x + 1] == '\0' || (input[x + 2] == '\0'))
            {
                int check = chdir(path_to_home);
                if (check == -1)
                {
                    return -1;
                }
                strcpy(prev_directory, cwd);
                return 1;
            }
            if (input[x + 1] == '/')
            {
                i = x + 2;
            }
            else
            {
                i = x + 1;
            }
        }
    }
    if (input[i] == '/')
    {
        i++;
    }
    getcwd(cwd, sizeof(cwd));
    strcat(cwd, "/");
    strcat(cwd, &input[i]);
    int check = chdir(cwd);
    if (check == -1)
    {
        return -1;
    }
    strcpy(prev_directory, prev_path_to_dir);
    return 1;
}
int harshit_cd(int number_of_inputs, char **tokenized, char *path_to_home, char *prev_directory)
{
    if (number_of_inputs > 2)
    {
        printf("Error! Extra arguments\n");
        return -1;
    }
    int flag = cd_call(tokenized[1], path_to_home, prev_directory);
    if (flag == -1)
    {
        char cwd[PATH_MAX];
        getcwd(cwd, sizeof(cwd));
        char temp[1000];
        cd_call("/", path_to_home, temp);
        int check = cd_call(tokenized[1], path_to_home, temp);
        if (check == -1)
        {
            char temp[1000];
            cd_call(cwd, path_to_home, temp);
            printf("Error! Check if the directory exists.\n");
            return -1;
        }
        else
        {
            strcpy(prev_directory, cwd);
        }
    }
    if (flag == -2)
    {
        printf("Error! No previous directory.\n");
        return -1;
    }
    return 1;
}