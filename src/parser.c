/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adriouic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 22:03:56 by adriouic          #+#    #+#             */
/*   Updated: 2022/05/14 17:42:18 by adriouic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/includes.h"

char	is_qouted(char *s)
{
	char	*t;

	t = ft_strchr(s, '\'');
	if (t)
		return (*t);
	t = ft_strchr(s, '\"');
	if (t)
		return (*t);
	return (0);
}

t_list	*create_env(char **env)
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

bool	check_syntax(t_token *t, t_token_list *lst)
{
	if (t->quote_err)
		return (printf(PARSE_ERR));
	if (t->is_key && (!t->next_token || !t->next_token->data))
		return (printf("%s '%s'\n", SYNTAX_ERR, "newline"));
	if (lst->all->type == PIPE)
		return (printf("%s '%s'\n", SYNTAX_ERR, t->data));
	if (t->is_key)
	{
		if (t->type == PIPE && t->next_token->type == PIPE)
			return (printf("%s '%s'\n", SYNTAX_ERR, t->next_token->data));
		if (t->next_token && t->next_token->is_key && t->type != PIPE)
			return (printf("%s '%s'\n", SYNTAX_ERR, t->next_token->data));
	}
	return (0);
}

struct s_pvars
{
	t_token	*t;
	t_list	*lst_list;
	int		length;
	int		last;
};

void	trim_expand_token(struct s_pvars *vars)
{
	char	*polished;

	if (vars->t->data && ft_strchr(vars->t->data, '$'))
	{
		polished = vars->t->data;
		vars->t->data = get_values(vars->t->data,
				&(vars->lst_list), vars->t->quoted);
		ft_lstclear(&(vars->lst_list), free);
		free(polished);
	}
}

bool	n_parser(t_token_list *lst)
{
	struct s_pvars	vars;

	vars.length = 0;
	vars.last = 0;
	vars.lst_list = NULL;
	if (!lst)
		return (1);
	vars.t = lst->all;
	while (vars.t)
	{
		if (check_syntax(vars.t, lst))
			return (1);
		if (!vars.t->quoted || vars.t->quoted == '"')
			trim_expand_token(&vars);
		vars.last = vars.t->type;
		vars.t = vars.t->next_token;
	}
	return (0);
}
