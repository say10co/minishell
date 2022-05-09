/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adriouic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 19:56:34 by adriouic          #+#    #+#             */
/*   Updated: 2022/04/29 00:33:50 by adriouic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/includes.h"

void	get_bfore_key(t_list **str_lst, t_variables *v, int	*length)
{
	if (v->j)
	{
		(v->buffer)[v->j] = 0;
		ft_lstadd_back(str_lst, ft_lstnew(ft_strdup(v->buffer)));
		*length += (v->j);
		v->j = 0;
	}
}

void	expand(t_variables *v, t_list **str_lst, int *length)
{
	char	*buffer;
	char	*t;

	get_bfore_key(str_lst, v, length);
	buffer = v->buffer;
	v->i += 1;
	while ((v->token)[v->i] == (v->token[v->i + 1])
			&& ((v->token[v->i]) == '\'' || (v->token[v->i]) == '"'))
		v->i++;
	while ((v->token[v->i]) && (v->token[v->i]) != ' '
		&& (v->token[v->i] != '$') && (v->token[v->i]) != '\''
		&& (v->token[v->i]) != '\"')
		(v->buffer)[v->j++] = (v->token[v->i++]);
	buffer[v->j] = 0;
	t = ft_getenv(buffer);
	if (t)
	{
		*length += ft_strlen(t);
		ft_lstadd_back(str_lst, ft_lstnew(ft_strdup(t)));
	}
	v->j = 0;
}

bool	__init_variable(t_variables *v, char *token)
{
	v->len_token = ft_strlen(token);
	v->buffer = (char *) malloc(sizeof(char) * (v->len_token + 1));
	if (!v->buffer)
	{
		perror("Allocation Failed\n");
		return (1);
	}
	v->i = 0;
	v->j = 0;
	v->token = token;
	return (0);
}

char	*get_values(char *token, t_list **str_lst, char q)
{
	t_variables	v;
	int			length;

	length = 0;
	*str_lst = NULL;
	if (__init_variable(&v, token))
		return (NULL);
	while (v.token[v.i])
	{
		if (token[v.i] == '$')
			expand(&v, str_lst, &length);
		else if (((v.token)[(v.i)] != q))
			(v.buffer)[(v.j)++] = (v.token)[(v.i)++];
		else
			v.i++;
	}
	if (v.j)
	{
		(v.buffer)[v.j] = 0;
		ft_lstadd_back(str_lst, ft_lstnew(ft_strdup(v.buffer)));
		length += v.j;
	}
	free(v.buffer);
	return (wrappup_exapnded_token(*str_lst, length));
}
