/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   includes.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adriouic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 10:13:57 by adriouic          #+#    #+#             */
/*   Updated: 2022/04/13 03:12:09 by adriouic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <stdio.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <fcntl.h>
# include "../libft/libft.h"
# include "lexer.h"


typedef struct s_cmd
{
	int		fd_in;
	int		fd_out;
	char	**command;
	bool	error_free;

}t_cmd;


char	*append(char *prefix, const char *sufix);
void	free_befor_end(char **lst, int end);
bool	is_even(int x);
int		get_pipe_fileds(char ***argv);

int		ft_strcmp(const char *s1, const char *s2);
char	**my_ft_split(const char *str, char c);
char	*polish(const char *s, char *charset);

//*******************Expander************ 
char *get_expanded_values(char *token, t_list **str_lst, t_list *env, int *length);



//*******************PARSER***************

t_list *parser_one(t_token_list *lst, t_list *env);
bool	n_parser(t_token_list *lst, t_list **env, char **env_vector);
int		close_old_open_new(t_cmd *cmd, char *file_name, int mode, int old_fd);
void	heredoc(char *eof, t_list *env, int quote);
void	open_file(t_cmd *cmd, t_token *t, char *file_name);
void	append_to_lst(char ***vector, char *elem, size_t *vector_size);
void	close_files(t_cmd *cmd);


