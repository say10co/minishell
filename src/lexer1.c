/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adriouic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 00:31:44 by adriouic          #+#    #+#             */
/*   Updated: 2022/04/13 00:43:02 by adriouic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lexer.h"
#include "../includes/includes.h"
#include "../libft/libft.h"

void	__init_list(t_token_list *lst)
{
	lst->all = (t_token *)malloc(sizeof(t_token));
	lst->all->next_token = NULL;
	lst->all->data = NULL;
	lst->all->is_key = 0;
	lst->all->type = 0;
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
	int		i;
	int		j;
	int		start;

}t_lexer;

void	__init_lexer_vars(t_lexer *vars, t_token_list *lst, int size)
{
	vars->buffer = (char *)malloc(sizeof(char) * size);
	vars->quote = 0;
	vars->i = 0;
	vars->j = 0;
	vars->start = 1;
	vars->token = lst->all;
}

void	get_nonquoted(t_token_list *lst, t_lexer *var, char *text)
{
	if (*text == D_QUOTE || *text == S_QUOTE)
	{
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
			if (!var->token->type)
				var->token->type = get_type(*text, 0);
		}
		var->i = 0;
	}
	else if (!is_keyword(*text) && *text != ' ')
		var->buffer[var->i++] = *text;
}

void	get_between_quots(t_token_list *lst, t_lexer *var, char *text)
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

void	get_tokens(t_token_list *lst, char *text, int size)
{
	t_lexer	vars;	

	__init_list(lst);
	if (!text)
		return ;
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
