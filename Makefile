SRC = src/initers.c src/string_operators.c src/expander_utils.c src/lex_utils.c src/builtin/unset.c src/builtin/b_env.c  src/print.c src/destructors.c  src/builtin/export.c src/builtin/utils.c src/expander.c src/parser_utils.c  src/utils.c src/lexer_utils.c src/lexer1.c src/main.c src/parser.c src/parser_one.c src/execute.c src/builtin/b_cd.c src/builtin/exec_builtin.c src/builtin/utils.c src/env.c src/builtin/pwd.c src/builtin/exit.c src/signals.c



#@cc $(FLAGS) $(OBJECTS) -lreadline -L/Users/adriouic/.brew/opt/readline/lib  -L./libft -lft $(READLINE) -fsanitize=address -o $(NAME)

GNL = get_next_line/get_next_line.c get_next_line/get_next_line_utils.c

OBJECTS = ${SRC:.c=.o} 

GNL_OBJ = ${GNL:.c=.o}

FLAGS = -Wall -Werror -Wextra


READLINE = -L./modules/readline/lib -I ./modules/readline/include

NAME = minishell

all: PRINT $(NAME)

PRINT:
	@echo  "\n\033[0;33m Compiling minishell source files" "\n\033[1;32m"

%.o: %.c
	cc $(FLAGS) -I ./modules/readline/include -c $< -o  $@

$(NAME) : $(OBJECTS) $(GNL_OBJ) LIB 
	@echo "\n\033[0;33m Linking object files Done" "\033[1;32m"
	@cc $(FLAGS) $(OBJECTS) $(GNL_OBJ) -lreadline -L/opt/homebrew/Cellar/readline/8.1.2/lib -L./libft -lft $(READLINE) -fsanitize=address  -o $(NAME)
	#@cc $(FLAGS) $(OBJECTS) -lreadline -L./libft -lft  -o $(NAME)

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
	rm -f $(OBJECTS)

fclean: clean libfclean
	rm -f $(NAME)
	rm -f ./libft/libft.a

libclean:
	make clean -C libft

libfclean: libclean
	make fclean -C libft

re: fclean all

