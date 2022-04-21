/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adriouic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 22:08:02 by adriouic          #+#    #+#             */
/*   Updated: 2022/04/21 03:02:08 by adriouic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../libft/libft.h"
#include <stdio.h>

typedef struct s_variables
{
	int		i;
	int		j;
	int		len_token;
	char	*buffer;
	char	*token;
}t_variables;

char	*wrappup_exapnded_token(t_list *str_lst, int total_length)
{
	t_list	*curr;
	char	*result;
	int		i;
	int		j;

	result = (char *)malloc(total_length * sizeof(char));
	if (!result)
	{
		printf("Allocation failed in 'wrappup_exapnded_token;'\n");
		return (NULL);
	}
	curr = str_lst;
	i = 0;
	while (curr)
	{
		j = 0;
		while (curr->content && ((char *)curr->content)[j])
			result[i++] = ((char *)curr->content)[j++];
		curr = curr->next;
	}
	result[i] = 0;
	return (result);
}

char	*get_value_of_key(char *key, t_list *local_env)
{
	t_list	*iterator;
	char	*tmp;
	char	*equale_index;

	tmp = NULL;
	iterator = local_env;
	while (iterator)
	{
		equale_index = ft_strchr((char *)iterator->content, '=');
		if (equale_index)
		{
			*equale_index = 0;
			if (!ft_strcmp(key, iterator->content))
			{
				*equale_index = '=';
				tmp = ft_strdup(++equale_index);
				break ;
			}
			*equale_index = '=';
		}
		iterator = iterator->next;
	}
	return (tmp);
}

void	expand(t_variables *v, t_list **str_lst, int *length, t_list *local_env)
{
	int		i;
	int		j;
	char	*buffer;
	char 	*t;

	(void)local_env;
	i = v->i;
	j = v->j;
	buffer = v->buffer;
	if (j)
	{
		buffer[j] = 0;
		ft_lstadd_back(str_lst, ft_lstnew(ft_strdup(buffer)));
		*length += (j);
		j = 0;
	}
	i += 1;
	while ((v->token)[i] == (v->token[i + 1])
			 && ((v->token[i]) == '\'' || (v->token[i]) == '"'))
		i++;
	while ((v->token[i]) && (v->token[i]) != ' ' && (v->token[i] != '$')
		&& (v->token[i]) != '\'' && (v->token[i]) != '\"')
		(v->buffer)[j++] = (v->token[i++]);
	buffer[j] = 0;
	t = getenv(buffer);
	// if not t look in local env
	if (!t)
		t = get_value_of_key(buffer, local_env);
	*length += ft_strlen(t);
	ft_lstadd_back(str_lst, ft_lstnew(t));
	//printf("%s\n", buffer);
	v->j = 0;
	v->i = i;
}

char	*get_values(char *token, t_list **str_lst, int *length, t_list *local_env)
{
	t_variables	v;

	v.i = 0;
	v.j = 0;
	*str_lst = NULL;
	v.token = token;
	v.len_token = ft_strlen(token);
	v.buffer = (char *) malloc(sizeof(char) * v.len_token);
	while (v.token[v.i])
	{
		if (token[v.i] == '$')
			expand(&v, str_lst, length, local_env);
		else
			(v.buffer)[(v.j)++] = (v.token)[(v.i)++];
	}
	if (v.j)
	{
		(v.buffer)[v.j] = 0;
		ft_lstadd_back(str_lst, ft_lstnew(ft_strdup(v.buffer)));
		*length += v.j;
	}
	free(v.buffer);
	return (wrappup_exapnded_token(*str_lst, *length));
}
