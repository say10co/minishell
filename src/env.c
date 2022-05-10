/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macplus <macplus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 18:26:22 by bberkass          #+#    #+#             */
/*   Updated: 2022/05/10 16:50:14 by macplus          ###   ########.fr       */

/*                                                                            */
/* ************************************************************************** */

#include "../includes/includes.h"

void	ft_initenv(char **env)
{
	t_env	*en_var;
	t_list	*node;
	char	**var;

	while (*env)
	{
		var = ft_split(*env, '=');
		en_var = (t_env *)malloc(sizeof(t_env));
		en_var->key = var[0];
		en_var->val = var[1];
		node = ft_lstnew(en_var);
		ft_lstadd_back(&g_env, node);
		env++;
		free(var);
	}
}

char	*ft_getenv(char *key)
{
	t_env	*env;
	t_list	*curr;

	curr = g_env;
	while (curr)
	{
		env = (t_env *)curr->content;
		if (!ft_strcmp(env->key, key))
			return (env->val);
		curr = curr->next;
	}
	return (NULL);
}

void	ft_updateenv(char *key, char *new_val)
{
	t_env	*env;
	t_env	*new;
	t_list	*curr;
	char	*val;

	curr = g_env;
	while (curr)
	{
		env = (t_env *)curr->content;
		if (!ft_strcmp(key, env->key))
		{
			val = ft_strdup(new_val);
			free(env->val);
			env->val = val;
			return ;
		}
		curr = curr->next;
	}
	new = (t_env *)(malloc(sizeof(t_env)));
	if (!new)
		perror("Allocation Failed!\n");
	new->key = ft_strdup(key);
	new->val = ft_strdup(new_val);
	ft_lstadd_back(&g_env, ft_lstnew(new));
	return ;
}
