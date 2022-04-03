/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adriouic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 11:19:28 by adriouic          #+#    #+#             */
/*   Updated: 2022/04/03 20:17:14 by adriouic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/includes.h"
char	**my_ft_split(const char *str, char c);
enum
{
	RARROW,
	LARROW,
	DRARROW,
	DLARROW,
};

typedef struct s_simple_command
{
	char *simple_command;
	int		in_file;
	int		out_file;

}t_simple_command;

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

void	expand_variables(char **all);

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

void parser(char *field)
{
	int	i;
	char **all;
	char *outfile;
	char *infile;

	i = 0;
	infile = NULL;
	outfile = NULL;
	all = my_ft_split(field, ' ');
	remove_quotes(all);
	//expand_variables(all);
	while (all[i])
	{
		if (!ft_strcmp(all[i], ">") || !ft_strcmp(all[i], ">>"))
			outfile = all[i + 1];
		if (!ft_strcmp(all[i], "<"))
			infile = all[i + 1];
		if (!ft_strcmp(all[i], "<<"))
			open_deocument(all[i + 1]);
		i++;
	}
	printf("IN FILE:[%s]\n", infile);
	printf("OUT FILE:[%s]\n", outfile);
}

bool get_data_from_subfield(char **fields)
{
	int i;

	i = 0;
	while (fields[i])
	{
		if (veriffy_syntax(fields[i]))
			return 1;
		parser(fields[i]);
		i++;
	}
	return (0);
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
		get_data_from_subfield(argv);
		continue;
		for(int i = 0; (argv && argv[i] != NULL); i++)
		{
			printf("Field %d: %s \n", i, argv[i]);
			free(argv[i]);
		}
		free(argv);
	}
	return (0);
}
