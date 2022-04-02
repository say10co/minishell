/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adriouic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 11:19:28 by adriouic          #+#    #+#             */
/*   Updated: 2022/04/02 12:32:59 by adriouic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/includes.h"


typedef struct s_simple_command
{
	char *simple_command;
	int		in_file;
	int		out_file;

}t_simple_command;

/*
char *quoted_line(char *line)
{
	char *d_quote;

	d_quote = ft_strnstr(line, '\"');
	if (d_quote)
	{
		//get_back soon
		return (0);
	}
	return (0);
}
*/

char *get_filename(char *s)
{
	int		i;
	int		start;
	char	delemiter;
	bool	text_found;

	i = 0;
	delemiter = ' ';
	text_found = 0;
	while (s[i])
	{
		if (s[i] == delemiter && text_found)
			break;
		else if ((s[i] == '\'' || s[i] == '\"') && !text_found)
		{
			start = i;
			text_found = 1;
			delemiter = s[i];
		}
		else if (s[i] != delemiter && !text_found)
		{
			start = i;
			text_found = 1;
		}
		i++;
	}
	if (text_found)
		return (ft_substr(s, start,  i - start));
	return (NULL);

}

void construct_command(char *field)//, t_simple_command *cmd)
{
	int		i;

	i = 0;
	while (field[i])
	{
		if (field[i] == '>')
		{
			char * file_name = get_filename(field + i + 1);
			printf("file name :[%s]\n", file_name);
			free(file_name);
		}
		i++;
	}
}

void 	parse_fielf(int ac, char **argv)
{
	t_simple_command	*commands;
	int					i;

	commands = (t_simple_command *) malloc(sizeof(t_simple_command) * ac);
	i = 0;
	while (i < ac)
	{
		construct_command(argv[i]);
		i++;
	}
	return ;



}

bool	veriffy_syntax(char *s)
{
	int i;
	bool	text_found;
	bool	keyword_found;
	bool 	error;

	keyword_found = 0;
	text_found = 0;
	error = 0;
	i = 0;
	// debugl
	
	int start = 0;
	while (s[i] && !error)
	{
		// Found >> for the secons time
		if (s[i] == '>' && keyword_found && !text_found)
			error = 1;
		if (s[i] == '<' && keyword_found && !text_found)
			error = 1;
		if (!keyword_found && s[i] == '>' && s[i+1] == '>')
		{
			i++;
			keyword_found = 1;
		}
		if (!keyword_found && s[i] == '<' && s[i+1] == '<')
		{
			i++;
			keyword_found = 1;
		}
		if (!keyword_found && (s[i] == '>' || s[i] == '<'))
			keyword_found = 1;
		if (keyword_found && s[i] != '>' && s[i] != '>' && s[i] != ' ')
		{
			start = i;
			text_found = 1;
		}
		i++;
	
	}
	if (error || (keyword_found && !text_found))
		printf("minishell: syntax error near unexpected token while parsing.\n");
	return (error);
}

void 	parse_fielfs(int ac, char **argv)
{
	int					i;

	i = 0;
	printf(" i == %d ac ==  %d\n", i, ac);
	while (i < ac)
	{
		if (veriffy_syntax(argv[i]))
			break;
		else
			printf("Argument %d Veriffied [X]\n", i);
		i++;
	}
	return ;

}

int main(void)
{
	char **argv;
	int		ac;

	argv = NULL;
	while (1)
	{
		ac = get_pipe_fileds(&argv);
		if (!ac)
			continue ;
		parse_fielfs(ac, argv);
		continue;
		for(int i = 0; (argv && argv[i] != '\0'); i++)
		{
			printf("Field %d: %s \n", i, argv[i]);
			free(argv[i]);
		}
		free(argv);
	}
	return (0);
}
