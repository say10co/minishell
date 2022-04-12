#include "../includes/lexer.h"
#include "../includes/includes.h"
#include "../libft/libft.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>


int main(int ac, char **av, char **env)
{
	int		tmp_fd;
	char		*cmd;
	t_cmd		*x;
	t_token_list	token_lst;
	t_token		*t;
	t_list		*enviorment;
	t_list		*command_list;

	(void)(av);
	while (ac)
	{
		cmd = readline("$ ");
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
			printf("-----------------------\n");
			x = curr->content;
			tmp_fd = x->fd_in;
			printf("-/--: input fd : %d\n", tmp_fd);
			if (tmp_fd > 2)
				close(tmp_fd);
			x = curr->content;
			tmp_fd = x->fd_out;
			printf("-/--: output fd : %d\n", tmp_fd);
			if (tmp_fd > 2)
				close(tmp_fd);
			printf("-/--: Command : ");
			for (int y = 0; (x->command)[y] != NULL; y++)
				printf("%s ",(x->command)[y]);
			printf("\n");
			printf("-/--: Error Free : %d\n:", x->error_free);
		}
	}

}
