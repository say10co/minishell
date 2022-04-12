/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adriouic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 22:03:56 by adriouic          #+#    #+#             */
/*   Updated: 2022/04/12 01:58:12 by adriouic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "expander.h"
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

bool n_parser(t_token_list *lst, t_list **env, char **env_vector)
{
	t_token *t;
	t_list	*lst_list;
	char 	*polished;
	int		length;
	int		last;

	length = 0;
	last = 0;
	lst_list = NULL;
	*env = create_env(env_vector);
	if (!*env)
		return (1);
	if (!lst)
		return 1;
	t = lst->all; 
	while (t)
	{
		if (t->is_key && (!t->next_token || !t->next_token->data))
			return (printf("syntax error unexpected token 'newline'\n"));
		if (t->data == NULL)
			return (printf("Parse Error, Uncolsed quote\n"));
		if (lst->all->type == PIPE)
			return (printf("syntax error unexpected token '%s'\n", t->data));
		if (t->is_key)
		{
			if (t->type == PIPE && t->next_token->type == PIPE)
				return (printf("syntax error unexpected token '%s'\n", t->next_token->data));
			if (t->next_token && t->next_token->is_key && t->type != PIPE)
				return (printf("syntax error unexpected token '%s'\n", t->next_token->data));
		}
		if (t->quoted)
		{
			polished = ft_strtrim(t->data, &(t->quoted));
			free(t->data);
			t->data = polished;
		}
		if (last != DL_ARROW && t->quoted != S_QUOTE && ft_strchr(t->data, '$'))
		{
			polished = t->data;
			t->data = get_expanded_values(t->data, &lst_list, *env, &length);
			free(polished);
		}
		last = t->type;
		t = t->next_token;
	}
	return (0);
}
