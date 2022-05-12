/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destructors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macplus <macplus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 00:26:37 by adriouic          #+#    #+#             */
/*   Updated: 2022/05/12 01:27:44 by macplus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/includes.h"

void	deallocate(char **s)
{
	int	i;

	i = 0;
	if (!s)
		return ;
	while (s[i])
		free(s[i++]);
	free(s);
}

void	destroy_token_list(t_token_list *tokens)
{
	t_token	*curr;
	t_token	*tmp;

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

void	destroy_command(t_cmd *cmd)
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
