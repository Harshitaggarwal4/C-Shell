#ifndef __jobs__
#define __jobs__
#include "my_dll.h"
#include "node.h"
void jobs_call(dll *list, int l, int a);
void bubblesort(char **names, int n, int number[], int pids[], char status[]);
void swap_all(char *naa, char *nab, int *na, int *nb, int *pa, int *pb, char *sa, char *sb);
void harshit_jobs(char **tokenized, int number_of_inputs, dll *list);
#endif