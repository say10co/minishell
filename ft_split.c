/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adriouic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/24 11:14:30 by adriouic          #+#    #+#             */
/*   Updated: 2022/04/06 21:57:33 by adriouic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft/libft.h"

#include<stdlib.h>
int	ft_is_sep(char *charset, char s, int x)
{
	while (*charset)
	{
		if (*charset == s)
			return (x);
		charset++;
	}
	return (!x);
}

int	ft_count_words(char *str, char *charset, int s)
{
	int	nb_wds;

	nb_wds = 0;
	while (*str)
	{
		while (*str && ft_is_sep(charset, *str, s))
			str++;
		if (*str)
			nb_wds++;
		while (*str && !(ft_is_sep(charset, *str, s)))
			str++;
	}
	return (nb_wds);
}

int	len_word(char *str, char *charset, int s)
{
	int		l;
	char	quote;

	l = 0;
	quote = 0;
	while (*str)
	{
		if ((*str == '"' && !quote) || (*str == '\'' && !quote) )
			quote = *str;
		else if (*str == quote)
			quote = 0;
		if (ft_is_sep(charset, *str, s) && !quote)
			break;
				str++;
		l++;
	}
	return (l);
}


char	*ft_copy_word(char *str, int size)
{
	int		t;
	char	*word;

	t = 0;
	word = (char *)malloc(sizeof(char) * (size + 1));
	while (*str && t < size)
	{
		word[t] = *str;
		str++;
		t++;
	}
	word[t] = '\0';
	return (word);
}

char	**ft_split_(char *str, char *charset, int s)
{
	char	**result;
	int		nb_w;
	int		j;
	int		length;
	char	quote;
	char	*cp;

	cp = str;
	nb_w = ft_count_words(str, charset, s);
	result = (char **)malloc(sizeof(char *) * (nb_w + 1));
	if (!result)
		return (NULL);
	j = 0;
	quote = 0;
	while (*str && j < nb_w)
	{
		while (*str)
		{
			if ((*str == '"' && !quote) || (*str == '\'' && !quote) )
				quote = *str;
			else if (*str == quote)
				quote = 0;
			if (!ft_is_sep(charset, *str, s) && !quote)
				break;
			str++;
		}
		if (*str)
		{
			if ((*str == '"' || *str == '\'')  && !j)
			{
				length = len_word(cp, charset, s);
				result[j] = ft_copy_word(cp, length);
				str = cp + length;
			}
			else
			{
				length = len_word(str, charset, s);
				result[j] = ft_copy_word(str, length);
				str += length;
			}
			j++;
		}
	}
	result[j] = 0;
	return (result);
}
