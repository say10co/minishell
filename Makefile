# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adriouic <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/14 14:28:34 by adriouic          #+#    #+#              #
#    Updated: 2022/05/15 16:40:30 by adriouic         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = src/destructors.c src/env.c src/execute.c src/execute_utils.c src/expander.c src/expander_utils.c src/initers.c src/lex_utils.c src/lexer.c src/lexer_utils.c src/main.c src/parser.c src/parser_one.c src/parser_utils.c  src/signals.c src/string_operators.c src/utils.c src/builtin/b_cd.c src/builtin/b_cd_utils.c src/builtin/b_env.c src/builtin/exec_builtin.c src/builtin/exit.c src/builtin/export.c src/builtin/pwd.c src/builtin/unset.c src/builtin/utils.c src/builtin/echo.c src/print.c src/file_ctl.c

GNL = get_next_line/get_next_line.c get_next_line/get_next_line_utils.c

OBJECTS = ${SRC:.c=.o} 

GNL_OBJ = ${GNL:.c=.o}

FLAGS = -Wall -Werror -Wextra

#READLINE = -L./modules/readline/lib -I ./modules/readline/include

NAME = minishell

all: PRINT LIB $(NAME)

PRINT:
	@echo  "\n\033[0;33m Compiling minishell source files" "\n\033[1;32m"

%.o: %.c
	@echo  "\n\033[0;33m Compiling minishell src"
	@echo  "\033[1;32m"
	#cc $(FLAGS) -I /Users/macplus/Developer/homebrew/Cellar/readline/8.1.2/include -c $< -o  $@
	cc $(FLAGS) -I /Users/adriouic/.brew/Cellar/readline/8.1.2/include -c $< -o  $@
	@clear

$(NAME) : $(OBJECTS) $(GNL_OBJ) 

	@cc $(FLAGS) $(OBJECTS) $(GNL_OBJ) -lreadline -L/Users/adriouic/.brew/opt/readline/lib  -L./libft -lft $(READLINE)  -o $(NAME)
	#@cc $(FLAGS) $(OBJECTS) $(GNL_OBJ) -lreadline -L/Users/macplus/Developer/homebrew/Cellar/readline/8.1.2/lib -L./libft -lft $(READLINE) -o $(NAME)

	@echo "\n\033[0;33m Linking object files Done" "\033[1;32m"
	
LIB :
	@echo  "\n\033[0;33m Compiling Libft..."
	@echo  "\033[1;32m"
	make -C ./libft 
	@echo "\n\033[0;33m Compiling Libft Bonus..."
	@echo  "\033[1;32m"
	make bonus -C ./libft 

clean: libclean
	@echo  "\n\033[0;33m Deleting Object Files..."
	@echo  "\033[0;31m"
	rm -f $(OBJECTS) $(GNL_OBJ)

fclean: clean libfclean
	rm -f $(NAME)
	rm -f ./libft/libft.a

libclean:
	make clean -C libft

libfclean: libclean
	make fclean -C libft

re: fclean all

