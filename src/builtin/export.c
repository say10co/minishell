/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macplus <macplus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 21:16:23 by adriouic          #+#    #+#             */
/*   Updated: 2022/05/15 13:21:57 by adriouic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/includes.h"

int	export(char **command)
{
	char	*name;
	int		i;

	i = 1;
	name = NULL;
	if (!command[i])
	{
		print_env_g("declare -x");
		return (0);
	}
	while (command[i])
	{
		if (is_assignment(command[i], &name))
		{
			ft_updateenv(name, ft_strchr(command[i], '=') + 1);
			free(name);
		}
		else
			return (1);
		i++;
	}
	return (0);
}
