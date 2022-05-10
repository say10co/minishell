/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   includes.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macplus <macplus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 10:13:57 by adriouic          #+#    #+#             */
/*   Updated: 2022/04/28 01:22:09 by macplus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INCLUDES_H

# define INCLUDES_H

# include <stdio.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <fcntl.h>
# include "../libft/libft.h"
# include "lexer.h"
# include <strings.h>
# include <stdlib.h>
# include <signal.h>

# define B_CD 501
# define B_ECHO 502
# define B_PWD 503
# define B_EXPORT 504
# define B_UNSET 505
# define B_ENV 506
# define B_EXIT 507

# define PERMISSION "Permission denied"
# define FILENTFOUND "No such file or directory"
# define CMDNOTFOUND "command not found"

typedef struct s_cmd
{
	int		fd_in;
	int		fd_out;
	char	**command;
	bool	error_free;
}t_cmd;

typedef struct s_env
{
	char	*key;
	char	*val;
}	t_env;

extern t_list	*g_env;

char	*append(char *prefix, const char *sufix);
void	free_befor_end(char **lst, int end);
bool	is_even(int x);
int		get_pipe_fileds(char ***argv);

int		ft_strcmp(const char *s1, const char *s2);
char	**my_ft_split(const char *str, char c);
char	*polish(const char *s, char *charset);

//*******************Expander************ 
char	*get_values(char *token, t_list **str_lst, char q);
char	*get_value_of_key(char *key, t_list *local_env);

//******************** PARSER ONE ********
bool	is_assignment(char *str, char **name);

//*******************PARSER***************

t_list	*parser_one(t_token_list *lst);
bool	n_parser(t_token_list *lst);
int		close_old_open_new(t_cmd *cmd, char *file_name, int mode, int old_fd);
void	heredoc(char *eof, t_cmd *cmd);
void	open_file(t_cmd *cmd, t_token *t, char *file_name);
void	append_to_lst(char ***vector, char *elem, size_t *vector_size);
void	close_files(t_cmd *cmd);
t_list	*create_env(char **env);

//***************** EXECUTION ***************
void	exec_cmd(t_list *icmd);
int		is_builtin(char *cmd);
void	exec_builtin(int ncmd, t_cmd *cmd);
void	cd(char **arg);
void	pwd(char **arg);
void	env(t_cmd *cmd);
void	b_exit(void);
void	unset(char **command);
void	copy_file(int fdi, int fdo);
//***************** ENV **********************
void	ft_initenv(char **env);
char	*ft_getenv(char *key);
void	ft_updateenv(char *key, char *new_val);
void	exec_builtin(int ncmd, t_cmd *cmd);
char	**gen_env(void);

//******************* tmp ***************
void	export(char **command);

// ****************** SIGNALS ***************
void	handler(int sig);

//****************** Distructor.c ************

void	destroy_command(t_cmd *cmd);
void	destroy_command(t_cmd *cmd);
void	destroy_token_list(t_token_list *tokens);

// ------------------ CD UTILS ----------------

void	go_touser(char *dir);
void	go_tohome(void);
void	go_todir(char *dir);
void	go_tobasedhome(char *dir);
void	go_replcpwd(char *target, char *replacement);
void	go_oldpwd(void);

// ----------------- EXECUTE UTILS ---------------
int		*init_pipes(int size);
void	close_pipes(int *fd, int size);
void	output_tofile(t_cmd *cmd);
void	close_iofd(t_cmd *cmd);
void	merge_input(int fdpipe, int fdfile);

#endif