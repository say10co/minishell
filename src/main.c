/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adriouic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 11:19:28 by adriouic          #+#    #+#             */
/*   Updated: 2022/04/02 19:20:21 by adriouic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/includes.h"


typedef struct s_simple_command
{
	char *simple_command;
	int		in_file;
	int		out_file;

}t_simple_command;

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


bool	veriffy_syntax(char *s, t_list **lst)
{
	int 	start;
	int 	i;
	bool	text_found;
	bool	keyword_found;
	bool 	error;

	*lst = NULL;
	keyword_found = 0;
	text_found = 0;
	error = 0;
	start = 0;
	i = 0;
	printf("%s\n", s);
	while (s[i] && !error)
	{
		if ((s[i] == '>' && keyword_found && !text_found ) || (s[i] == '<' && keyword_found && !text_found))
			error = 1;
		if ((!keyword_found && s[i] == '>' && s[i+1] == '>' && ++i) ||
				(!keyword_found && s[i] == '<' && s[i+1] == '<' && ++i))
			keyword_found = 1;
		if (!keyword_found && (s[i] == '>' || s[i] == '<'))
			keyword_found = 1;
		if (keyword_found && !text_found && s[i] != '>' && s[i] != '<' && s[i] != ' ')
		{
			start = i;
			text_found = 1;
		}
		if (keyword_found && text_found && (s[i] == ' ' || !s[i+1]))
		{
			if (!s[i+1])
				ft_lstadd_back(lst, ft_lstnew(ft_substr(s, start, i - start + 1)));
			else
				ft_lstadd_back(lst, ft_lstnew(ft_substr(s, start, i - start)));
			keyword_found = 0;
			text_found = 0;
			start = 0;
		}
		i++;
	}
	if (error || (keyword_found && !text_found))
		printf("minishell: syntax error near unexpected token while parsing.\n");
	return (error);
}

bool parse_fielfs(int ac, char **argv)
{
	int					i;
	t_list				*file_names;
	t_list 				*curr;

	i = 0;
	while (i < ac)
	{
		if (!ft_strchr(argv[i], '>' ) || !(ft_strchr(argv[i], '<'))) 
		{
		if (veriffy_syntax(argv[i], &file_names))
		{
			i = 0;
			while (argv[i])
				free(argv[i++]);
			free(argv);
			return (1);
		}
		printf("%s Ok\n", argv[i]);
		if (ft_strchr(argv[i], '>'))
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
		if (parse_fielfs(ac, argv))
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
