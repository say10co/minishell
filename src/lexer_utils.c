/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adriouic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 00:37:53 by adriouic          #+#    #+#             */
/*   Updated: 2022/04/28 22:37:31 by adriouic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/includes.h"

int	get_type(char c, int p)
{
	if (c == '>' && p)
		return (DR_ARROW);
	if (c == '<' && p)
		return (DL_ARROW);
	if (c == '|')
		return (PIPE);
	if (c == '>')
		return (R_ARROW);
	if (c == '<')
		return (L_ARROW);
	return (0);
}

bool	merge(char c1, char c2, t_token *t)
{
	char	*both;

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
		t->type = get_type(c1, 1);
		return (1);
	}
	return (0);
}

void	fill_token(t_token *t, char *buffer)
{
	char	*tmp;

	tmp = ft_strdup(buffer);
	if (tmp[0] == '\0')
	{
		free(tmp);
		tmp = NULL;
	}
	t->data = tmp;
	t->length = ft_strlen(tmp);
}

bool	is_key_(int *i)
{
	if (*i == -1)
	{
		*i = 1;
		return (1);
	}
	return (0);
}

bool	get_data(char *buffer, t_lexer *v, t_token **t, bool join)
{
	bool	is_key;
	char	*tmp;
	int		i;

	i = v->i;
	is_key = is_key_(&i);
	if ((*t)->is_key && is_key && merge(buffer[0], (*t)->data[0], *t))
		return (1);
	buffer[i] = 0;
	if (i && (buffer[i -1] == S_QUOTE || buffer[i -1] == D_QUOTE))
		tmp = ft_strtrim(buffer, &buffer[i -1]);
	else
		tmp = ft_strdup(buffer);
	if (tmp[0] == '\0')
	{
		free(tmp);
		return (0);
	}
	__init_new_command(v, t, join, is_key);
	fill_token(*t, tmp);
	v->start = 0;
	free(tmp);
	return (1);
}
