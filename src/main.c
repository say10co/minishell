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

static bool trace_quote_dquote(char *prefix, char **p_prompt)
{
	unsigned int		i;
	static int			open_quote;

	i = 0;
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
		i++;
	}
	if (open_quote == DQUOTE)
	{
		*p_prompt = "dquote> ";
		return (1);
	}
	else if (open_quote == QUOTE)
	{	
		*p_prompt = "quote> ";
		return (1);
	}
	return (0);
}

char *get_valid_line(void)
{
	char	*f_command;
	char	*command;
	char 	*prompt;
	char 	*tmp;
	bool	start;
	
	start = 1;
	prompt = "miniSHELL-0.0$ ";
	command = readline(prompt);
	while (1)
	{
		if (start)
		{
			f_command = ft_strdup(command);
			start = 0;
		}
		else
		{
			command = append(command, "\n");
			tmp = f_command;
			f_command = ft_strjoin(f_command, command);
			free(tmp);
		}
		if (!trace_quote_dquote(command, &prompt))
				break;
		free(command);
		command = readline(prompt);
	}
	if (start)
		return (command);
	free(command);
	return (f_command);	
}

int main(void)
{
	char	*command;
	char	*t_command;

	while (1)
	{
		command = get_valid_line();
		if (command)
			add_history(command);
		t_command = ft_strtrim(command, " \t");
		free(command);
		command = t_command;
		printf("%s\n", t_command);
		//system(command);
		free(command);
	}
	return (0);
}
