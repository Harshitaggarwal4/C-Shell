#ifndef my_dll__
#define my_dll__
#include "node.h"
typedef struct my_dll
{
    node *root;
    node *last;
} dll;
void insert(dll *list, int x, char *namex, int number);
void delete (dll *list, int i);
int find(dll *list, int x, char *name_of_process, int *number);
int get_size(dll *list);
void find_max(dll *list, int *max_number_of_processes);
int find_via_process_number(dll *list, int x, char *name_of_process);
void delete_all_background(dll *list);
#endif