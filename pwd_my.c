#include "pwd_my.h"
#include "headers.h"
int pwd_call(int size)
{
    char cwd[PATH_MAX];
    getcwd(cwd, sizeof(cwd));
    printf("%s\n", cwd);
    return 1;
}
void harshit_pwd(int number_of_inputs, int size_of_path_to_home)
{
    if (number_of_inputs != 1)
    {
        printf("Error! Extra arguments\n");
        return;
    }
    pwd_call(size_of_path_to_home);
    return;
}