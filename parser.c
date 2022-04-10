/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adriouic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 22:03:56 by adriouic          #+#    #+#             */
/*   Updated: 2022/04/10 15:13:36 by adriouic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_list *create_env(char **env)
{
	t_list	*head;
	t_list	*tmp;
	int		i;

	head = NULL;
	i = 0;
	while (env[i])
	{
		tmp = ft_lstnew(ft_strdup(env[i]));
		if (!tmp)
		{
			ft_lstclear(&head, free);
			return (NULL);
		}	
		ft_lstadd_front(&head, tmp);
		i++;
	}
	return (head);
}

void expand_quoted_token(t_token *token, t_list *env, char *var_name)
{
	char	*tmp;
	char	*tmp1;
	char	*equale_index;
	t_list *iterator;
	
	iterator = env;
	tmp1 = ft_strchr(var_name, token->quoted); 
	if(tmp1)
		*tmp1 = 0;
	//printf("tmp1 : %s var name [%s], quote : %c\n", tmp1 , var_name, token->quoted);
	tmp = 0;
	while (tmp1 && iterator && token->length > 1)
	{
		equale_index = ft_strchr((char *)iterator->content, '=');
		if (equale_index)
		{
			*equale_index = 0;
			if (!ft_strcmp(var_name, iterator->content))
			{
				*equale_index = '=';
				tmp = ft_strjoin((const char *)++equale_index, tmp1 + 1);
				break ;
			}
			*equale_index = '=';
		}
		iterator = iterator->next;
	}
	if(tmp1)
		*tmp1 = token->quoted;
	else
		tmp = ft_calloc(1, sizeof(char));
	if (!tmp && tmp1)
		tmp = ft_strdup(tmp1 + 1);
	free(token->data);
	token->data = tmp;

}
void expand_varible(t_token *token, t_list *env)
{
	t_list *iterator;
	char	*var_name;
	char	*tmp;
	char	*equale_index;

	iterator = env;
	var_name = token->data + 1;
	if (token->quoted)
	{
		expand_quoted_token(token, env, var_name);
		return ;
	}
	tmp = 0;
	while (iterator && token->length > 1)
	{
		equale_index = ft_strchr((char *)iterator->content, '=');
		
		if (equale_index)
		{
			*equale_index = 0;
				
			if (!ft_strcmp(var_name, iterator->content))
			{
				*equale_index = '=';
				tmp = ft_strdup((const char *)++equale_index);
				break ;
			}
			*equale_index = '=';
		}
		iterator = iterator->next;
	}
	if (!tmp)
		tmp = ft_calloc(1, sizeof(char));
	free(token->data);
	token->data = tmp; 
}

bool n_parser(t_token_list *lst, t_list **env, char **env_vector)
{
	t_token *t;
	char 	*polished;


	*env = create_env(env_vector);
	if (!*env)
		return (1);
	if (!lst)
		return 1;
	t = lst->all; 
	while (t)
	{
		if (t->is_key && (!t->next_token || !t->next_token->data))
			return (printf("syntax error unexpected token after 'newline'\n"));
		if (t->data == NULL)
			return (printf("Parse Error, Uncolsed quote\n"));
		if (lst->all->type == PIPE)
			return (printf("syntax error unexpected token '%s'\n", t->data));
		if (t->is_key && (t->next_token && t->next_token->is_key))
			return (printf("syntax error unexpected token '%s'\n", t->next_token->data));
		if (t->quoted)
		{
			polished = ft_strtrim(t->data, &(t->quoted));
			free(t->data);
			t->data = polished;
		}
		if (t->data[0] == '$')
			expand_varible(t, *env);
		t = t->next_token;
	}
	return (0);
}
