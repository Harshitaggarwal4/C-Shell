#ifndef __ls__
#define __ls__
#include "headers.h"
int alphasort(const struct dirent **a, const struct dirent **b);
int printfilecharacteristics(char *input, int l, int a, int file, char *path_to_home, char *tokenized);
int ls_call(char *input, int l, int a, int file, char *path_to_home, char *tokenized);
void harshit_ls(int number_of_inputs, char **tokenized, char *prev_directory, char *path_to_home);
void count_total(char *input, int *total);
#endif