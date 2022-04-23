/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adriouic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 21:16:14 by adriouic          #+#    #+#             */
/*   Updated: 2022/04/22 21:16:16 by adriouic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	del_node(t_list **lst, int index)
{
	t_list *prev;
	t_list *next;
	int		i;
	

	i = 0;
	if (!index)
	{
		next = (*lst)->next;
		free((*lst)->content);
		if (next)
			*lst = next;
		else
			*lst = NULL;
		free(*lst);
		return ;
	}
	while (i < index - 1)
		lst = lst->next;
	next = lst->next;
	lst->next = next->next;
	free(next->data);
	free(next);
}
