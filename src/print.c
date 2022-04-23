/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adriouic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 00:32:01 by adriouic          #+#    #+#             */
/*   Updated: 2022/04/23 08:42:44 by adriouic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/includes.h"

void	print_env(t_list *env)
{
	while (env)
	{
		printf("=%s\n", (char *)env->content);
		env = env->next;
	}
	printf("Done printing env\n");
}

void display_logo(void)
{
	char *logo;
	int	fd;
	int	r;

	logo = (char *)malloc(sizeof(char) * (330 + 1));
	fd = open("logo.txt", O_RDONLY);
	r = read(fd, logo, 330);
	logo[r] = '\0';
	printf("\e[0;92m %s\n", logo);
	printf("\e\033[0;37m");
	close(fd);
	free(logo);
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
		printf("-----------------------\n");
		printf("-/--: input fd : %d\n", cmd->fd_in);
		printf("-/--: output fd : %d\n", cmd->fd_out);
		printf("-/--: Command : ");
		for (int y = 0;  cmd->command && (cmd->command)[y] != NULL; y++)
			printf("%s ",(cmd->command)[y]);
		printf("\n");
		printf("-/--: Error Free : %d\n", cmd->error_free);
		curr = curr->next;
		//destroy_command(cmd);		
	}

}

void	print_env_g()
{
	t_env *content;
	t_list *curr;

	curr = genv;
	while (curr)
	{
		content = (t_env *)curr->content;
		printf("%s=%s\n", content->key, content->val);
		curr = curr->next;
	}
}