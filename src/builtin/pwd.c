/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bberkass <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 19:38:16 by bberkass          #+#    #+#             */
/*   Updated: 2022/05/15 17:22:24 by bberkass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/includes.h"

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

void	pwd(char **arg)
{
	char	*pwd;

	if (args_len(arg) > 1)
	{
		printf("pwd: too many arguments\n");
		return ;
	}
	pwd = getcwd(NULL, 0);
	if (pwd)
	{
		printf("%s\n", pwd);
		free(pwd);
	}
}
