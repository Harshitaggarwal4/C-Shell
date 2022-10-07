#ifndef __autocompletion__
#define __autocompletion__
#include "headers.h"
int alphasorting(const struct dirent **a, const struct dirent **b);
int auto_printfilecharacteristics(char *input, char **to_be_printed, int count);
char *harshit_autocompletion(char *input, char *buf, char *hostname, char *path_to_home, int size_of_path_to_home, char *print_to_terminal, int *done);
#endif