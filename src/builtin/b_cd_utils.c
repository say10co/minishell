/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_cd_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bberkass <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 19:38:16 by bberkass          #+#    #+#             */
/*   Updated: 2022/05/14 15:43:50 by bberkass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/includes.h"

void	go_touser(char *dir)
{
	char	*holder;
	int		status;

	holder = ft_strreplace(dir, "~", "/Users/");
	if (!holder)
		printf("msh: no such user or named directory: %s\n", holder);
	status = chdir(holder);
	if (status == -1)
		printf("msh: no such user or named directory: %s\n", holder);
	free(holder);
}

void	go_tohome(void)
{
	int	status;

	status = chdir(ft_getenv("HOME"));
	if (status == -1)
		perror("cd faild !");
}

void	go_todir(char *dir)
{
	int	status;

	status = chdir(dir);
	if (status == -1)
		printf("cd: no such file or directory: %s\n", dir);
}

void	go_tobasedhome(char *dir)
{
	char	*holder;
	char	*pwd;
	int		status;

	holder = ft_getenv("HOME");
	pwd = ft_strreplace(dir, "~", holder);
	status = chdir(pwd);
	free(pwd);
	if (status == -1)
		printf("cd: no such file or directory: %s\n", dir);
}

void	go_replcpwd(char *target, char *replacement)
{
	char	*pwd;
	char	*holder;
	int		status;

	pwd = ft_getenv("PWD");
	holder = ft_strreplace(pwd, target, replacement);
	if (!holder)
		printf("cd: string not in pwd: %s\n", target);
	else
	{
		status = chdir(holder);
		if (status == -1)
			printf("cd: no such file or directory: %s\n", holder);
		else
			printf("%s\n", holder);
		free(holder);
	}
}
