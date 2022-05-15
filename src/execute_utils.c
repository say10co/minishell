/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bberkass <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 22:47:11 by bberkass          #+#    #+#             */
/*   Updated: 2022/05/15 16:25:22 by bberkass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


int	*init_pipes(int size)
{
	int	*fd;
	int	i;
	int	status;

	if (size <= 0)
		return (NULL);
	fd = (int *)malloc(sizeof(int) * (size - 1) * 2);
	if (!fd)
		perror("could't allocate memory !");
	i = 0;
	while (i < size - 1)
	{
		status = pipe(&fd[i * 2]);
		if (status < 0)
			perror("init pipes faild !");
		i++;
	}
	return (fd);
}

void	close_pipes(int *fd, int size)
{
	int	i;

	i = 0;
	while (i < (size - 1) * 2)
	{
		close(fd[i]);
		i++;
	}
	free(fd);
}

void	output_tofile(t_cmd *cmd)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		status = dup2(cmd->fd_out, 1);
		if (status < 0)
			perror("dup2 faild");
		execve(cmd->command[0], cmd->command, NULL);
		perror("exec faild");
	}
	else if (pid > 0)
	{
		wait(&status);
		kill(pid, 9);
	}
}

void	close_iofd(t_cmd *cmd)
{
	if (cmd->fd_in > 2)
		close(cmd->fd_in);
	if (cmd->fd_out > 2)
		close(cmd->fd_out);
}

void	merge_input(int fdpipe, int fdfile)
{
	int		readed;
	char	buff[1];

	readed = read(fdfile, buff, 1);
	while (readed >= 1)
	{
		write(fdpipe, buff, 1);
		readed = read(fdfile, buff, 1);
	}
}
