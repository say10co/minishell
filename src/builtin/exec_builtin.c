/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bberkass <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 19:38:16 by bberkass          #+#    #+#             */
/*   Updated: 2022/05/14 15:45:00 by bberkass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/includes.h"

void	exec_builtin(int ncmd, t_cmd *cmd)
{
	if (ncmd == B_CD)
		cd(cmd->command);
	else if (ncmd == B_EXPORT)
		export(cmd->command);
	else if (ncmd == B_ENV)
		env(cmd);
	else if (ncmd == B_UNSET)
		unset(cmd->command);
	else if (ncmd == B_PWD)
		pwd(cmd->command);
	else if (ncmd == B_EXIT)
		b_exit();
	else if (ncmd == B_ECHO)
		echo(cmd->command);
	else
		printf("STILL UNSUPORTED ?\n");
}
