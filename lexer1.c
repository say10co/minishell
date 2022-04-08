#include "libft/libft.h"
#include <stdio.h>
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
	t_token	*next_token;
};

struct s_token_list
{
	t_token *all;
	int	nb_tokens;

};

int	is_keyword(char c)
{
	if (c == L_ARROW || c == R_ARROW || c == PIPE)
		return (1);
	return (0);
}

void get_data(char *buffer, int i, t_token **t, int *start)
{
	if (*start == 0)
	{
		(*t)->next_token = (t_token *)malloc(sizeof(t_token));
		(*t) = (*t)->next_token;
		(*t)->next_token = NULL;
	}
	buffer[i] = 0;
	(*t)->data = ft_strdup(buffer);
	*start = 0;

}

void get_tokens(t_token_list *lst, char *text, size_t size)
{
	t_token	*token;
	char	*buffer;
	char	quote;
	int	i;
	int	j;
	int	start;


	if (!text)
		return ;
	lst->all = (t_token *)malloc(sizeof(t_token));
	lst->all->next_token = NULL;
	lst->all->data = NULL;
	buffer = (char *)malloc(sizeof(char) * size);
	lst->nb_tokens = 0;
	quote = 0;
	i = 0;
	j = 0;
	start = 1;
	token = lst->all;
	while (j <= size)
	{
		if (!quote)
		{
			if (*text == D_QUOTE || *text == S_QUOTE)
			{
				if (i && 0)
				{
					get_data(buffer, i, &token, &start);
					i = 0;
					lst->nb_tokens += 1;
				}
				quote = *text;
				buffer[i++] = *text;
			}
			else if (*text == ' ' && i)
			{
				get_data(buffer, i, &token, &start);
				lst->nb_tokens += 1;
				i = 0;
			}
			else if (is_keyword(*text) || !*text)
			{
				if (i)
				{
					get_data(buffer, i, &token, &start);
					lst->nb_tokens += 1;
				}
				if (*text)
				{
					buffer[0] = *text;
					get_data(buffer, 1, &token, &start);
				}
				i = 0;
			}
			else if (!is_keyword(*text) && *text != ' ')
				buffer[i++] = *text;
		}
		else
		{
			buffer[i++] = *text;
			//if (*text == D_QUOTE || *text == S_QUOTE)
			if (*text == quote)
			{
				quote = 0;
				get_data(buffer, i, &token, &start);
				lst->nb_tokens += 1;
				i = 0;
			}
		}
		text++;
		j++;
	}
}

int main()
{
	char *t_cmd;
	t_token_list token_lst;
	t_token *t;

	while (1)
	{
		t_cmd = readline("$ ");
		add_history(t_cmd);
		get_tokens(&token_lst, t_cmd, ft_strlen(t_cmd));
		t  = token_lst.all;
		while (t)
		{
			printf("--/-: [%s] {%p}\n", t->data, t->next_token);
			t = t->next_token;
		}

	}
}
