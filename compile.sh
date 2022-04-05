!#/bin/bash

rm -f minishell
clear 
gcc -Wall -Werror -Wextra src/main.c src/pipe_state.c src/parse_utils.c src/lexer.c src/parser.c my_split_.c -L./libft -lft  -lreadline -o minishell
./minishell
