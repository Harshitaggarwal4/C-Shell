#include "display.h"
#include "headers.h"
void harshit_display(char *buf, char *hostname, char *path_to_home, int size_of_path_to_home, char *print_to_terminal)
{
    printf("<");
    printf("\033[0;32m");
    char cwd[PATH_MAX];
    getcwd(cwd, sizeof(cwd));
    printf("%s@%s", buf, hostname);
    printf("\033[0m");
    printf(":");
    printf("\033[0;34m");
    if (strncmp(cwd, path_to_home, strlen(path_to_home)) != 0)
    {
        printf("%s", cwd);
    }
    else
    {
        printf("~%s", &cwd[size_of_path_to_home]);
    }
    printf("%s", print_to_terminal);
    printf("\033[0m");
    printf("> ");
    print_to_terminal[0] = '\0';
}