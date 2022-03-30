/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adriouic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 11:19:28 by adriouic          #+#    #+#             */
/*   Updated: 2022/03/30 20:29:51 by adriouic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/includes.h"


char *append(char *prefix, const char *sufix)
{
	char *joined_str;

	joined_str = ft_strjoin(prefix, sufix);
	free(prefix);
	return (joined_str);
}

bool is_even(int x)
{
	return (x % 2 == 0);
}

static int trace_quote_dquote(char *prefix)
{
	unsigned int		i;
	unsigned int		j;
	unsigned int		open_quote;

	i = 0;
	j = 1;
	open_quote = NONE;
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

static char *polish(char *s)
{
	char *polished;

	polished = ft_strtrim((const char *)s, " ");
	free(s);
	if (polished[0] == '\0')
		return (NULL);
	return (polished);
	
}

void 	free_befor_i(char **lst, int end)
{
	int i;

	i = -1;
	while (++i < end)
		free(lst[i]);
}

static	char **get_fields(char *line, unsigned int nb_fields)
{
	char			**res;
	unsigned int	i;
	unsigned int	j;
	unsigned int	start;
	unsigned int		open_quote;

	open_quote = NONE;
	res = (char **)(malloc(sizeof(char *) * nb_fields + 1));
	if(!res)
		return (NULL);
	start = 0;
	i = 0;
	j = 0;
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
		if (open_quote == NONE && (line[i] == '|' || (!line[i+1] && ++i)))
		{
			res[j] =  polish(ft_substr(line, start, i - start));	
			if (!res[j] || (line[i] == '|' && !line[i + 1]))
			{
				free_befor_i(res, i);
				free(res);
				ft_putstr_fd("parse error near `|'\n", 2);
				return (NULL);
			}
			printf("%s<>\n", res[j]);
			j++;
			start = (i+1);
		}
		i++;
	}
	res[nb_fields] = NULL;
	return (res);
}

void print_pipe_fildes(char **a)
{
	int	i = 0;
	while (a[i])
	{
		//printf(">>> %s\n", a[i]);
		i++;
	}
}

int main(void)
{
	char	*command;
	char 	**fields;
	int		nb_fields; 
	
	while (1)
	{
		command = readline("MiniShell-0.0$ ");
		nb_fields = trace_quote_dquote(command);
		printf("number of fields %d\n", nb_fields);
		if (command && nb_fields)
		{
			fields =  get_fields(command, nb_fields);
			if (!fields)
			{
				free(command);
				continue;
			}
			add_history(command);
			print_pipe_fildes(fields);
		}
	}
	return (0);
}
