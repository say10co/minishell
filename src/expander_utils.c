/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adriouic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 21:29:26 by adriouic          #+#    #+#             */
/*   Updated: 2022/05/15 15:07:32 by adriouic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/includes.h"

void	check_parameters(t_list *lst, char **result, int total_length)
{
	if (lst)
		*result = (char *)malloc((total_length + 1) * sizeof(char));
	if (!*result && lst)
		perror("Allocation failed.\n");
}

char	*wrappup_exapnded_token(t_list *lst, int total_length)
{
	char	*result;
	char	c;
	int		i;
	int		j;

	result = NULL;
	check_parameters(lst, &result, total_length);
	i = 0;
	while (result && lst)
	{
		j = 0;
		if (lst->content)
			c = ((char *)lst->content)[j];
		while (c)
		{
			result[i++] = c;
			c = ((char *)lst->content)[++j];
		}
		lst = lst->next;
		result[i] = 0;
	}
	ft_lstclear(&lst, free);
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
