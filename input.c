#include "input.h"
#include "random_functions.h"
#include "headers.h"
#include "autocompletion.h"
#include "my_dll.h"
#include "node.h"
int input_and_history(char *input, int *number_of_history_stored, char **history)
{
    int i = 0, first_char = 0, space = 0;
    char inp[1000];
    int j = 0;
    strcpy(inp, input);
    while (1)
    {
        char a;
        a = inp[j];
        j++;
        if (first_char == 0)
        {
            if (a == ' ' || a == '\t')
            {
                space++;
                continue;
            }
            else
            {
                first_char++;
            }
        }
        if (a == '\n')
        {
            input[i] = '\0';
            break;
        }
        input[i] = a;
        i++;
    }
    if (strcmp(input, "") == 0)
    {
        return 1;
    }
    if (space == 0)
    {
        if ((*number_of_history_stored) == 0)
        {
            strcpy(history[0], input);
            (*number_of_history_stored)++;
        }
        else if (strcmp(history[0], input) != 0)
        {
            for (int d = 1; d < 20; d++)
            {
                swap(history[0], history[d]);
            }
            strcpy(history[0], input);
            if ((*number_of_history_stored) != 20)
            {
                (*number_of_history_stored)++;
            }
        }
    }
}
void die(const char *s)
{
    perror(s);
    exit(1);
}
struct termios orig_termios;
void disableRawMode()
{
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios) == -1)
        die("tcsetattr");
}
void enableRawMode()
{
    if (tcgetattr(STDIN_FILENO, &orig_termios) == -1)
        die("tcgetattr");
    atexit(disableRawMode);
    struct termios raw = orig_termios;
    raw.c_lflag &= ~(ICANON | ECHO);
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1)
        die("tcsetattr");
}
int raw_input(char *input, int *number_of_history_stored, char **history, char *buf, char *hostname, char *path_to_home, int size_of_path_to_home, char *print_to_terminal, dll *list)
{
    char c;
    setbuf(stdout, NULL);
    enableRawMode();
    memset(input, '\0', 1000);
    int pt = 0;
    while (read(STDIN_FILENO, &c, 1) == 1)
    {
        if (iscntrl(c))
        {
            if (c == 10)
                break;
            else if (c == 27)
            {
                char buf[3];
                buf[2] = 0;
                if (read(STDIN_FILENO, buf, 2) == 2)
                { // length of escape code
                    printf("\rarrow key: %s", buf);
                }
            }
            else if (c == 127)
            { // backspace
                if (pt > 0)
                {
                    if (input[pt - 1] == 9)
                    {
                        for (int i = 0; i < 7; i++)
                        {
                            printf("\b");
                        }
                    }
                    input[--pt] = '\0';
                    printf("\b \b");
                }
            }
            else if (c == 9)
            { // TAB character
                char *temp;
                int done = 0;
                temp = harshit_autocompletion(input, buf, hostname, path_to_home, size_of_path_to_home, print_to_terminal, &done);
                if (done == 1)
                {
                    printf("%s", input);
                }
                if (temp != NULL)
                {
                    for (int i = 0; i < strlen(temp); i++)
                    {
                        input[pt++] = temp[i];
                        printf("%c", temp[i]);
                    }
                }
            }
            else if (c == 4)
            {
                delete_all_background(list);
                exit(0);
            }
            else
            {
                printf("%d\n", c);
            }
        }
        else
        {
            input[pt++] = c;
            printf("%c", c);
        }
    }
    printf("\n");
    disableRawMode();
    return input_and_history(input, number_of_history_stored, history);
}