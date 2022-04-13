/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_one.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adriouic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 02:07:55 by adriouic          #+#    #+#             */
/*   Updated: 2022/04/13 04:38:43 by adriouic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/includes.h"

void	__init_cmd(t_cmd *cmd)
{
	cmd->fd_in = 0;
	cmd->fd_out = 1;
	cmd->error_free = 1;
	cmd->command = NULL;
}

void	wrape_command(t_list **cmd_lst, t_cmd **cmd, size_t *vector_size)
{
	int	fd;

	fd = (*cmd)->fd_out;
	ft_lstadd_back(cmd_lst, ft_lstnew(*cmd));
	*cmd = (t_cmd *)malloc(sizeof(t_cmd));
	__init_cmd(*cmd);
	(*cmd)->fd_in = fd;
	*vector_size = 0;
}

void	__init_parser_vars(size_t *size, t_list **cmd_lst, t_cmd **cmd)
{
	*size = 0;
	*cmd = (t_cmd *)malloc(sizeof(t_cmd));
	*cmd_lst = NULL;
	__init_cmd(*cmd);
}

t_list	*parser_one(t_token_list *lst, t_list *env)
{
	size_t	vector_size;
	t_list	*cmd_lst;
	t_token	*t;
	t_cmd	*cmd;

	__init_parser_vars(&vector_size, &cmd_lst, &cmd);
	t = lst->all;
	while (t)
	{
		if (t->type == PIPE)
			wrape_command(&cmd_lst, &cmd, &vector_size);
		else if ((t->is_key && t->type == DL_ARROW))
		{
			heredoc(t->next_token->data, env);
			t = t->next_token;
		}
		if (t->is_key)
		{
			open_file(cmd, t, t->next_token->data);
			t = t->next_token;
		}
		else
			append_to_lst(&(cmd->command), t->data, &vector_size);
		if (!cmd->error_free)
			close_files(cmd);
		t = t->next_token;
	}
	ft_lstadd_back(&cmd_lst, ft_lstnew(cmd));
	return (cmd_lst);
}
