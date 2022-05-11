/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_ctl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adriouic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 22:56:16 by adriouic          #+#    #+#             */
/*   Updated: 2022/05/11 23:24:40 by adriouic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/includes.h"

bool	open_file(t_cmd *cmd, t_token *t, char *file_name)
{
	if (t->type == R_ARROW && cmd->error_free)
		cmd->fd_out = close_old_open_new(cmd, file_name, O_TRUNC, cmd->fd_out);
	else if (t->type == DR_ARROW && cmd->error_free)
		cmd->fd_out = close_old_open_new(cmd, file_name, O_APPEND, cmd->fd_out);
	else if (t->type == L_ARROW && cmd->error_free)
		cmd->fd_in = close_old_open_new(cmd, file_name, O_RDONLY, cmd->fd_in);
	return (1);
}

void	close_files(t_cmd *cmd)
{
	if (cmd->fd_in > 3)
		close(cmd->fd_in);
	if (cmd->fd_out > 3)
		close(cmd->fd_out);
}
