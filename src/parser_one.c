/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_one.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adriouic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 02:07:55 by adriouic          #+#    #+#             */
/*   Updated: 2022/04/23 05:28:53 by adriouic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/includes.h"

char *add_prefix(const char *prefix, const char *file)
{
	int		len;
	int		len_prefix;
	char	*buffer;

	len = ft_strlen(file);
	len_prefix = ft_strlen(prefix);
	buffer = malloc(sizeof(char) * (len_prefix + len + 2));
	ft_memmove(buffer, prefix, len_prefix);
	ft_memmove(buffer + len_prefix, "/", 1);
	ft_memmove((buffer + len_prefix + 1), file, len+1);
	return (buffer);
}

void 	deallocate(char **s)
{
	int	i;
	
	i = 0;
	while (s[i])
		free(s[i++]);
	free(s);
}

bool	 is_assignment(char *str, char **name)
{
	char	*tmp_str;
	char	*equale;
	int		i;

	tmp_str = ft_strdup(str);
	equale = ft_strchr(tmp_str, '=');
	if (!equale || *(equale+1) == '\0')
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
			return (0);
		}
	}
	*name = tmp_str;
	return (1);
}


bool	check_file(t_token *token, t_cmd *cmd)
{
	char	*buffer;
	int		i;
	char 	**paths;
	const char	*error;

	i = 0;
	error = FILENTFOUND;
	if (cmd->command)
		return (0);
	error = CMDNOTFOUND;
	if (!access(token->data, F_OK) ||  is_builtin(token->data))
		return (0);
	paths = ft_split(ft_getenv("PATH"), ':');
	while (paths && paths[i]) 
	{
		buffer =  add_prefix(paths[i++], token->data);
		if (!access(buffer, F_OK))
		{
			if (!access(buffer, R_OK))
			{
				free(token->data);
				token->data = ft_strdup(buffer);
				token->data = buffer;
				deallocate(paths);
				return (0);
			}
			else
				error = PERMISSION;
		}
		free(buffer);
	}
	cmd->error_free = 0;
	deallocate(paths);
	return (printf("msh: %s: %s\n", token->data, error));
}

void	__init_cmd(t_cmd *cmd)
{
	cmd->fd_in = 0;
	cmd->fd_out = 1;
	cmd->error_free = 1;
	cmd->command = NULL;
}

void	wrape_command(t_list **cmd_lst, t_cmd **cmd, size_t *vector_size)
{
	int	fd;

	fd = (*cmd)->fd_out;
	ft_lstadd_back(cmd_lst, ft_lstnew(*cmd));
	*cmd = (t_cmd *)malloc(sizeof(t_cmd));
	__init_cmd(*cmd);
	(*cmd)->fd_in = fd;
	*vector_size = 0;
}

void	__init_parser_vars(size_t *size, t_list **cmd_lst, t_cmd **cmd)
{
	*size = 0;
	*cmd = (t_cmd *)malloc(sizeof(t_cmd));
	*cmd_lst = NULL;
	__init_cmd(*cmd);
}

t_list	*parser_one(t_token_list *lst)
{
	size_t	vector_size;
	t_list	*cmd_lst;
	t_token	*t;
	t_cmd	*cmd;

	__init_parser_vars(&vector_size, &cmd_lst, &cmd);
	t = lst->all;
	while (t)
	{
		if (t->type == PIPE)
			wrape_command(&cmd_lst, &cmd, &vector_size);
		else if ((t->is_key && t->type == DL_ARROW))
		{
			heredoc(t->next_token->data, cmd);
			t = t->next_token;
		}
		else if (t->is_key)
		{
			open_file(cmd, t, t->next_token->data);
			t = t->next_token;
		}
		else if (!check_file(t, cmd))
			append_to_lst(&(cmd->command), t->data, &vector_size);
		if (!cmd->error_free)
			close_files(cmd);
		t = t->next_token;
	}
	ft_lstadd_back(&cmd_lst, ft_lstnew(cmd));
	return (cmd_lst);
}
