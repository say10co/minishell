#include "libft/libft.h"
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>

#define D_QUOTE '"'
#define S_QUOTE '\''
#define L_ARROW '<'
#define R_ARROW '>'
#define PIPE	'|'
#define SPACE	' '

typedef struct s_token t_token;
typedef struct s_token_list t_token_list;

struct s_token
{
	char *data;
	int	type;
	bool is_key;
	bool found_space;
	t_token	*next_token;
};

struct s_token_list
{
	t_token *all;
	int	nb_tokens;

};
