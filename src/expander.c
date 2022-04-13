/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adriouic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 22:08:02 by adriouic          #+#    #+#             */
/*   Updated: 2022/04/13 03:59:16 by adriouic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../libft/libft.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

char	*get_value_of_key(char *key, t_list *env, int *len)
{
	t_list	*iterator;
	char	*tmp;
	char	*equale_index;

	tmp = NULL;
	iterator = env;
	while (iterator)
	{
		equale_index = ft_strchr((char *)iterator->content, '=');
		if (equale_index)
		{
			*equale_index = 0;
			if (!ft_strcmp(key, iterator->content))
			{
				*equale_index = '=';
				tmp = ft_strdup(++equale_index);
				break ;
			}
			*equale_index = '=';
		}
		iterator = iterator->next;
	}
	if (tmp)
		*len += ft_strlen(tmp);
	return (tmp);
}

char	*wrappup_exapnded_token(t_list *str_lst, int total_length)
{
	t_list	*curr;
	char	*result;
	int		i;
	int		j;

	result = (char *)malloc(total_length * sizeof(char));
	if (!result)
	{
		printf("Allocation failed in 'wrappup_exapnded_token;'\n");
		return (NULL);
	}
	curr = str_lst;
	i = 0;
	while (curr)
	{
		j = 0;
		while (curr->content && ((char *)curr->content)[j])
			result[i++] = ((char *)curr->content)[j++];
		curr = curr->next;
	}
	result[i] = 0;
	return (result);
}

char *get_expanded_values(char *token, t_list **str_lst, t_list *env, int *length)
{
	int		i;
	int		j;
	int		len_token;
	char	*buffer;

	i = 0;
	j = 0;
	*str_lst = NULL;
	len_token = ft_strlen(token);
	buffer = (char *) malloc(sizeof(char) * len_token);
	while (token[i])
	{
		if (token[i] == '$')
		{
			if (j)
			{
				buffer[j] = 0;
				ft_lstadd_back(str_lst, ft_lstnew(ft_strdup(buffer)));
				*length += j;
				j = 0;
			}
			i++;
			while (token[i] && token[i] != ' ' && token[i] != '$'
				&& token[i] != '\'' && token[i] != '\"')
				buffer[j++] = token[i++];
			buffer[j] = 0;
			ft_lstadd_back(str_lst, ft_lstnew(get_value_of_key(buffer, env, length)));
			j = 0;
		}
		else
			buffer[j++] = token[i++];
	}
	if (j)
	{
		buffer[j] = 0;
		ft_lstadd_back(str_lst, ft_lstnew(ft_strdup(buffer)));
		*length += j;
	}
	free(buffer);
	return (wrappup_exapnded_token(*str_lst, *length));
}


/*
int	main(int ac, char **av, char **enviorment)
{
	int	  len = 0;
	(void)av;

	ac--;
	t_list *lst;
	t_list *env;
	char *zitona;

	env = create_env(enviorment); 
	get_expanded_values(av[1], &lst, env, &len);
	zitona = wrappup_exapnded_token(lst, len);
	printf("%s\n", zitona);
	ft_lstclear(&lst, free);
	sleep(3);
	return (0);
}
*/
