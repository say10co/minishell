/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bberkass <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 19:38:16 by bberkass          #+#    #+#             */
/*   Updated: 2022/05/15 18:54:21 by bberkass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/includes.h"

void	del(void *content)
{
	if (content)
		free(content);
}

static int	args_len(char **arg)
{
	int	l;

	if (!arg)
		return (0);
	l = 0;
	while (arg[l])
		l++;
	return (l);
}

void	b_exit(char **command)
{
	int	s;
	int	l;

	s = 2;
	if (command)
	{
		l = args_len(command);
		if (l > 2)
		{
			printf("exit: too many arguments\n");
			return ;
		}
		if (l == 2)
			s = ft_atoi(command[1]);
	}
	ft_lstclear(&g_env, del);
	exit(s);
}
