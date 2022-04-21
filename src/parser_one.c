/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_one.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adriouic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 02:07:55 by adriouic          #+#    #+#             */
/*   Updated: 2022/04/21 03:26:06 by adriouic         ###   ########.fr       */
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
	buffer = malloc(sizeof(char) * (len_prefix + len + 1));
	ft_memmove(buffer, prefix, len_prefix);
	ft_memmove(buffer + len_prefix, "/", 1);
	ft_memmove((buffer + len_prefix + 1), file, len+1);
	return (buffer);
}

void 	deallocate(char **s)
{
	int	i;
	
	i = -1;
	while (s[++i])
		free(s[i]);
	free(s);
}

void	 add_to_env(char *str, t_list **env, int len_name)
{
	t_list *curr;

	curr = *env;
	if (!*env)
	{
		ft_lstadd_back(env, ft_lstnew(ft_strdup(str)));
		return ;
	}
	while (curr && ft_strncmp(str, (char *)curr->content, len_name))
		curr = curr->next;
	if (!curr)
	{
		ft_lstadd_back(env, ft_lstnew(ft_strdup(str)));
		return ;
	}
	else
		curr->content = ft_strdup(str);
}

int	assignment(char *str, t_list **local_env)
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
	while (equale[i])
	{
		if (!ft_isalpha(equale[i++]))
		{
			free(tmp_str);
			return (0);
		}
	}
	add_to_env(str, local_env, ft_strlen(tmp_str));
	free(tmp_str);
	return (1);
}


bool	check_file(t_token *token, t_cmd *cmd, t_list **local_env)
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
	else if (assignment(token->data, local_env))
		return (1);
	paths = ft_split(getenv("PATH"), ':');
	while (paths[i]) 
	{
		buffer =  add_prefix(paths[i++], token->data);
		if (!access(buffer, F_OK))
		{
			if (!access(buffer, R_OK))
			{
				free(token->data);
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

t_list	*parser_one(t_token_list *lst, t_list **local_env)
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
			heredoc(t->next_token->data, *local_env, cmd);
			t = t->next_token;
		}
		else if (t->is_key)
		{
			open_file(cmd, t, t->next_token->data);
			t = t->next_token;
		}
		else if (!check_file(t, cmd, local_env))
			append_to_lst(&(cmd->command), t->data, &vector_size);
		if (!cmd->error_free)
			close_files(cmd);
		t = t->next_token;
	}
	ft_lstadd_back(&cmd_lst, ft_lstnew(cmd));
	return (cmd_lst);
}