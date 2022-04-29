/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_operators.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adriouic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 00:43:30 by adriouic          #+#    #+#             */
/*   Updated: 2022/04/29 00:59:27 by adriouic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/includes.h"

void	join_next_token(char **old, char *new)
{
	char	*tmp;

	tmp = *old;
	*old = ft_strjoin(*old, new);
	free(tmp);
}

char	*add_prefix(const char *prefix, const char *file)
{
	int		len;
	int		len_prefix;
	char	*buffer;

	len = ft_strlen(file);
	len_prefix = ft_strlen(prefix);
	buffer = malloc(sizeof(char) * (len_prefix + len + 2));
	if (!buffer)
	{
		perror("Allocation Failed\n");
		return (0);
	}
	ft_memmove(buffer, prefix, len_prefix);
	ft_memmove(buffer + len_prefix, "/", 1);
	ft_memmove((buffer + len_prefix + 1), file, len +1);
	return (buffer);
}

bool	is_assignment(char *str, char **name)
{
	char	*tmp_str;
	char	*equale;
	int		i;

	tmp_str = ft_strdup(str);
	equale = ft_strchr(tmp_str, '=');
	if (!equale || *(equale +1) == '\0')
	{
		free(tmp_str);
		return (0);
	}
	i = 0;
	*equale = 0;
	while (tmp_str[i])
	{
		if (!ft_isalpha(tmp_str[i++]))
		{
			free(tmp_str);
			perror("msh: export: not a valid identifier\n");
			return (0);
		}
	}
	*name = tmp_str;
	return (1);
}

void	wrape_command(t_list **cmd_lst, t_cmd **cmd, size_t *vector_size)
{
	int	fd;

	fd = (*cmd)->fd_out;
	ft_lstadd_back(cmd_lst, ft_lstnew(*cmd));
	*cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (!*cmd)
	{
		perror("Allocation Failed!");
		return ;
	}
	__init_cmd(*cmd);
	(*cmd)->fd_in = fd;
	*vector_size = 0;
}

void	join_tokens(t_token_list *lst)
{
	t_token	*t;
	t_token	*tmp;

	t = lst->all;
	while (t)
	{
		if (t->join && t->next_token)
		{
			join_next_token(&(t->data), t->next_token->data);
			t->join = t->next_token->join;
			free(t->next_token->data);
			tmp = t->next_token->next_token;
			free(t->next_token);
			t->next_token = tmp;
		}
		else
			t = t->next_token;
	}
}
