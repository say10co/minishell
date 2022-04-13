#include "../libft/libft.h"
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>

#define D_QUOTE '"'
#define S_QUOTE '\''
#define L_ARROW '<'
#define DL_ARROW 120
#define R_ARROW '>'
#define DR_ARROW 142
#define PIPE	'|'
#define SPACE	' '

typedef struct s_token t_token;
typedef struct s_token_list t_token_list;

struct s_token
{
	char *data;
	int	type;
	int	length;
	bool is_key;
	bool found_space;
	char	quoted;
	t_token	*next_token;
};

struct s_token_list
{
	t_token *all;
	int	nb_tokens;

};

void	get_tokens(t_token_list *lst, char *text, int	size);
int		is_keyword(char c);
int		get_type(char c, int p);
bool	merge(char c1, char c2, t_token *t);
void	fill_token(t_token *t, char *buffer);
void	get_data(char *buffer, int i, t_token **t, int *start);

