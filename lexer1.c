#include "lexer.h"
#include "includes/includes.h"
#include "libft/libft.h"

int	is_keyword(char c)
{
	if (c == L_ARROW || c == R_ARROW || c == PIPE)
		return (1);
	return (0);
}

bool merge(char c1, char c2, t_token *t)
{
	char *both;

	if (c1 == c2 && !(t->found_space))
	{
		printf("c1 : %c c2 : %c", c1, c2);
		if (c1 == '<')
			both = ft_strdup("<<");
		else if (c1 == '>')
			both = ft_strdup(">>");
		else
			return (0);
		free(t->data);
		t->data = both;
		return (1);
	}
	return (0);
}

void get_data(char *buffer, int i, t_token **t, int *start)
{
	char *tmp;
	int		is_key;

	is_key = 0;
	if (i == -1)
	{
		i = 1;
		is_key = 1;
	}
	if ((*t)->is_key && is_key && merge(buffer[0], (*t)->data[0], *t))
		return ;
	if (*start == 0)
	{
		(*t)->next_token = (t_token *)malloc(sizeof(t_token));
		(*t) = (*t)->next_token;
		(*t)->is_key = is_key;
		(*t)->found_space = 0;
		(*t)->next_token = NULL;
	}
	buffer[i] = 0;
	tmp = ft_strdup(buffer);
	if (tmp[0] == '\0')
	{
		free(tmp);
		tmp = NULL;
	}
	(*t)->data = tmp;
	*start = 0;


}

void __init_list(t_token_list *lst)
{
	lst->all = (t_token *)malloc(sizeof(t_token));
	lst->all->next_token = NULL;
	lst->all->data = NULL;
	lst->all->is_key = 0;
	lst->all->found_space = 0;
	lst->nb_tokens = 0;

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
	__init_list(lst);
	buffer = (char *)malloc(sizeof(char) * size);
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
			else if (*text == ' ')
			{
				if (i)
				{
					get_data(buffer, i, &token, &start);
					lst->nb_tokens += 1;
					i = 0;
				}
				else
					token->found_space = 1;
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
					get_data(buffer, -1, &token, &start);
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
	if (quote)
		get_data(buffer, 0, &token, &start);

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
		printf("out\n");
		if (n_parser(&token_lst))
			continue;
		t  = token_lst.all;
		while (t)
		{
			printf("--/-: [%s] {%p}\n", t->data, t->next_token);
			t = t->next_token;
		}

	}
}
