/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macplus <macplus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 18:01:00 by bberkass          #+#    #+#             */
/*   Updated: 2022/05/12 01:55:29 by macplus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/includes.h"

static void	handle_builtin(t_cmd *cmd, int *fd, int size, int i)
{
	int	tmp_fdo;
	int	fdo;

	if (i < size - 1 || cmd->fd_out > 2)
	{
		tmp_fdo = dup(1);
		fdo = open("/tmp/ms-builtin-tmp", O_CREAT | O_RDWR, 0777);
		dup2(fdo, 1);
	}
	exec_builtin(is_builtin(cmd->command[0]), cmd);
	if (i < size - 1 || cmd->fd_out > 2)
	{
		close(fdo);
		fdo = open("/tmp/ms-builtin-tmp", O_RDWR);
		dup2(tmp_fdo, 1);
		if (i < size - 1 && cmd->fd_out > 2)
			copy_file(fdo, fd[i * 2 + 1], cmd->fd_out);
		else if (cmd->fd_out > 2)
			copy_file(fdo, -1, cmd->fd_out);
		else
			copy_file(fdo, fd[i * 2 + 1], -1);
		close(tmp_fdo);
		unlink("/tmp/ms-builtin-tmp");
	}
}

static void	handle_cmd(t_cmd *cmd, int *fd, int i, int size)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		perror("fork faild ");
	else if (pid == 0)
	{
		if (cmd->fd_in > 2 && i == 0)
			dup2(cmd->fd_in, 0);
		if (cmd->fd_in > 2 && i > 0)
			merge_input(fd[(i - 1) * 2 + 1], cmd->fd_in);
		if (i != 0)
			dup2(fd[(i - 1) * 2], 0);
		if (cmd->fd_out > 2 && size > 1 && i < size - 1)
			dup2(cmd->fd_out, 1);
		else if ((cmd->fd_out > 2 && size == 1)
			|| (cmd->fd_out > 2 && size > 1 && i == size - 1))
			dup2(cmd->fd_out, 1);
		if (i < size - 1 && cmd->fd_out <= 2)
			dup2(fd[i * 2 + 1], 1);
		close_pipes(fd, size);
		execve(cmd->command[0], cmd->command, gen_env());
		perror("exec faild");
	}
}

void	update_exec_status(int status)
{
	char	*s;

	s = ft_itoa(status);
	ft_updateenv("$", s);
	free(s);
}

void	exec_cmd(t_list *icmd)
{
	t_cmd	*cmd;
	int		*fd;
	int		size;
	int		i;
	int		status;

	size = ft_lstsize(icmd);
	fd = init_pipes(size);
	i = 0;
	while (i < size && icmd)
	{
		cmd = (t_cmd *)icmd->content;
		if (cmd->command && cmd->error_free && is_builtin(cmd->command[0]))
			handle_builtin(cmd, fd, size, i);
		else if (cmd->command && cmd->error_free)
			handle_cmd(cmd, fd, i, size);
		close_iofd(cmd);
		i++;
		destroy_command(cmd);
		icmd = icmd->next;
	}
	close_pipes(fd, size);
	while (i-- > 0)
		wait(&status);
	update_exec_status(status);
}
