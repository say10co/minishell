
#include "../includes/lexer.h"
#include "../includes/includes.h"
#include "../libft/libft.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

t_list *genv;

// Temporary functions 
//
void	print_env_g();
void	print_env(t_list *env);
void	display_logo(void);
void	print_tokens(t_token_list *lst);
void	print_command_data(t_list *lst);
void	print_env_g();
void	print_env_g();

// End Temporary functions

t_list *parse_command(char *cmd)
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
	//print_env(*local_env);
	print_command_data(command_list);
	//destroy_token_list(tokens);
	return (command_list);
}


int main(int ac, char **av, char **env)
{
	t_list		*command_list;
	char		*cmd;

	(void)(av);

	display_logo();
  ft_initenv(env);
	while (ac)
	{
		cmd = readline("\e\033[0;33mmsh$ \e\033[0;37m");
		command_list = parse_command(cmd);
		add_history(cmd);
		exec_cmd(command_list, env);
		//print_env_g();
		ft_lstclear(&command_list, free);
		free(command_list); 
		free(cmd);
	}
}

