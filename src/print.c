/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bberkass <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 19:38:16 by bberkass          #+#    #+#             */
/*   Updated: 2022/05/15 14:19:12 by adriouic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/includes.h"

/* Debuging Tools 

void	print_env(t_list *env)
{
	while (env)
	{
		printf("=%s\n", (char *)env->content);
		env = env->next;
	}
	printf("Done printing env\n");
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
void	print_command_data(t_list *lst)
{
	t_list *curr;
	t_cmd 	*cmd;

	curr = lst;
	while (curr)
	{
		cmd = (t_cmd *)curr->content;

		if (!cmd->error_free)
		{
			destroy_command(cmd);		
			curr = curr->next;
			continue;
		}
		if (1){
			printf("-----------------------\n");
			printf("-/--: input fd : %d\n", cmd->fd_in);
			printf("-/--: output fd : %d\n", cmd->fd_out);
			printf("-/--: Command : ");
			for (int y = 0;  cmd->command && (cmd->command)[y] != NULL; y++)
				printf("[%s] ",(cmd->command)[y]);
			printf("\n");
			printf("-/--: Error Free : %d\n", cmd->error_free);
		}
		curr = curr->next;
		//destroy_command(cmd);		
	}

}
void ft_putenv_fd(char *s, int fd)
{
	if (!s)
		return ;
	while (*s)
	{
		write(fd, s, 1);
		s++;
	}
}

*/
void	display_logo(void)
{
	char	*logo;
	int		fd;
	int		r;

	logo = (char *)malloc(sizeof(char) * (330 + 1));
	fd = open("logo.txt", O_RDONLY);
	r = read(fd, logo, 330);
	logo[r] = '\0';
	printf("\e[0;92m %s\n", logo);
	printf("\e\033[0;37m");
	close(fd);
	free(logo);
}

void	print_env_g(const char *prefix)
{
	t_env	*content;
	t_list	*curr;

	curr = g_env;
	while (curr)
	{
		content = (t_env *)curr->content;
		printf("%s %s=%s\n", prefix, content->key, content->val);
		curr = curr->next;
	}
	return ;
}
