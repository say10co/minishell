/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_one.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adriouic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 02:07:55 by adriouic          #+#    #+#             */
/*   Updated: 2022/05/15 18:28:47 by adriouic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/includes.h"

char	*file_fr_ok(char *file_name, char **token)
{
	char	*error;

	error = CMDNOTFOUND;
	if (!access(file_name, F_OK))
	{
		if (!access(file_name, R_OK))
		{
			free(*token);
			*token = ft_strdup(file_name);
			free(file_name);
			return (NULL);
		}
		else
			error = PERMISSION;
	}
	return (error);
}

bool	check_file(t_token *token, t_cmd *cmd)
{
	char		*buffer;
	int			i;
	char		**paths;

	i = 0;
	if (cmd->command || is_builtin(token->data)
		|| (ft_strchr(token->data, '/') && !access(token->data, X_OK)))
		return (0);
	if (!ft_strcmp(token->data, "..") || !ft_strcmp(token->data, "."))
		return (printf("msh: %s: %s\n", token->data, CMDNOTFOUND));
	paths = ft_split(ft_getenv("PATH"), ':');
	while (paths && paths[i])
	{
		buffer = add_prefix(paths[i++], token->data);
		if (!file_fr_ok(buffer, &(token->data)))
		{
			deallocate(paths);
			return (0);
		}
		free(buffer);
	}
	cmd->error_free = 0;
	deallocate(paths);
	return (printf("msh: %s: %s\n", token->data, CMDNOTFOUND));
}

t_list	*parser_one(t_token_list *lst)
{
	size_t	vector_size;
	t_list	*cmd_lst;
	t_token	*t;
	t_cmd	*cmd;

	__init_parser_vars(&vector_size, &cmd_lst, &cmd);
	join_tokens(lst);
	t = lst->all;
	while (t && t->data)
	{
		if (t->type == PIPE)
			wrape_command(&cmd_lst, &cmd, &vector_size);
		else if ((t->is_key && t->type == DL_ARROW) && cmd->error_free
			&& heredoc(t->next_token->data, cmd))
			t = t->next_token;
		else if (t->is_key && open_file(cmd, t, t->next_token->data))
			t = t->next_token;
		else if (!check_file(t, cmd))
			append_to_lst(&(cmd->command), t->data, &vector_size);
		if (!cmd->error_free)
			close_files(cmd);
		t = t->next_token;
	}
	ft_lstadd_back(&cmd_lst, ft_lstnew(cmd));
	return (cmd_lst);
}
