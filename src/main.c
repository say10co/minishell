
#include "../includes/lexer.h"
#include "../includes/includes.h"
#include "../libft/libft.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

t_list *g_env;

// Temporary functions
//
void print_env_g();
void print_env(t_list *env);
void display_logo(void);
void print_tokens(t_token_list *lst);
void print_command_data(t_list *lst);
void print_env_g();
void print_env_g();

// End Temporary functions

char *get_foldername()
{
	char str[4096];
	char *tmp;

	getcwd(str, 4096);
	tmp = ft_strrchr(str, '/');
	if (!tmp[1])
		return (ft_strjoin("➜ \e\033[0;33m", "/"));
	return (ft_strjoin("➜ \e\033[0;33m", tmp + 1));
}

t_list *parse_command(char *cmd)
{
	t_token_list *tokens;
	t_list *command_list;

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
	// print_env(*local_env);
	// print_command_data(command_list);
	destroy_token_list(tokens);
	return (command_list);
}

char *get_cmd()
{
	char *cmd;
	char *dir;
	char *tmp;

	dir = get_foldername();
	tmp = dir;
	dir = ft_strjoin(dir, " \e\033[0;37m");
	cmd = readline(dir);
	free(dir);
	free(tmp);
	return (cmd);
}

int main(int ac, char **av, char **env)
{
	t_list *command_list;
	char *cmd;
	char *t;

	(void)(av);

	signal(SIGINT, handler);
	signal(SIGQUIT, SIG_IGN);

	display_logo();
	ft_initenv(env);
	while (ac)
	{
		t = get_foldername();
		// cmd = readline("\e\033[0;33mmsh$ \e\033[0;37m");
		cmd = get_cmd();
		if (!cmd)
			b_exit();
		command_list = parse_command(cmd);
		if (command_list)
		{
			exec_cmd(command_list);
			unlink("/tmp/minishell-dumy_file-0ew3d");
			add_history(cmd);
		}
		// print_env_g();
		ft_lstclear(&command_list, free);
		free(command_list);
		free(cmd);
	}
}
