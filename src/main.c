#include "../includes/lexer.h"
#include "../includes/includes.h"

t_list	*g_env;

char	*get_foldername(void)

{
	char	str[4096];
	char	*tmp;

	getcwd(str, 4096);
	tmp = ft_strrchr(str, '/');
	if (!tmp[1])
		return (ft_strjoin("➜ \e\033[0;33m", "/"));
	return (ft_strjoin("➜ \e\033[0;33m", tmp + 1));
}

t_list	*parse_command(char *cmd)
{
	t_token_list	*tokens;
	t_list			*command_list;

	command_list = NULL;
	tokens = get_tokens(cmd);
	if (!tokens)
		return (NULL);
	if (n_parser(tokens))
	{
		destroy_token_list(tokens);
		return (NULL);
	}
	command_list = parser_one(tokens);
	destroy_token_list(tokens);
	return (command_list);
}

char	*get_cmd(void)

{
	char	*cmd;
	char	*dir;
	char	*tmp;

	dir = get_foldername();
	tmp = dir;
	dir = ft_strjoin(dir, " \e\033[0;37m");
	cmd = readline(dir);
	free(dir);
	free(tmp);
	return (cmd);
}

int	main(int ac, char **av, char **env)
{
	t_list	*command_list;
	char	*cmd;

	(void)av;
	signal(SIGINT, handler);
	signal(SIGQUIT, SIG_IGN);
	display_logo();
	ft_initenv(env);
	while (ac)
	{
		cmd = get_cmd();
		if(!cmd)
			b_exit();
		command_list = parse_command(cmd);
		if (command_list)
		{
			exec_cmd(command_list, env);
			unlink("/tmp/minishell-dumy_file-0ew3d");
			add_history(cmd);
		}
		ft_lstclear(&command_list, free);
		free(command_list);
		free(cmd);
	}
}
