!#/bin/bash

clear
gcc -Wall -Werror -Wextra src/main.c -L./libft -lft  -lreadline -o minishell
./minishell
