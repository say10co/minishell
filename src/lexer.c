/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adriouic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 00:31:44 by adriouic          #+#    #+#             */
/*   Updated: 2022/05/15 14:01:56 by adriouic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lexer.h"
#include "../includes/includes.h"
#include "../libft/libft.h"

void	__init_lexer_vars(t_lexer *vars, t_token_list *lst, int size)
{
	vars->buffer = (char *)malloc(sizeof(char) * size);
	vars->quote = 0;
	vars->i = 0;
	vars->j = 0;
	vars->start = 1;
	vars->token = lst->all;
	vars->quote_type = 0;
}

bool	check_arguments(char *text, t_token_list *lst)
{
	if (!text || !text[0])
	{
		free(lst);
		return (1);
	}
	else if (!lst)
	{
		perror("Allocation Failed\n");
		return (1);
	}
	return (0);
}

t_token_list	*get_tokens(char *text)
{
	t_lexer			vars;	
	t_token_list	*lst;
	int				size;

	lst = (t_token_list *)(malloc(sizeof(t_token_list)));
	if (check_arguments(text, lst))
		return (NULL);
	__init_list(lst);
	size = ft_strlen(text);
	__init_lexer_vars(&vars, lst, size);
	while (vars.j <= size)
	{
		if (!vars.quote)
			get_nonquoted(lst, &vars, text);
		else
			get_between_quots(lst, &vars, text);
		text++;
		vars.j++;
	}
	if (vars.quote)
		(vars.token)->quote_err = 1;
	free(vars.buffer);
	return (lst);
}
