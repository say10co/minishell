/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_state.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adriouic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 10:04:59 by adriouic          #+#    #+#             */
/*   Updated: 2022/04/03 20:09:09 by adriouic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/includes.h"

static int trace_quote_dquote(char *prefix)
{
	unsigned int		i;
	unsigned int		j;
	unsigned int		open_quote;

	i = 0;
	j = 1;
	open_quote = NONE;
	if (!prefix)
		return (0);
	while (prefix[i])
	{
		if (prefix[i] == '"' && open_quote == NONE)
			open_quote = DQUOTE;
		else if (prefix[i] == '"' && open_quote == DQUOTE)
			open_quote = NONE;
		if (prefix[i] == '\'' && open_quote == NONE)
			open_quote = QUOTE;
		else if (prefix[i] == '\'' && open_quote == QUOTE)
			open_quote = NONE;
		if (open_quote == NONE && prefix[i] == '|')
				j += 1;
		i++;
	}
	if (open_quote == DQUOTE)
	{
		ft_putstr_fd("[Error] Double Quote Unclosed!\n" ,2);
		return (0);
	}
	if (open_quote == QUOTE)
	{
		ft_putstr_fd("[Error] Single Quote Unclosed!\n" ,2);
		return (0);
	}
	return (j);
}

char *polish(const char *s, char *charset)
{
	char *polished;

	polished = ft_strtrim(s, charset);
	if (polished[0] == '\0')
	{
		free(polished);
		return (NULL);
	}
	return (polished);
	
}

static	char *get_fields(char *line, int *end)
{
	unsigned int	i;
	unsigned int	open_quote;
	char			*return_value;

	i = 0;
	open_quote = NONE;
	if(!line[0])
		return (NULL);
	while (line[i])
	{
		if (line[i] == '"' && open_quote == NONE)
			open_quote = DQUOTE;
		else if (line[i] == '"' && open_quote == DQUOTE)
			open_quote = NONE;
		if (line[i] == '\'' && open_quote == NONE)
			open_quote = QUOTE;
		else if (line[i] == '\'' && open_quote == QUOTE)
			open_quote = NONE;
		if (open_quote == NONE && line[i] == '|')
		{	
			line[i] = '\0';
			return_value = polish(line, " ");
			line[i] = '|';
			*end += i + 1;
			return (return_value);
		}
		i++;
	}
	*end += i;
	return (polish(line, " "));
}

int	get_pipe_fileds(char ***all_fields)
{
	char	*command;
	char 	*field;
	int		nb_fields; 
	int		end;
	int		index;
	

	command = readline("MiniShell-0.0$ ");
	nb_fields = trace_quote_dquote(command);
	if (!nb_fields)
		return (0);
	*all_fields = (char **)(malloc(sizeof(char *) * nb_fields + 1));
	end = 0;
	index = 0;
	while (1)
	{
		field =  get_fields(command + end, &end);
		if (!field)
			break ;
		else
			(*all_fields)[index++] = field;
	}
	if (nb_fields != index )
	{
		ft_putstr_fd("[Error] Error When Parsing Pipes.\n",2);
		free_befor_end(*all_fields, index);
		free(*all_fields);
		free(command);
		return (0);
	}
	add_history(command);
	free(command);
	(*all_fields)[nb_fields] = NULL;
	return (index);
}
