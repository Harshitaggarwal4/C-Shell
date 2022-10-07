.PHONY: main
main:
	gcc main.c cd.c clear.c echo.c history.c ls.c pinfo.c pwd_my.c random_functions.c input.c display.c tokenization.c discover.c foreground.c background.c my_dll.c jobs.c bg.c sig.c autocompletion.c fg.c -o main

valgrind:
	gcc main.c cd.c clear.c echo.c history.c ls.c pinfo.c pwd_my.c random_functions.c input.c display.c tokenization.c discover.c foreground.c background.c my_dll.c jobs.c bg.c sig.c autocompletion.c fg.c -o main
	valgrind ./main