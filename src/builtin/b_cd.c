/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_cd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bberkass <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 19:38:16 by bberkass          #+#    #+#             */
/*   Updated: 2022/05/15 12:50:49 by adriouic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/includes.h"

static int	arg_size(char **arg)
{
	int	l;

	if (!arg)
		return (0);
	l = 0;
	while (arg[l])
		l++;
	return (l);
}

void	go_oldpwd(void)
{
	char	*oldpwd;
	int		status;

	oldpwd = ft_getenv("OLDPWD");
	printf("%s\n", oldpwd);
	status = chdir(oldpwd);
	if (status == -1)
		perror("cd faild");
}

static int	core_cd(char **arg, int size)
{
	if (size > 3)
		printf("cd: too many arguments\n");
	else if (size == 2 && arg[1][0] == '~'
		&& ft_strlen(arg[1]) > 1 && arg[1][0] != '/')
		go_touser(arg[1]);
	else if (size == 2 && arg[1][0] == '-'
		&& ft_strlen(arg[1]) == 1)
		go_oldpwd();
	else if ((size == 2 && arg[1][0] == '~'
		&& ft_strlen(arg[1]) == 1) || size == 1 || ((!ft_strcmp("--", arg[1])
		|| !ft_strcmp("~-", arg[1])) && size == 2))
		go_tohome();
	else if (size == 3)
		go_replcpwd(arg[1], arg[2]);
	else if (size == 2 && (arg[1][0] != '~'))
		go_todir(arg[1]);
	else if (size == 2 && arg[1][0] == '~' && ft_strlen(arg[1]) > 1)
		go_tobasedhome(arg[1]);
	else
	{
		printf("Unsupported arguments !");
		return (0);
	}
	return (1);
}

int	cd(char **arg)
{
	int		size;
	char	path[4096];

	size = arg_size(arg);
	getcwd(path, 4096);
	if (!core_cd(arg, size))
		return (42);
	ft_updateenv("OLDPWD", path);
	getcwd(path, 4096);
	ft_updateenv("PWD", path);
	return (0);
}
