/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_env.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bberkass <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 19:38:16 by bberkass          #+#    #+#             */
/*   Updated: 2022/05/14 15:43:45 by bberkass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/includes.h"

void	env(t_cmd *cmd)
{
	int	tmpout;

	tmpout = -1;
	if (!cmd)
		return ;
	if (cmd->command[1] != NULL)
		perror("env: too many arguments\n");
	print_env_g("");
}
