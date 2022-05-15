/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adriouic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 16:40:08 by adriouic          #+#    #+#             */
/*   Updated: 2022/05/15 13:17:29 by adriouic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/includes.h"

void	del_node(char *key)
{
	t_list	*curr;
	t_list	*prev;
	char	*tkey;
	t_env	*e;

	curr = g_env;
	prev = curr;
	while (curr)
	{
		e = (t_env *)curr->content;
		tkey = (e)->key;
		if (!ft_strcmp(key, tkey))
		{
			if (curr == g_env)
				g_env = curr->next;
			prev->next = curr->next;
			free(e->key);
			free(e->val);
			free(e);
			free(curr);
			break ;
		}
		prev = curr;
		curr = curr->next;
	}
}

void	unset(char **command)
{
	int	i;

	i = 1;
	if (!command[1])
		return ;
	while (command[i])
		del_node(command[i++]);
}
