/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macplus <macplus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 18:01:00 by bberkass          #+#    #+#             */
/*   Updated: 2022/04/28 03:59:44 by macplus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/includes.h"

static void	handle_builtin(t_cmd *cmd, int *fd, int size, int i)
{
	int	tmp_fdo;

	if (i < size - 1)
	{
		printf("INTRO PIPE TO NEXT COMMAND\n");
		tmp_fdo = dup(1);
		dup2(fd[i * 2 + 1], 1);
		close(fd[i * 2 + 1]);
	}
	else if (cmd->fd_out > 2)
	{
		tmp_fdo = dup(1);
		dup2(cmd->fd_out, 1);
	}
	exec_builtin(is_builtin(cmd->command[0]), cmd);
  if (i < size - 1 || cmd->fd_out > 2)
	{
    dup2(tmp_fdo, 1);
		if (cmd->fd_out > 2 && i < size - 1)
		{
      printf("COPY TO FILE \n");
      copy_file(fd[i * 2], cmd->fd_out);
    }
    close(tmp_fdo);
		printf("OUTRO PIPE TO NEXT COMMAND\n");
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
			output_tofile(cmd);
		else if ((cmd->fd_out > 2 && size == 1)
			|| (cmd->fd_out > 2 && size > 1 && i == size - 1))
			dup2(cmd->fd_out, 1);
		if (i < size - 1)
			dup2(fd[i * 2 + 1], 1);
		close_pipes(fd, size);
		execve(cmd->command[0], cmd->command, gen_env());
		perror("exec faild");
	}
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
		if (cmd->error_free && is_builtin(cmd->command[0]))
			handle_builtin(cmd, fd, size, i);
		else if (cmd->error_free)
			handle_cmd(cmd, fd, i, size);
		close_iofd(cmd);
		i++;
		icmd = icmd->next;
	}
	close_pipes(fd, size);
	i = 0;
	while (i++ < size)
		wait(&status);
	ft_updateenv("$", ft_itoa(status));
}
