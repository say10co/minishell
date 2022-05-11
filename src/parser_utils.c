/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macplus <macplus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 02:33:48 by adriouic          #+#    #+#             */
/*   Updated: 2022/05/11 23:26:20 by adriouic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/includes.h"

void	run_child(int fd, char *eof, t_list **str_lst)
{
	char	*buffer;

	buffer = NULL;
	signal(SIGINT, handler_herdoc);
	while (1)
	{
		buffer = slice_nl(get_next_line(0));
		if (!buffer || !ft_strcmp(buffer, eof))
			break ;
		if (ft_strchr(buffer, '$'))
			ft_putstr_fd(get_values(buffer, str_lst, is_qouted(buffer)), fd);
		else
			write(fd, buffer, ft_strlen(buffer));
		write(fd, "\n", 1);
		free(buffer);
	}
	free(buffer);
}

bool	heredoc(char *eof, t_cmd *cmd)
{
	t_list	*str_lst;
	int		fd;
	int		tmp;
	pid_t	pid;

	tmp = cmd->error_free;
	cmd->fd_in = 0;
	str_lst = NULL;
	fd = open("/tmp/dumy_file-0ew3d", O_CREAT | O_APPEND | O_WRONLY, 0600);
	cmd->error_free = 0;
	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid == 0)
		run_child(fd, eof, &str_lst);
	else
		wait(NULL);
	if (kill(pid, 0) != -1)
	{
		close(fd);
		fd = open("/tmp/dumy_file-0ew3d", O_RDONLY);
		cmd->fd_in = fd;
		cmd->error_free = tmp;
	}
	signal(SIGINT, handler);
	return (1);
}

int	close_old_open_new(t_cmd *cmd, char *file_name, int mode, int old_fd)
{
	int	fd;

	if (old_fd > 2)
		close(old_fd);
	if (mode == O_RDONLY)
	{
		if (access(file_name, F_OK) != 0)
		{
			cmd->error_free = 0;
			return (printf("%s: %s\n", file_name, FILENTFOUND) * 0);
		}
		fd = open(file_name, O_RDONLY);
	}
	else
		fd = open(file_name, O_CREAT | O_WRONLY | mode, 06644);
	if (fd < 0)
	{
		cmd->error_free = 0;
		return (printf("msh: %s: %s\n", file_name, PERMISSION) * 0);
	}
	return (fd);
}

void	append_to_lst(char ***vector, char *elem, size_t *vector_size)
{
	char	**tmp;

	if (!elem || !elem[0])
		return ;
	if (*vector == NULL)
	{
		*vector = (char **)malloc(sizeof(char *) * 2);
		(*vector)[0] = ft_strdup(elem);
		*vector_size += 1;
	}
	else
	{
		tmp = *vector;
		*vector = (char **)malloc(sizeof(char *) * (*vector_size + 2));
		ft_memmove(*vector, tmp, sizeof(char *) * *vector_size);
		(*vector)[*vector_size] = ft_strdup(elem);
		free(tmp);
		*vector_size += 1;
	}
	(*vector)[*vector_size] = NULL;
}
