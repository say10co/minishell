/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macplus <macplus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 18:01:00 by bberkass          #+#    #+#             */
/*   Updated: 2022/05/10 16:52:43 by macplus          ###   ########.fr       */
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

void	exec_cmd(t_list *icmd, char **env)
{
	t_cmd	*cmd;
	int		*fd;
	int		size;
	int		i;
	int		status;
	int		tmp_fdo;
	pid_t	pid;

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
    if(cmd->error_free && is_builtin(cmd->command[0]))
    {
      // handle pipe and redirection 
      // check if it'is not the last command before pipe 
      if(i < size - 1)
      {
        tmp_fdo = dup(1);
        status = dup2(fd[i * 2 + 1], 1);
				if (status < 0)
					perror("dup2 faild");
        close(fd[i * 2 + 1]);
      } 
      else if(cmd->fd_out > 2)
      {
        tmp_fdo = dup(1);
        status = dup2(cmd->fd_out, 1);
				if (status < 0)
					perror("dup2 faild");
      }
      exec_builtin(is_builtin(cmd->command[0]), cmd);      
      if(i < size - 1)
      {
        dup2(tmp_fdo, 1);
        if(cmd->fd_out > 2)
          copy_file(fd[i * 2], cmd->fd_out);
        close(tmp_fdo); 
      }
      else if(cmd->fd_out > 2)
      {
        dup2(tmp_fdo, 1);
        close(tmp_fdo);
      }
    }
    else if (cmd->error_free)
		{
			pid = fork();
			if (pid == -1)
				perror("fork faild ");
			else if (pid == 0)
			{
				// child process 
				if (cmd->fd_in > 2 && i == 0)
					dup2(cmd->fd_in, 0);
		    if(cmd->fd_in > 2 && i > 0)
					merge_input(fd[(i - 1) * 2 + 1], cmd->fd_in);
        if (i != 0)
				{
					// this is not the first command ! 
					// child gets the previous process output by duplicating read fd to stdin  
					//write(fd[(i - 1) * 2 + 1], "kanye_west_is_now_ye", 20);
          status = dup2(fd[(i - 1) * 2], 0);
					if (status < 0)
						perror("dup2 faild");
				}
				// check if file output to another fd beside stdout !
				// execute command in another proccess redirect result to the given fd if cmd size > 1
				// otherwise redirect command output to the given fd and display nada on stdout !
				if (cmd->fd_out > 2 && size > 1 && i < size - 1)
					output_tofile(cmd);
				else if (cmd->fd_out > 2 && size > 1 && i == size - 1) // if the last command output to fil 
					dup2(cmd->fd_out, 1); 		
				else if (cmd->fd_out > 2 && size == 1)
					dup2(cmd->fd_out, 1);
				if (i < size - 1)
				{
					// this is not the last command !
					// child output to the next command bu dup write fd to std out
					status = dup2(fd[i * 2 + 1], 1);
					if (status < 0)
						perror("dup2 faild");
				}
				// close pipe's fd to have EOF so the next proccess can read from it 
				close_pipes(fd, size);
				execve(cmd->command[0], cmd->command, env);
				perror("exec faild");
			  return;
      }
		}
		close_iofd(cmd);
		i++;
		destroy_command(cmd);
    icmd = icmd->next;
	}
	close_pipes(fd, size);
	i = 0;
	while (i++ < size)
		wait(&status);
	ft_updateenv("$", ft_itoa(status));
}
