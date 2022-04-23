/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adriouic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 01:08:17 by adriouic          #+#    #+#             */
/*   Updated: 2022/04/22 20:57:17 by adriouic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/lexer.h"
#include "../includes/includes.h"

int	is_keyword(char c)
{
	if (c == L_ARROW || c == R_ARROW || c == PIPE)
		return (1);
	return (0);
}

int is_builtin(char *cmd)
{
  if(!ft_strcmp(cmd, "cd"))
    return B_CD;
  else if(!ft_strcmp(cmd, "echo") && 0)
    return B_ECHO;
  else if(!ft_strcmp(cmd, "pwd") && 0)
    return B_PWD;
  else if(!ft_strcmp(cmd, "export"))
    return B_EXPORT;
  else if(!ft_strcmp(cmd, "unset"))
    return B_UNSET;
  else if(!ft_strcmp(cmd, "env"))
    return B_ENV;
  else if(!ft_strcmp(cmd, "exit"))
    return B_EXIT;
  return 0;
}
