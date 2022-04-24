/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adriouic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 00:37:53 by adriouic          #+#    #+#             */
/*   Updated: 2022/04/24 07:37:05 by adriouic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/includes.h"

void	__init_list(t_token_list *lst)
{
	lst->all = (t_token *)malloc(sizeof(t_token));
	lst->all->next_token = NULL;
	lst->all->data = NULL;
	lst->all->is_key = 0;
	lst->all->type = 0;
	lst->all->quoted = 0;
	lst->all->quote_err = 0;
	lst->all->length = 0;
	lst->all->found_space = 0;
	lst->nb_tokens = 0;
}

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

int	is_key_(int *i)
{
	if (*i == -1)
	{
		*i = 1;
		return (1);
	}
	return (0);
}

bool get_data(char *buffer, t_lexer *v, t_token **t, int *start)
{
	int		is_key;
	char	*tmp;
	int		i;

	i = v->i;
	is_key = is_key_(&i);
	if ((*t)->is_key && is_key && merge(buffer[0], (*t)->data[0], *t))
		return (1);
	buffer[i] = 0;
	if (i && (buffer[i-1] == S_QUOTE || buffer[i-1] == D_QUOTE))
		tmp = ft_strtrim(buffer, &buffer[i-1]);
	else
		tmp = ft_strdup(buffer);
	if (tmp[0] == '\0')
	{
		free(tmp);
		return (0);
	}
	if (*start == 0)
	{
		(*t)->next_token = (t_token *)malloc(sizeof(t_token));
		(*t) = (*t)->next_token;
		(*t)->found_space = 0;
		(*t)->next_token = NULL;
		(*t)->quoted = 0;
		(*t)->quote_err = 0;
		(*t)->type = 0;
	}
	(*t)->is_key = is_key;
	(*t)->quoted = v->quote_type;
	fill_token(*t, tmp);
	*start = 0;
	free(tmp);
	return  (1);
}
