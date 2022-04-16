#include "../includes/lexer.h"
#include "../includes/includes.h"
#include "../libft/libft.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>



void display_logo(void)
{
	char *logo;
	int	fd;

	logo = (char *)malloc(sizeof(char) * 330);
	fd = open("logo.txt", O_RDONLY);
	read(fd, logo, 329);
	printf("\e\033[0;33m %s\n", logo);
	//printf("\e[0;92m %s\n", logo);
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
}

int main(int ac, char **av, char **env)
{
	int		ofd;
	int		ifd;
	int		tmp_fd;
	char		*cmd;
	t_cmd		*x;
	t_token_list	token_lst;
	t_token		*t;
	t_list		*enviorment = NULL;
	t_list		*command_list = NULL;
	int	pid;

	(void)(av);
	display_logo();
	enviorment = create_env(env);
	while (ac)
	{
		ft_lstclear(&command_list, free);
		cmd = readline("\e\033[0;33mmsh$ \e\033[0;37m");
		get_tokens(&token_lst, cmd, ft_strlen(cmd));
		if (!token_lst.nb_tokens || n_parser(&token_lst, &enviorment))
		{ 
			destroy_token_list(&token_lst);
			continue;
		}
		command_list = parser_one(&token_lst, enviorment);
			destroy_token_list(&token_lst);
		add_history(cmd);
		free(cmd);
		t  = token_lst.all;
		for (t_list *curr = command_list; curr != NULL; curr = curr->next)
		{
			x = (t_cmd *)curr->content;
			if (!x->error_free)
				continue;
			
			ifd = dup(0);
			ofd = dup(1);
			pid = fork();
			if (pid == 0)
			{
				dup2(x->fd_in, 0);
				dup2(x->fd_out, 1);
				execv(x->command[0], x->command);
			}
			else
				wait(NULL);
			dup2(0, ifd);
			dup2(1, ofd);
			tmp_fd = x->fd_in;
			if (tmp_fd > 2)
				close(tmp_fd);
			tmp_fd = x->fd_out;
			if (tmp_fd > 2)
				close(tmp_fd);
			if (!access("/tmp/minishell-dumy_file-0ew3d", F_OK))
				unlink("/tmp/minishell-dumy_file-0ew3d");
		}
	}
	ft_lstclear(&enviorment, free);

}


/*
int main(int ac, char **av, char **env)
{
	int		tmp_fd;
	char		*cmd;
	t_cmd		*x;
	t_token_list	token_lst;
	t_token		*t;
	t_list		*enviorment;
	t_list		*command_list;
	int	pid;

	(void)(av);
	display_logo();
	while (ac)
	{
		cmd = readline("\e\033[0;33mmsh$ \e\033[0;37m");
		get_tokens(&token_lst, cmd, ft_strlen(cmd));
		if (!token_lst.nb_tokens || n_parser(&token_lst, &enviorment, env))
			continue;
		command_list = parser_one(&token_lst, enviorment);
		add_history(cmd);
		t  = token_lst.all;
		while ( 0 && t)
		{
			printf("--/-: [%s] {%p}\n", t->data, t->next_token);
			t = t->next_token;
		}
		for (t_list *curr = command_list; curr != NULL; curr = curr->next)
		{
			x = (t_cmd *)curr->content;
			if (!x->error_free)
				continue;
	
			pid = fork();
			if (pid == 0)
				execv(x->command[0], x->command);
			else
				wait(NULL);
			//printf("-----------------------\n");
			tmp_fd = x->fd_in;
			//printf("-/--: input fd : %d\n", tmp_fd);
			if (tmp_fd > 2)
				close(tmp_fd);
			tmp_fd = x->fd_out;
			//printf("-/--: output fd : %d\n", tmp_fd);
			if (tmp_fd > 2)
				close(tmp_fd);
			//printf("-/--: Command : ");
			for (int y = 0;  0 && x->command && (x->command)[y] != NULL; y++)
			{
				printf("%s ",(x->command)[y]);
			}
			//printf("\n");
			//printf("-/--: Error Free : %d\n", x->error_free);
		}
		ft_lstclear(&command_list, free);
	}

}*/
