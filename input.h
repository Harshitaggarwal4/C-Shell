#ifndef __input__
#define __input__
#include "my_dll.h"
#include "node.h"
int input_and_history(char *input, int *number_of_history_stored, char **history);
int raw_input(char *input, int *number_of_history_stored, char **history, char *buf, char *hostname, char *path_to_home, int size_of_path_to_home, char *print_to_terminal, dll *list);
void enableRawMode();
void disableRawMode();
void die(const char *s);
#endif