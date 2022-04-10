/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_one.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adriouic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 02:07:55 by adriouic          #+#    #+#             */
/*   Updated: 2022/04/10 03:17:05 by adriouic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "lexer.h"

typedef struct s_cmd
{
	int	fd_in;
	int	fd_out;
	char **commad;

}t_cmd;


t_cmd *parser_one(t_token_list *lst, t_list *env, char **env_vector)
{
	t_token *t;
	t_list	*cmd_lst;
	int		index;
	t_cmd	*cmd;
	
	index = 0;
	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	while (t)
	{
		if (t->data )
		t = (t->is_keyword && )
		if (t->data == )

		t = t->next_token;
		index++;
	}
}
