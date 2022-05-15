/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_env.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bberkass <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 19:38:16 by bberkass          #+#    #+#             */
/*   Updated: 2022/05/15 13:06:51 by adriouic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/includes.h"

int	env(t_cmd *cmd)
{
	int	tmpout;

	tmpout = -1;
	if (!cmd)
		return (0);
	if (cmd->command[1] != NULL)
		perror("env: too many arguments\n");
	print_env_g("");
	return (0);
}
