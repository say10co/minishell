/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bberkass <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 19:38:16 by bberkass          #+#    #+#             */
/*   Updated: 2022/05/14 15:44:15 by bberkass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/includes.h"

void	del(void *content)
{
	if (content)
		free(content);
}

void	b_exit(void)
{
	ft_lstclear(&g_env, del);
	exit(0);
}
