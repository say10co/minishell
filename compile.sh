!#/bin/bash

rm -f minishell
clear 
gcc -Wall -Werror -Wextra src/main.c src/pipe_state.c src/parse_utils.c -L./libft -lft  -lreadline -o minishell
./minishell
