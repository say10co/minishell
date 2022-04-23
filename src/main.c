
#include "../includes/lexer.h"
#include "../includes/includes.h"
#include "../libft/libft.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

void	print_env(t_list *env)
{
	while (env)
	{
		printf("->%s\n", (char *)env->content);
		env = env->next;
	}
	printf("Done printing env\n");
}

void display_logo(void)
{
	char *logo;
	int	fd;

	logo = (char *)malloc(sizeof(char) * 330);
	fd = open("logo.txt", O_RDONLY);
	read(fd, logo, 329);
	//printf("\e\033[0;33m %s\n", logo);
	printf("\e[0;92m %s\n", logo);
	printf("\e\033[0;37m");
	close(fd);
	free(logo);
}

void destroy_token_list(t_token_list *tokens)
{
	t_token *curr;
	t_token *tmp;

	curr = tokens->all;
	while (curr)
	{
		free(curr->data);
		tmp = curr;
		curr = curr->next_token;
		free(tmp);
	}
	free(tokens);
}

void	print_tokens(t_token_list *lst)
{
	t_token		*t;

	t = lst->all;
	while (t)
	{
		printf("--/-: [%s] {%p}\n", t->data, t->next_token);
		t = t->next_token;
	}
}

void	destroy_command(t_cmd * cmd)
{
	int	i;

	i = 0;
	if (cmd->fd_in > 2)
		close(cmd->fd_in);
	if (cmd->fd_out > 2)
		close(cmd->fd_out);
	while (cmd->command && (cmd->command)[i])
		free((cmd->command)[i++]);
	free(cmd->command);
}

void	print_command_data(t_list *lst)
{
	t_list *curr;
	t_cmd 	*cmd;

	curr = lst;
	while (curr)
	{
		cmd = (t_cmd *)curr->content;

		if (0  && !cmd->error_free)
		{
			destroy_command(cmd);		
			curr = curr->next;
			continue;
		}

		printf("-----------------------\n");
		printf("-/--: input fd : %d\n", cmd->fd_in);
		printf("-/--: output fd : %d\n", cmd->fd_out);
		printf("-/--: Command : ");
		for (int y = 0;  cmd->command && (cmd->command)[y] != NULL; y++)
			printf("%s ",(cmd->command)[y]);
		printf("\n");
		printf("-/--: Error Free : %d\n", cmd->error_free);
		curr = curr->next;
		
		//deallocating commands (debuging purpuses)
		destroy_command(cmd);		
	}

}



t_list *parse_command(char *cmd, t_list	**local_env)
{
	t_token_list *tokens;
	t_list		*command_list;

	command_list = NULL;
	tokens = get_tokens(cmd);
	if (!tokens)
		return (NULL);
	if (n_parser(tokens, *local_env))
	{
		destroy_token_list(tokens);
		return (NULL);
	}
	command_list = parser_one(tokens, local_env);
	//print_env(*local_env);

	//print_command_data(command_list);

	destroy_token_list(tokens);
	return (command_list);
}


void	print_env_g()
{
	t_env *content;
	while (genv)
	{
		content = (t_env *)genv->content;
		printf("[%s]->%s\n", content->key, content->val);
		genv = genv->next;
	}
	printf("Done printing env\n");
}

int main(int ac, char **av, char **env)
{
	t_list		*local_env;
	t_list		*command_list;
	char		*cmd;

	(void)(av);
	(void)(env);
	display_logo();
	local_env = NULL;
  ft_initenv(env);
	//print_env_g();
	//print_env(local_env);	  
	while (ac)
	{
		cmd = readline("\e\033[0;33mmsh$ \e\033[0;37m");
		command_list = parse_command(cmd, &local_env);
		add_history(cmd);
		//print_env_g();
		exec_cmd(command_list, env);
    	//
		//	execute commands in command list
		//		destroy each command after being executed
		//		destroy_command();
		//
		ft_lstclear(&command_list, free);
		free(command_list); 
		free(cmd);
	}
	ft_lstclear(&local_env, free);
}
