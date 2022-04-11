/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_one.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adriouic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 02:07:55 by adriouic          #+#    #+#             */
/*   Updated: 2022/04/11 15:51:01 by adriouic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "lexer.h"
#include "libft/libft.h"
#include "includes/includes.h"


void __init_cmd(t_cmd *cmd)
{
	cmd->fd_in = 0;
	cmd->fd_out = 1;
	cmd->error_free = 1;
	cmd->commad = NULL;
}

void heredoc(char *eof, t_list *env)
{
	char *buffer;
	int	fd;

	fd = open("/tmp/minishell-dumy_file-0ew3d", O_CREAT | O_APPEND , 0600);
	(void)env;
	while (1)
	{
		buffer = readline("heredoc> ");
		if (!ft_strcmp(buffer, eof))
			break;
		write(fd, buffer,ft_strlen(buffer));
		free(buffer);
	}
	unlink("/tmp/minishell-dumy_file-0ew3d");
}

int	close_old_open_new(t_cmd *cmd, char *file_name, int mode, int old_fd)
{
	int fd;

	if (old_fd > 2)
		close(old_fd);
	if (mode == O_RDONLY)
	{
		if (access(file_name, F_OK) != 0)
		{
			cmd->error_free = 0;
			return (printf("Error : No such file '%s'\n", file_name) * 0);
		}
		fd = open(file_name, O_RDONLY);
	}
	else
		fd = open(file_name, O_CREAT | O_WRONLY | mode, 06644);
	if (fd < 0)
	{
		cmd->error_free = 0;
		return (printf("Permission Denied. %s \n", file_name) * 0);
	}
	return (fd);
}

void open_file(t_cmd *cmd, t_token *t, char *file_name)
{
	if(t->type == R_ARROW)
		cmd->fd_out = close_old_open_new(cmd, file_name, O_WRONLY, cmd->fd_out);
	else if (t->type == DR_ARROW)
		cmd->fd_out = close_old_open_new(cmd, file_name, O_APPEND, cmd->fd_out);
	else if (t->type == L_ARROW)
		cmd->fd_in = close_old_open_new(cmd, file_name, O_RDONLY, cmd->fd_in);
}

void	close_files(t_cmd *cmd)
{
	if (cmd->fd_in > 3)
		close(cmd->fd_in);
	if (cmd->fd_out > 3)
		close(cmd->fd_out);
}

t_list	*parser_one(t_token_list *lst, t_list *env)
{
	int i = 0;
	int		fd;
	t_list	*cmd_lst;
	t_token *t;
	t_cmd	*cmd;
	
	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	__init_cmd(cmd);
	t = lst->all;
	cmd_lst = NULL;
	while (t)
	{
		printf("In parser %d\n", i++);
		if (t->type == PIPE )
		{
			fd = cmd->fd_out;
			ft_lstadd_back(&cmd_lst, ft_lstnew(cmd));
			cmd = (t_cmd *)malloc(sizeof(t_cmd));
			__init_cmd(cmd);
			cmd->fd_in = fd;
		}
		else if (t->is_key && t->type == DL_ARROW)
		{
			heredoc(t->next_token->data, env, cmd);
		}
		else if (t->is_key)
			open_file(cmd, t, t->next_token->data);
		if (!cmd->error_free)
			close_files(cmd);
		t = t->next_token;
	}
	ft_lstadd_back(&cmd_lst, ft_lstnew(cmd));
	return (cmd_lst);
}
