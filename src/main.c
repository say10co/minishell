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
	static unsigned int	quote;
	static unsigned int dquote;
	unsigned int		i;

	i = 0;
	while (prefix[i])
	{
		if (prefix[i] == '"')
			dquote += 1;
		if (prefix[i] == 44)
			quote += 1;
		i++;
	}
	if (! is_even(dquote) && ( dquote < quote || !quote))
	{
		*p_prompt = "dquote> ";
		return (1);
	}
	else if (! is_even(quote) && (quote < dquote || !dquote))
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
	bool	start;
	
	start = 1;
	prompt = "minishell-0.0$ ";
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
			f_command = ft_strjoin(f_command, command);
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
		printf("%s\n", command);
		free(command);
		command = t_command;
		//system(command);
		free(command);
	}
	return (0);
}
