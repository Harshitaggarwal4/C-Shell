#include "ls.h"
#include "cd.h"
#include "headers.h"
void count_total(char *input, int *total)
{
    struct stat fileStat;
    stat(input, &fileStat);
    (*total) += fileStat.st_blocks;
}
int alphasort(const struct dirent **a, const struct dirent **b)
{
    char namea[1000], nameb[1000], na[1000], nb[1000];
    strcpy(namea, (*a)->d_name);
    strcpy(nameb, (*b)->d_name);
    strcpy(na, (*a)->d_name);
    strcpy(nb, (*b)->d_name);
    int j = 0, flag = 0;
    for (int i = 0; i < strlen(na); i++)
    {
        na[j] = (((*a)->d_name)[i]);
        if (na[j] == '.' && flag == 0)
        {
            continue;
        }
        flag = 1;
        j++;
    }
    na[j] = '\0';
    j = 0;
    flag = 0;
    for (int i = 0; i < strlen(nb); i++)
    {
        nb[j] = (((*b)->d_name)[i]);
        if (nb[j] == '.' && flag == 0)
        {
            continue;
        }
        flag = 1;
        j++;
    }
    nb[j] = '\0';
    j = 0;
    flag = 0;
    for (int i = 0; i < strlen(namea); i++)
    {
        namea[j] = tolower(((*a)->d_name)[i]);
        if (namea[j] == '.' && flag == 0)
        {
            continue;
        }
        flag = 1;
        j++;
    }
    namea[j] = '\0';
    j = 0;
    flag = 0;
    for (int i = 0; i < strlen(nameb); i++)
    {
        nameb[j] = tolower(((*b)->d_name)[i]);
        if (nameb[j] == '.' && flag == 0)
        {
            continue;
        }
        flag = 1;
        j++;
    }
    nameb[j] = '\0';
    if (strcmp(namea, nameb) != 0)
    {
        return strcmp(namea, nameb);
    }
    else
    {
        if (strcmp(na, nb) != 0)
        {
            return -1 * strcmp(na, nb);
        }
        else
        {
            return strcmp((*a)->d_name, (*b)->d_name);
        }
    }
}
int printfilecharacteristics(char *input, int l, int a, int file, char *path_to_home, char *tokenized)
{
    struct stat fileStat;
    int h = stat(input, &fileStat);
    if (h == -1)
    {
        return -1;
    }
    if (l == 1)
    {
        if (S_ISDIR(fileStat.st_mode))
        {
            printf("d");
        }
        else
        {
            printf("-");
        }
        if ((fileStat.st_mode & S_IRUSR))
        {
            printf("r");
        }
        else
        {
            printf("-");
        }
        if (fileStat.st_mode & S_IWUSR)
        {
            printf("w");
        }
        else
        {
            printf("-");
        }
        if (fileStat.st_mode & S_IXUSR)
        {
            printf("x");
        }
        else
        {
            printf("-");
        }
        if (fileStat.st_mode & S_IRGRP)
        {
            printf("r");
        }
        else
        {
            printf("-");
        }
        if (fileStat.st_mode & S_IWGRP)
        {
            printf("w");
        }
        else
        {
            printf("-");
        }
        if (fileStat.st_mode & S_IXGRP)
        {
            printf("x");
        }
        else
        {
            printf("-");
        }
        if (fileStat.st_mode & S_IROTH)
        {
            printf("r");
        }
        else
        {
            printf("-");
        }
        if (fileStat.st_mode & S_IWOTH)
        {
            printf("w");
        }
        else
        {
            printf("-");
        }
        if (fileStat.st_mode & S_IXOTH)
        {
            printf("x ");
        }
        else
        {
            printf("- ");
        }
        printf("%ld ", fileStat.st_nlink);
        struct passwd *pws;
        pws = getpwuid(fileStat.st_uid);
        printf("%s ", pws->pw_name);
        pws = getpwuid(fileStat.st_gid);
        printf("%s ", pws->pw_name);
        printf("%ld ", fileStat.st_size);
        char time_of_file[10000];
        strcpy(time_of_file, ctime(&fileStat.st_mtime));
        time_of_file[strlen(time_of_file) - 9] = '\0';
        printf("%s ", time_of_file);
    }
    if (S_ISDIR(fileStat.st_mode))
    {
        printf("\033[0;34m");
        printf("%s  ", input);
        printf("\033[0m");
    }
    else if (fileStat.st_mode & S_IXUSR || fileStat.st_mode & S_IXGRP || fileStat.st_mode & S_IXOTH)
    {
        if (file == 0)
        {
            printf("\033[0;32m");
            printf("%s  ", tokenized);
            printf("\033[0m");
        }
        else
        {
            printf("\033[0;32m");
            printf("%s  ", input);
            printf("\033[0m");
        }
    }
    else
    {
        if (file == 0)
        {
            printf("%s  ", tokenized);
        }
        else
        {
            printf("%s  ", input);
        }
    }
    if (l == 1)
    {
        printf("\n");
    }
    return 0;
}
int ls_call(char *input, int l, int a, int file, char *path_to_home, char *tokenized)
{
    if (file == 0)
    {
        int h = printfilecharacteristics(input, l, a, file, path_to_home, tokenized);
        if (h == -1)
        {
            return -1;
        }
        if (l != 1)
        {
            printf("\n");
        }
        return 1;
    }
    int total = 0;
    int no_of_files = 0;
    struct dirent **file_list_temp;
    no_of_files = scandir(input, &file_list_temp, NULL, alphasort);
    if (l == 1)
    {
        for (int h = 0; h < no_of_files; h++)
        {
            if (a == 0 && file_list_temp[h]->d_name[0] == '.')
            {
                continue;
            }
            count_total(file_list_temp[h]->d_name, &total);
        }
        printf("total %d\n", total / 2);
    }
    for (int h = 0; h < no_of_files; h++)
    {
        if (a == 0 && file_list_temp[h]->d_name[0] == '.')
        {
            continue;
        }
        printfilecharacteristics(file_list_temp[h]->d_name, l, a, 1, path_to_home, tokenized);
    }
    if (l != 1)
    {
        printf("\n");
    }
    return 1;
}
void harshit_ls(int number_of_inputs, char **tokenized, char *prev_directory, char *path_to_home)
{
    int l = 0, a = 0, v = 0;
    for (int x = 1; x < number_of_inputs; x++)
    {
        int f = 0;
        if (strcmp(tokenized[x], "-la") == 0)
        {
            l = 1;
            a = 1;
            f++;
            continue;
        }
        if (strcmp(tokenized[x], "-al") == 0)
        {
            l = 1;
            a = 1;
            f++;
            continue;
        }
        if (strcmp(tokenized[x], "-l") == 0)
        {
            l = 1;
            f++;
            continue;
        }
        if (strcmp(tokenized[x], "-a") == 0)
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
    int flag = 0;
    for (int x = 1; x < number_of_inputs; x++)
    {
        if (tokenized[x][0] != '-')
        {
            flag++;
            char temp[1000];
            char current_saved[PATH_MAX];
            getcwd(current_saved, sizeof(current_saved));
            int checkings = cd_call(tokenized[x], path_to_home, temp);
            if (checkings == -1)
            {
                char cwd[PATH_MAX];
                getcwd(cwd, sizeof(cwd));
                char temp[1000];
                cd_call("/", path_to_home, temp);
                int check = cd_call(tokenized[1], path_to_home, temp);
                if (check == -1)
                {
                    char to_output[1000];
                    strcpy(to_output, tokenized[x]);
                    cd_call(cwd, path_to_home, temp);
                    int index = 0;
                    for (int h = strlen(tokenized[x]) - 2; h > -1; h--)
                    {
                        if (tokenized[x][h] == '/')
                        {
                            index = h + 1;
                            break;
                        }
                    }
                    char name_of_file[1000];
                    strcpy(name_of_file, &tokenized[x][index]);
                    if (name_of_file[strlen(name_of_file) - 1] == '/')
                    {
                        name_of_file[strlen(name_of_file) - 1] = '\0';
                    }
                    tokenized[x][index] = '\0';
                    int h = harshit_cd(2, &tokenized[x - 1], path_to_home, temp);
                    if (h == -1)
                    {
                        chdir(current_saved);
                        continue;
                    }
                    int har = ls_call(name_of_file, l, a, 0, path_to_home, to_output);
                    if (har == -1)
                    {
                        printf("Error! Check if the directory exists.\n");
                    }
                    chdir(current_saved);
                    continue;
                }
            }
            chdir(current_saved);
            int checking = harshit_cd(2, &tokenized[x - 1], path_to_home, temp);
            if (checking == -1)
            {
                printf("Error! Please check if the directory exists.\n");
                chdir(current_saved);
                continue;
            }
            char current[PATH_MAX];
            getcwd(current, sizeof(current));
            int check = ls_call(current, l, a, 1, path_to_home, temp);
            if (check == -1)
            {
                printf("Error! Please check if the directory exists.\n");
            }
            chdir(current_saved);
        }
    }
    if (flag == 0)
    {
        char current_saved[PATH_MAX];
        getcwd(current_saved, sizeof(current_saved));
        char temp[1000];
        int check = ls_call(current_saved, l, a, 1, path_to_home, temp);
        if (check == -1)
        {
            printf("Error! Please check if the directory exists.\n");
        }
    }
    return;
}