#ifndef __tokenize__
#define __tokenize__
void harshit_tokenize_for_semicolon(char *tokenize, char *input, char *t, char **tokenize_for_semicolon, int *number_of_inputs_for_semicolon);
void harshit_tokenize_for_spaces(char *token, char **tokenize_for_semicolon, int z, char *s, char **tokenized, int *number_of_inputs);
void harshit_tokenize_for_and(char *token_for_and, char **tokenize_for_semicolon, int z, char *and, char **tokenize_for_and, int *number_of_inputs_for_and);
int harshit_tokenize_for_input_output(char *token, char *tokenized, char **tokenize, int *output, int *input_backup);
void harshit_tokenize_for_pipe(char *token, char **tokenize_for_pipe, int *number, char *input);
#endif