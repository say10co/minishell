/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adriouic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 14:59:25 by adriouic          #+#    #+#             */
/*   Updated: 2022/04/05 15:36:30 by adriouic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/includes.h"

char *expand_variables(char *key)
{
	return (key);
}

int	open_file(char *file_name, int mode)
{
	int fd;

	if (file_name[0] == '$')
		expand_variables(file_name + 1);
	if (mode == O_RDONLY)
	{
		if (access(file_name, F_OK) != 0)
			return (printf("Error : No such file '%s'\n", file_name) * 0);
		fd = 0; //open(file_name, O_RDONLY);
	}
	else
		fd = 0; //open(file_name, O_CREAT | O_WRONLY | mode);
	if (fd < 0)
		return (printf("Error : Permission Denied\n") * 0);
	return (fd);
}

void remove_quotes(char **all)
{
	int		i;
	char	*tmp;

	i = 0;
	while (all[i])
	{
		tmp = all[i];
		all[i] = polish(all[i], "\'\"");
		free(tmp);
		i++;
	}
}

void	open_deocument(char *eof)
{
	char *buffer;

	
	while (1)
	{
		buffer = readline("heredoc> ");
		printf("[%s] [%s]\n", buffer, eof);
		if (!ft_strcmp(buffer, eof))
			break;
		write(3, buffer,ft_strlen(buffer));
		free(buffer);
	}
}

t_command *parser(char *field)
{
	int		i;
	char	**all;
	t_command *command;

	i = 0;
	command = (t_command *)malloc(sizeof(t_command));
	ft_bzero(command, sizeof(t_command));
	all = my_ft_split(field, ' ');
	command->cmd = NULL; 
	remove_quotes(all);

	while (all[i])
	{
		if (!ft_strcmp(all[i], ">") || !ft_strcmp(all[i], ">>"))
		{
			command->append = !ft_strcmp(all[i], ">>");
			if (command->append)
			{
				if (command->out_file)
					close(command->out_file);
				command->out_file = open_file(all[++i], O_APPEND);
			}
			else
			{
				if (command->out_file)
					close(command->out_file);
				command->out_file = open_file(all[++i], O_WRONLY);
			}
		}
		else if (!ft_strcmp(all[i], "<"))
			command->in_file = open_file(all[++i], 0);
		else if (!ft_strcmp(all[i], "<<"))
			open_deocument(all[++i]);
		i++;
	}
	return(command);
}
