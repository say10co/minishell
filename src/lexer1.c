/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adriouic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 00:31:44 by adriouic          #+#    #+#             */
/*   Updated: 2022/04/21 02:56:19 by adriouic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lexer.h"
#include "../includes/includes.h"
#include "../libft/libft.h"

void	__init_lexer_vars(t_lexer *vars, t_token_list *lst, int size)
{
	vars->buffer = (char *)malloc(sizeof(char) * size);
	vars->quote = 0;
	vars->i = 0;
	vars->j = 0;
	vars->start = 1;
	vars->token = lst->all;
}

void	get_keyword_and_filename(t_token_list *lst, t_lexer *var, char *text)
{
	if (var->i)
	{
		if (get_data(var->buffer, var->i, &(var->token), &(var->start)))
			lst->nb_tokens += 1;
	}
	if (*text)
	{
		var->buffer[0] = *text;
		if (get_data(var->buffer, -1, &(var->token), &(var->start)))
			lst->nb_tokens += 1;
		if (!var->token->type)
			var->token->type = get_type(*text, 0);
	}
	var->i = 0;
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
			if (get_data(var->buffer, var->i, &(var->token), &(var->start)))
				lst->nb_tokens += 1;
			var->i = 0;
		}
		else
			var->token->found_space = 1;
	}
	else if (is_keyword(*text) || !*text)
		get_keyword_and_filename(lst, var, text);
	else if (!is_keyword(*text) && *text != ' ')
		var->buffer[var->i++] = *text;
}

void	get_between_quots(t_token_list *lst, t_lexer *var, char *text)
{
	var->buffer[var->i++] = *text;
	if (*text == var->quote)
	{
		if (get_data(var->buffer, var->i, &(var->token), &(var->start)))
		{
			var->token->quoted = var->quote;
			lst->nb_tokens += 1;
		}
		var->i = 0;
		var->quote = 0;
	}
}

t_token_list *get_tokens(char *text)
{
	t_lexer			vars;	
	t_token_list	*lst;
	int				size;

	if (!text || !text[0])
		return (NULL);
	size = ft_strlen(text);
	lst  = (t_token_list *)(malloc(sizeof(t_token_list)));
	__init_list(lst);
	if (!text)
	{
		free(lst);
		return (NULL);
	}
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
		(vars.token)->quote_err = 1;
	else if (lst->nb_tokens == 0)
		lst->all->data = ft_strdup("");
	free(vars.buffer);
	return (lst);
}