/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adriouic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 10:05:25 by adriouic          #+#    #+#             */
/*   Updated: 2022/03/31 10:32:32 by adriouic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/includes.h"

char *append(char *prefix, const char *sufix)
{
	char *joined_str;

	joined_str = ft_strjoin(prefix, sufix);
	free(prefix);
	return (joined_str);
}

bool is_even(int x)
{
	return (x % 2 == 0);
}

void 	free_befor_end(char **lst, int end)
{
	int i;

	i = -1;
	while (++i < end)
		free(lst[i]);
}
