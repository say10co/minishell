/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adriouic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 14:41:37 by adriouic          #+#    #+#             */
/*   Updated: 2022/04/06 14:09:53 by adriouic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/includes.h"

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





void	free_on_error(t_command **memory, int size)
{
	int i;
	
	i = 0;
	while (i < size)
		free(memory[i++]);
	free(memory);
}

bool get_data_from_subfield(int ac, char **fields, t_command ***all_commands)
{
	int i;

	i = 0;
	*all_commands = (t_command **)malloc(sizeof(t_command) * ac);
	if (!all_commands)
		return (0);
	while (fields[i])
	{
		if (veriffy_syntax(fields[i]))
		{
			free_on_error(*all_commands, ac);
			*all_commands = NULL;
			return 1;
		}
		(*all_commands)[i] = parser(fields[i]);
		i++;
	}
	return (0);
}

