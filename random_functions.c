#include "random_functions.h"
#include "headers.h"
void swap(char *a, char *b)
{
    char temp[10000];
    strcpy(temp, a);
    strcpy(a, b);
    strcpy(b, temp);
    return;
}