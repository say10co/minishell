/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adriouic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 11:19:28 by adriouic          #+#    #+#             */
/*   Updated: 2022/04/06 22:10:49 by adriouic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <fcntl.h>
#include "../includes/includes.h"

t_list *create_env(char **env)
{
	t_list	*head;
	t_list	*tmp;
	int		i;

	head = NULL;
	i = 0;
	while (env[i])
	{
		tmp = ft_lstnew(env[i]);
		if (!tmp)
		{
			ft_lstclear(&head, free);
			return (NULL);
		}	
		ft_lstadd_front(&head, tmp);
		i++;
	}
	return (head);
}

int main(int ac, char **argv, char **env)
{
	t_list		*enviorment;
	t_command	**all_commands;
	
	enviorment = create_env(env);
	argv = NULL;
	all_commands = NULL;
	while (1)
	{
		ac = get_pipe_fileds(&argv);
		if (!ac)
			continue ;
		get_data_from_subfield(ac, argv, &all_commands);

		for(int i = 0; (argv && argv[i] != NULL); i++)
		{
			printf("\n_________Field %d ______:\n	::: %s \n", i, argv[i]);
			printf("command %s\n", all_commands[i]->cmd);
			printf("input fd : %d\n", (all_commands[i])->in_file);
			printf("output fd : %d\n", (all_commands[i])->out_file);
			if (all_commands[i]->in_file)
				close(all_commands[i]->in_file);
			if (all_commands[i]->out_file)
				close(all_commands[i]->out_file);
			free(argv[i]);
		}
		free(argv);
	}
	return (0);
}
