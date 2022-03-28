!#/bin/bash

clear
gcc -Wall -Werror -Wextra main.c -L./libft -lft  -lreadline -o minishell
./minishell
