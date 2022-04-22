/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bberkass <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 18:26:22 by bberkass          #+#    #+#             */
/*   Updated: 2022/04/22 19:08:47 by bberkass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/includes.h"


void	ft_initenv(char **env)
{
	t_env	*en_var;
	t_list	*node;
	char	**var;

	while(*env)
	{
		var = ft_split(*env, '=');
		en_var = (t_env *)malloc(sizeof(t_env));
		en_var->key = var[0];
		en_var->val = var[1];
		node = ft_lstnew(en_var);
		ft_lstadd_back(&genv, node);
		env++;
	}
}

char	*ft_getenv(char *key)
{
	t_env	*env;
	t_list	*curr;

	curr = genv;
	while(genv)
	{
		env = (t_env *)curr->content;
		if(!ft_strcmp(env->key, key))
			return (env->val);
		curr = curr->next;
	}
	
	return NULL;
}

void	ft_updateenv(char *key, char *new_val)
{
	t_env	*env;
	t_list	*curr;
	char	*val;

	curr = genv;
	while(curr)
	{
		env = (t_env *)curr->content;
		if(!ft_strcmp(key, env->key))
		{
			val = ft_strdup(new_val);
			free(env->val);
			env->val = val;
			return;
		}
		curr = curr->next;
	}
	return;
}
