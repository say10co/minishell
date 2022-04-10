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
		if (c1 == '<')
			both = ft_strdup("<<");
		else if (c1 == '>')
			both = ft_strdup(">>");
		else
			return (0);
		free(t->data);
		t->data = both;
		t->length = ft_strlen(both);
		return (1);
	}
	return (0);
}

void fill_token(t_token *t, char *buffer)
{
	char *tmp;

	tmp = ft_strdup(buffer);
	if (tmp[0] == '\0')
	{
		free(tmp);
		tmp = NULL;
	}
	t->data = tmp;
	t->length = ft_strlen(tmp);
}

void get_data(char *buffer, int i, t_token **t, int *start)
{
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
		(*t)->found_space = 0;
		(*t)->next_token = NULL;
		(*t)->quoted = 0;
	}
	(*t)->is_key = is_key;
	buffer[i] = 0;
	fill_token(*t, buffer);
	*start = 0;
}

void __init_list(t_token_list *lst)
{
	lst->all = (t_token *)malloc(sizeof(t_token));
	lst->all->next_token = NULL;
	lst->all->data = NULL;
	lst->all->is_key = 0;
	lst->all->quoted = 0;
	lst->all->length = 0;
	lst->all->found_space = 0;
	lst->nb_tokens = 0;

}

typedef struct s_lexer
{
	t_token	*token;
	char	*buffer;
	char	quote;
	int	i;
	int	j;
	int	start;

}t_lexer;

void __init_lexer_vars(t_lexer *vars, t_token_list *lst, int size)
{
	vars->buffer = (char *)malloc(sizeof(char) * size);
	vars->quote = 0;
	vars->i = 0;
	vars->j = 0;
	vars->start = 1;
	vars->token = lst->all;
}

void get_nonquoted(t_token_list *lst, t_lexer *var, char *text)
{
	if (*text == D_QUOTE || *text == S_QUOTE)
	{
		//if (var->i  || (var->j && text[var->j - 1] == '$'))
		if (0)
		{
			get_data(var->buffer, var->i, &(var->token), &(var->start));
			var->i = 0;
			lst->nb_tokens += 1;
		}
		var->quote = *text;
		var->buffer[var->i++] = *text;
	}

	else if (*text == ' ')
	{
		if (var->i)
		{
			get_data(var->buffer, var->i, &(var->token), &(var->start));
			lst->nb_tokens += 1;
			var->i = 0;
		}
		else
			var->token->found_space = 1;
	}
	else if (is_keyword(*text) || !*text)
	{
		if (var->i)
		{
			get_data(var->buffer, var->i, &(var->token), &(var->start));
			lst->nb_tokens += 1;
		}
		if (*text)
		{
			var->buffer[0] = *text;
			get_data(var->buffer, -1, &(var->token), &(var->start));
		}
		var->i = 0;
	}
	else if (!is_keyword(*text) && *text != ' ')
		var->buffer[var->i++] = *text;

}

void get_between_quots(t_token_list *lst, t_lexer *var, char *text)
{
	var->buffer[var->i++] = *text;
	if (*text == var->quote)
	{
		get_data(var->buffer, var->i, &(var->token), &(var->start));
		var->token->quoted = var->quote;
		lst->nb_tokens += 1;
		var->i = 0;
		var->quote = 0;
	}
}

void get_tokens(t_token_list *lst, char *text, int	size)
{
	t_lexer vars;	

	if (!text)
		return ;
	__init_list(lst);
	__init_lexer_vars(&vars, lst, size);
	while (vars.j <= size)
	{
		if (!vars.quote)
			get_nonquoted(lst, &vars, text);
		else
			get_between_quots(lst, &vars, text);
		text++;
		vars.j++;
	}
	if (vars.quote)
		get_data(vars.buffer, 0, &(vars.token), &(vars.start));

}

int main(int ac, char **av, char **env)
{
	char *t_cmd;
	t_token_list token_lst;
	t_token *t;
	t_list	*enviorment;
	
	(void)ac;
	(void)av;
	while (1)
	{
		t_cmd = readline("$ ");
		get_tokens(&token_lst, t_cmd, ft_strlen(t_cmd));
		if (token_lst.nb_tokens && n_parser(&token_lst, &enviorment, env))
			continue;
		add_history(t_cmd);
		t  = token_lst.all;
		while (t)
		{
			printf("--/-: [%s] {%p}\n", t->data, t->next_token);
			t = t->next_token;
		}

	}
}
