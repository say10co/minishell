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

static bool trace_quote_dquote(char *prefix)
{
	unsigned int		i;
	unsigned int		open_quote;

	i = 0;
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
		i++;
	}
	if (open_quote == DQUOTE)
	{
		ft_putstr_fd("[Error] Double Quote Unclosed!\n" ,2);
		return (1);
	}
	if (open_quote == QUOTE)
	{
		ft_putstr_fd("[Error] Single Quote Unclosed!\n" ,2);
		return (1);
	}
	return (0);
}

int main(void)
{
	char	*command;

	while (1)
	{
		command = readline("MiniShell-0.0$ ");
		if (command && !trace_quote_dquote(command))
			add_history(command);
		//system(command);
		free(command);
	}
	return (0);
}
