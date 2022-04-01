/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   includes.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adriouic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 10:13:57 by adriouic          #+#    #+#             */
/*   Updated: 2022/03/31 15:16:33 by adriouic         ###   ########.fr       */
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
# include <stdbool.h> 

#define QUOTE 1
#define DQUOTE 2
#define NONE 0


char	*append(char *prefix, const char *sufix);
void	free_befor_end(char **lst, int end);
bool	is_even(int x);
bool	get_pipe_fileds(char ***argv);
#endif
