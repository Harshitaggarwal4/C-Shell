# Assignment 3 | Operating Systems and Networks

## Harshit Aggarwal | 2021111015

## Requirements

- GCC compiler
- Linux OS (preferably Ubuntu)

## Running Shell

From the root directory of project, run `make` followed by `./main`

## File & Functions

### main.c

    This contains the main functions which compare the input string to determine the command aand calls the respective functions.

### background.c

    This file contains the functions which manage the background processes via creating a new child and using execvp. A command is considered to be background if a `&` is found after the command.

### cd.c

    This files contains the fucntion which implement cd command. This helps you to switch between folders.

### clear.c

    This files contains the fucntion which implement clear command. This helps you to clear the shell terminal.

### discover.c

    This files contains the fucntion which implement discover command. This helps you to discover any kind of files or directories recursively in a directory you input.

### display.c

    This files contains the fucntion which displays the prompt when you start the shell.

### echo.c

    This files contains the fucntion which implement echo command. This prints the content of the given arguments.

### foreground.c

    This file contains the functions which manage the foreground processes via creating a new child and using execvp.

### history.c

    This files contains the fucntion which displays last 10 commands ran the shell terminal including the command history (which you just ran).

### input.c

    This read the input you gave as argument.

### ls.c

    This command shows the files and directory present at the directory to which your given path points.

### my_dll.c

    This is implementation of a doubly linked list.

### pinfo.c

    This file contains the fucntion which implement pinfo command. This command prints the information related to the process with the id you give as an argument.

### pwd_my.c

    This file contains the fucntion which implement pwd command. This command prints the absolute path of the directory in which you are in from the root.

### random_function.c

    This file contains swap function.

### tokenization.c

    This file contains functions which tokenize the given input for `;`, `&` and `spaces`.std

### autocompletion.c

    This file contains function which implememt autocomplete command. The file/ directory name is autocompleted for you if you press tab.

### bg.c

    This file contains functions which implememt bg command. This starts the running of a background process if it is stopped.

### fg.c

    This file contains functions which implememt fg comand. This changes background process to foreground.

### jobs.c

    This file contains functions which implemwnt jobs comand. This prints information about all of the background processes which are running.

### headers.h

    This contains all the headers to be included.

## Assumptions

    The maximum number of arguments the shell will accept is 1000 and there are upper limits to every function.
