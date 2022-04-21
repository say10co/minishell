/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adriouic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 01:08:17 by adriouic          #+#    #+#             */
/*   Updated: 2022/04/13 01:08:36 by adriouic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/lexer.h"

int	is_keyword(char c)
{
	if (c == L_ARROW || c == R_ARROW || c == PIPE)
		return (1);
	return (0);
}