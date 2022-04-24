/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adriouic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 02:33:48 by adriouic          #+#    #+#             */
/*   Updated: 2022/04/24 08:03:48 by adriouic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/includes.h"

char is_qouted(char *s)
{
	char *t;
	
	t = ft_strchr(s, '\'');
	if (t)
		return (*t);
	t = ft_strchr(s, '\"');
	if (t)
		return (*t);
	return (0);
}

void	heredoc(char *eof, t_cmd *cmd)
{
	t_list	*str_lst;
	char	*buffer;
	int		length;
	int		fd;

	str_lst = NULL;
	fd = open("/tmp/minishell-dumy_file-0ew3d",
			O_CREAT | O_APPEND | O_WRONLY, 0600);
	while (1)
	{
		length = 0;
		buffer = readline("\033[0;31mheredoc> ");
		if (!ft_strcmp(buffer, eof))
			break ;
		if (ft_strchr(buffer, '$'))
			ft_putstr_fd(get_values(buffer, &str_lst, is_qouted(buffer)), fd);
		else
			write(fd, buffer, ft_strlen(buffer));
		write(fd, "\n", 1);
		free(buffer);
	}
	close(fd);
	fd = open("/tmp/minishell-dumy_file-0ew3d", O_RDONLY);
	cmd->fd_in = fd;
	printf("\e\033[0;37m");
	free(buffer);
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

void	open_file(t_cmd *cmd, t_token *t, char *file_name)
{
	if (t->type == R_ARROW && cmd->error_free)
		cmd->fd_out = close_old_open_new(cmd, file_name, O_TRUNC, cmd->fd_out);
	else if (t->type == DR_ARROW && cmd->error_free)
		cmd->fd_out = close_old_open_new(cmd, file_name, O_APPEND, cmd->fd_out);
	else if (t->type == L_ARROW && cmd->error_free)
		cmd->fd_in = close_old_open_new(cmd, file_name, O_RDONLY, cmd->fd_in);
}

void	close_files(t_cmd *cmd)
{
	if (cmd->fd_in > 3)
		close(cmd->fd_in);
	if (cmd->fd_out > 3)
		close(cmd->fd_out);
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
