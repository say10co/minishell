/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adriouic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 03:22:25 by adriouic          #+#    #+#             */
/*   Updated: 2022/04/28 23:03:13 by adriouic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/includes.h"

void	get_keyword_and_filename(t_token_list *lst, t_lexer *var, char *text)
{
	if (var->i)
	{
		if (get_data(var->buffer, var, &(var->token), 0))
			lst->nb_tokens += 1;
	}
	if (*text)
	{
		var->buffer[0] = *text;
		var->i = -1;
		if (get_data(var->buffer, var, &(var->token), 0))
			lst->nb_tokens += 1;
		if (!var->token->type)
			var->token->type = get_type(*text, 0);
	}
	var->i = 0;
}

void	get_befor_quote(t_token_list *lst, t_lexer *var, char *text)
{
	bool	join;

	join = 0;
	if (var->i && !is_keyword(*(text -1)) && *(text -1) != ' ')
		join = 1;
	if (var->i && get_data(var->buffer, var, &(var->token), join))
	{
		lst->nb_tokens += 1;
		var->i = 0;
	}
	var->quote = *text;
	var->quote_type = *text;
	var->buffer[var->i++] = *text;
}

void	get_nonquoted(t_token_list *lst, t_lexer *var, char *text)
{
	if (*text == D_QUOTE || *text == S_QUOTE)
		get_befor_quote(lst, var, text);
	else if (*text == ' ')
	{
		if (var->i)
		{
			if (get_data(var->buffer, var, &(var->token), 0))
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
	bool	join;

	join = 0;
	var->buffer[var->i++] = *text;
	if (*text == var->quote)
	{
		if (!is_keyword(*(text +1)) && *(text +1) != ' ')
			join = 1;
		if (get_data(var->buffer, var, &(var->token), join))
		{
			var->token->quoted = var->quote;
			lst->nb_tokens += 1;
		}
		var->i = 0;
		var->quote = 0;
	}
}
