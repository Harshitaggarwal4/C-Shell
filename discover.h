#ifndef __discover__
#define __discover__
void harshit_discover(int number_of_inputs, char **tokenized);
int discover_call(int directory, int file, char **tokenized, int d, int f, char *path_to_home);
int discover(char **path_to_directories, char *file_to_be_found, int file, int d, int f, int *number_of_directories, int b, char *path_to_home);
void printfilespresent(char *directory, int d, int f, char **path_to_directories, char *file_to_be_found, int file, int *number_of_directories, char *path_to_home);
#endif