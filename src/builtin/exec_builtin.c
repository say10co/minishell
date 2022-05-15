/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bberkass <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 19:38:16 by bberkass          #+#    #+#             */
/*   Updated: 2022/05/15 17:17:27 by bberkass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/includes.h"

void	exec_builtin(int ncmd, t_cmd *cmd)
{
	int	status;

	status = 0;
	if (ncmd == B_CD)
		status = cd(cmd->command);
	else if (ncmd == B_EXPORT)
		status = export(cmd->command);
	else if (ncmd == B_ENV)
		status = env(cmd);
	else if (ncmd == B_UNSET)
		unset(cmd->command);
	else if (ncmd == B_PWD)
		pwd(cmd->command);
	else if (ncmd == B_EXIT)
		b_exit(cmd->command);
	else if (ncmd == B_ECHO)
		echo(cmd->command);
	update_exec_status(status);
}
