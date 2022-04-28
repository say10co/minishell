/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macplus <macplus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 21:16:23 by adriouic          #+#    #+#             */
/*   Updated: 2022/04/27 22:14:33 by macplus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/includes.h"

void	export(char **command)
{
	char	*name;
	int		i;

	i = 1;
	name = NULL;
	if (!*command)
		return ;
	while (command[i])
	{
		if (is_assignment(command[i], &name))
		{
			ft_updateenv(name, ft_strchr(command[i], '=') + 1);
			free(name);
		}
		i++;
	}
}
