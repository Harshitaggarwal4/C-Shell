#ifndef __pinfo__
#define __pinfo__
#include "my_dll.h"
#include "node.h"
int pinfo_call(char *piid, int size_of_path_to_home, char *path_to_home, dll *background_processes);
void harshit_pinfo(int number_of_inputs, char **tokenized, int size_of_path_to_home, char *path_to_home, dll *background_processes);
#endif