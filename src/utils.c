/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macplus <macplus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 01:08:17 by adriouic          #+#    #+#             */
/*   Updated: 2022/04/28 01:20:23 by macplus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/includes.h"

int	is_keyword(char c)
{
	if (c == L_ARROW || c == R_ARROW || c == PIPE)
		return (1);
	return (0);
}

int	is_builtin(char *cmd)
{
	if (!ft_strcmp(cmd, "cd"))
		return (B_CD);
	else if (!ft_strcmp(cmd, "echo") && 0)
		return (B_ECHO);
	else if (!ft_strcmp(cmd, "pwd") && 0)
		return (B_PWD);
	else if (!ft_strcmp(cmd, "export"))
		return (B_EXPORT);
	else if (!ft_strcmp(cmd, "unset"))
		return (B_UNSET);
	else if (!ft_strcmp(cmd, "env"))
		return (B_ENV);
	else if (!ft_strcmp(cmd, "exit"))
		return (B_EXIT);
	return (0);
}

void	copy_file(int fdi, int fdo)
{
	char	*buff;
	int		readed;

	buff = (char *)malloc(sizeof(char) * 2);
	readed = read(fdi, buff, 1);
	while (readed > 0)
	{
		buff[1] = '\0';
		write(fdo, buff, 1);
		readed = read(fdi, buff, 1);
	}
	close(fdo);
	free(buff);
}

static char	*join_env(char *key, char *val)
{
	char	*key_joined;
	char	*env;

	key_joined = ft_strjoin(key, "=");
	env = ft_strjoin(key_joined, val);
	free(key_joined);
	return (env);
}

char	**gen_env(void)
{
	t_env		*env;
	t_list		*curr;
	char		**env_txt;
	int			i;

	if (!g_env)
		return (NULL);
	curr = g_env;
	i = ft_lstsize(g_env);
	env_txt = (char **)malloc(sizeof(char *) * i + 1);
	i = 0;
	while (curr)
	{
		env = (t_env *)curr->content;
		env_txt[i] = join_env(env->key, env->val);
		i++;
		curr = curr->next;
	}
	env_txt[i] = NULL;
	return (env_txt);
}
