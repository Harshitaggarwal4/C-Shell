#ifndef __history__
#define __history__
void harshit_history(int number_of_inputs, int number_of_history_stored, char **tokenized, char **history);
void history_input(char **history, int *number_of_history_stored);
void history_output(char **history, int *number_of_history_stored);
#endif