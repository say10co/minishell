/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adriouic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 01:00:04 by adriouic          #+#    #+#             */
/*   Updated: 2022/04/29 01:00:56 by adriouic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/includes.h"

void	__init_list(t_token_list *lst)
{
	lst->all = (t_token *)malloc(sizeof(t_token));
	lst->all->next_token = NULL;
	lst->all->data = NULL;
	lst->all->is_key = 0;
	lst->all->type = 0;
	lst->all->quoted = 0;
	lst->all->quote_err = 0;
	lst->all->length = 0;
	lst->all->join = 0;
	lst->all->found_space = 0;
	lst->nb_tokens = 0;
}

void	__init_cmd(t_cmd *cmd)
{
	cmd->fd_in = 0;
	cmd->fd_out = 1;
	cmd->error_free = 1;
	cmd->command = NULL;
}

void	__init_parser_vars(size_t *size, t_list **cmd_lst, t_cmd **cmd)
{
	*size = 0;
	*cmd = (t_cmd *)malloc(sizeof(t_cmd));
	*cmd_lst = NULL;
	__init_cmd(*cmd);
}

void	__init_new_command(t_lexer *v, t_token **t, bool join, bool is_key)
{
	if (v->start == 0)
	{
		(*t)->next_token = (t_token *)malloc(sizeof(t_token));
		(*t) = (*t)->next_token;
		(*t)->found_space = 0;
		(*t)->next_token = NULL;
		(*t)->quoted = 0;
		(*t)->quote_err = 0;
		(*t)->type = 0;
	}
	(*t)->is_key = is_key;
	(*t)->join = join;
	(*t)->quoted = v->quote_type;
}

char	*slice_nl(char *line)
{
	int	len;

	if (!line)
		return (NULL);
	len = ft_strlen(line);
	line[len -1] = 0;
	return (line);
}
