/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adriouic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 16:39:07 by adriouic          #+#    #+#             */
/*   Updated: 2022/05/14 16:39:13 by adriouic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/libft.h"
#include <stdbool.h>

int	echo(char **command)
{
	bool	nl_option;
	int		i;

	i = 1;
	nl_option = 0;
	if (!command[1])
		return (write(1, "\n", 1) * 0);
	while (command[i] && !ft_strcmp(command[i], "-n"))
		i++;
	nl_option = (i != 1);
	while (command[i])
	{
		ft_putstr_fd(command[i++], 1);
		if (command[i])
			write(1, " ", 1);
	}
	if (!nl_option)
		write(1, "\n", 1);
	return (0);
}
