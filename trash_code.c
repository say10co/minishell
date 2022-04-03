/*
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


bool	veriffy_syntax(char **s)
{
	bool 	error;
	int 	i;
	int		keyword_index;
	int		prev_index;

	error = 0;
	i = 0;
	keyword_index = -1;
	prev_index = -1;
	while (s[i] && !error)
	{
		prev_index = keyword_index;
		if (!ft_strcmp(s[i], "<<") || !ft_strcmp(s[i], ">>"))
			keyword_index = i;
		else if (!ft_strcmp(s[i], ">") || !ft_strcmp(s[i], "<"))
			keyword_index = i;
		if (keyword_index == prev_index + 1 )
			error = 1;
		i++;
	}
	if (error)
		printf("minishell: unexpected token while parsing.\n");
	return (error);
}

bool	veriffy_syntax(char *s)
{
	int 	i;
	bool	text_found;
	bool	keyword_found;
	bool 	error;
	char	*quote;

	keyword_found = 0;
	text_found = 0;
	error = 0;
	i = 0;
	while (s[i] && !error)
	{
		if ((s[i] == '"' && !quote) || (s[i] == '\'' && !quote) )
			quote = s[i];
		else if (s[i] == quote)
			quote = 0;
		if ((s[i] == '>' && keyword_found && !text_found ) || (s[i] == '<' && keyword_found && !text_found))
			error = 1;
		if (!keyword_found && s[i] == '>' && s[i+1] == '>' && ++i)
			keyword_found = 1;
		if (!keyword_found && s[i] == '<' && s[i+1] == '<' && ++i)
			keyword_found = 1;
		if (!keyword_found && (s[i] == '>' || s[i] == '<'))
			keyword_found = 1;
		if (keyword_found && !text_found && s[i] != '>' && s[i] != '<' && s[i] != ' ')
			text_found = 1;
		if (keyword_found && text_found && (s[i] == ' ' || !s[i+1]))
		{
			keyword_found = 0;
			text_found = 0;
		}
		i++;
	}
	if (error || (keyword_found && !text_found))
		printf("minishell: syntax error near unexpected token while parsing.\n");
	return (error);
}

bool get_redirection_fileames(char **fields, t_list **file_names, int *keyword, int i)
{
	if (veriffy_syntax(fields[i], file_names, keyword))
	{
		i = 0;
		while (fields[i])
			free(fields[i++]);
		free(fields);
		return (1);
	}
	return (0);
}

bool parse_fielfs(int ac, char **argv)
{
	int					i;
	int					keyword;
	t_list				*file_names;
	t_list 				*curr;

	i = 0;
	while (i < ac)
	{
		if (ft_strchr(argv[i], '>' ) || (ft_strchr(argv[i], '<'))) 
		{
			if (get_redirection_fileames(argv, &file_names, &keyword, i))
				return (1);
			if (veriffy_syntax(argv[i], &file_names, &keyword))
			{
				i = 0;
				while (argv[i])
					free(argv[i++]);
				free(argv);
				return (1);
			}
			printf("Key is %d\n", keyword);
			curr = file_names;
			while (curr)
			{
				printf("file name [%s]\n", (char *)curr->content);
				curr = curr->next;
			}
			ft_lstclear(&file_names, free);
		}

		i++;
	}
	return (0);
}
*/

