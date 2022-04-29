/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adriouic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 03:07:59 by adriouic          #+#    #+#             */
/*   Updated: 2022/04/27 03:24:01 by adriouic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H
# define D_QUOTE '"'
# define S_QUOTE '\''
# define L_ARROW '<'
# define DL_ARROW 120
# define R_ARROW '>'
# define DR_ARROW 142
# define PIPE	'|'
# define SPACE	' '
# define SYNTAX_ERR "syntax error unexpected token"
# define PARSE_ERR "Parse Error, Uncolsed quote\n"

# include <stdbool.h>

typedef struct s_token t_token;
typedef struct s_token_list t_token_list;

struct s_token
{
	char	*data;
	int		type;
	int		length;
	bool	is_key;
	bool	found_space;
	char	quoted;
	bool	quote_err;
	bool	join;
	t_token	*next_token;
};

struct s_token_list
{
	t_token *all;
	int	nb_tokens;

};

typedef struct s_lexer
{
	t_token	*token;
	char	*buffer;
	char	quote;
	char	quote_type;
	int		i;
	int		j;
	int		start;

}t_lexer;

t_token_list	*get_tokens(char *text);
int				is_keyword(char c);
int				get_type(char c, int p);
bool			merge(char c1, char c2, t_token *t);
void			fill_token(t_token *t, char *buffer);
bool			get_data(char *buffer, t_lexer *v, t_token **t, bool join);
void			__init_list(t_token_list *lst);

#endif
