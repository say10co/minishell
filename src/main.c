/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adriouic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 11:19:28 by adriouic          #+#    #+#             */
/*   Updated: 2022/04/04 18:26:31 by adriouic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <fcntl.h>

#include "../includes/includes.h"
char	**my_ft_split(const char *str, char c);
enum
{
	RARROW,
	LARROW,
	DRARROW,
	DLARROW,
};

typedef struct s_command
{
	char 	**cmd;
	int		in_file;
	int		out_file;
	int		nb_pipes;
	int		append;

}t_command;

char *polish(const char *s, char *charset);

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t			index;
	unsigned char	*ts1;
	unsigned char	*ts2;

	ts1 = (unsigned char *)s1;
	ts2 = (unsigned char *)s2;
	index = 0;
	while (ts1[index] != '\0' && ts2[index] != '\0')
	{
		if (ts1[index] == ts2[index])
			index++;
		else
			return (ts1[index] - ts2[index]);
	}
	return (ts1[index] - ts2[index]);
}

bool	veriffy_syntax(char *s)
{
	int 	i;
	bool	text_found;
	bool	keyword_found;
	bool 	error;
	char	quote;

	keyword_found = 0;
	text_found = 0;
	error = 0;
	i = 0;
	quote = 0;
	while (s[i] && !error)
	{
		if ((s[i] == '"' && !quote) || (s[i] == '\'' && !quote) )
			quote = s[i];
		else if (s[i] == quote)
			quote = 0;
		if (!quote && ((s[i] == '>' && keyword_found && !text_found ) || (s[i] == '<' && keyword_found && !text_found)))
			error = 1;
		if (!quote && !keyword_found && s[i] == '>' && s[i+1] == '>' && ++i)
			keyword_found = 1;
		if (!quote && !keyword_found && s[i] == '<' && s[i+1] == '<' && ++i)
			keyword_found = 1;
		if (!quote && !keyword_found && (s[i] == '>' || s[i] == '<'))
			keyword_found = 1;
		if (!quote && keyword_found && !text_found && s[i] != '>' && s[i] != '<' && s[i] != ' ')
			text_found = 1;
		if (!quote && keyword_found && text_found && (s[i] == ' ' || !s[i+1]))
		{
			keyword_found = 0;
			text_found = 0;
		}
		i++;
	}
	if (error || (keyword_found && !text_found))
		printf("minishell: unexpected token while parsing.\n");
	return (error);
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

char *expand_variables(char *key)
{
	return (key);
}

int	open_file(char *file_name, int flag)
{
	int fd;

	if (file_name[0] == '$')
		expand_variables(file_name + 1);
	if (flag == O_WRONLY)
		fd = open(file_name, flag | O_CREAT);
	else
		fd = open(file_name, flag);
	printf("fd %d \n", fd);
	return (fd);
}

t_command *parser(char *field)
{
	int	i;
	char **all;
	t_command *command;

	i = 0;
	command = (t_command *)malloc(sizeof(t_command));
	all = my_ft_split(field, ' ');
	command->cmd = NULL; 
	remove_quotes(all);
	while (all[i])
	{
		if (!ft_strcmp(all[i], ">") || !ft_strcmp(all[i], ">>"))
		{
			command->append = !ft_strcmp(all[i], ">>");
			command->out_file = open_file(all[++i], O_WRONLY);
		}
		else if (!ft_strcmp(all[i], "<"))
			command->in_file = open_file(all[++i], O_WRONLY);
		else if (!ft_strcmp(all[i], "<<"))
			open_deocument(all[++i]);
		i++;
	}
	return(command);
}

bool get_data_from_subfield(int ac, char **fields, t_command ***all_commands)
{
	int i;

	i = 0;
	*all_commands = (t_command **) malloc(sizeof(t_command) * ac);
	while (fields[i])
	{
		if (veriffy_syntax(fields[i]))
			return 1;
		(*all_commands)[i] = parser(fields[i]);
		i++;
	}
	return (0);
}

t_list *create_env(char **env)
{
	t_list	*head;
	t_list	*tmp;
	int		i;

	head = NULL;
	i = 0;
	while (env[i])
	{
		tmp = ft_lstnew(env[i]);
		if (!tmp)
		{
			ft_lstclear(&head, free);
			return (NULL);
		}	
		ft_lstadd_front(&head, tmp);
		i++;
	}
	return (head);
}

int main(int ac, char **argv, char **env)
{
	t_list		*enviorment;
	t_command	**all_commands;
	
	enviorment = create_env(env);
	argv = NULL;
	all_commands = NULL;
	while (1)
	{
		ac = get_pipe_fileds(&argv);
		if (!ac)
			continue ;
		get_data_from_subfield(ac, argv, &all_commands);
		for(int i = 0; (argv && argv[i] != NULL); i++)
		{
			printf("_________Field %d ______:\n	::: %s \n", i, argv[i]);
			printf("command %s\n", NULL);
			printf("input fd : %d\n", all_commands[i]->in_file);
			printf("output fd : %d\n", all_commands[i]->out_file);
			free(argv[i]);
		}
		free(argv);
	}
	return (0);
}
