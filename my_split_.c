/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adriouic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/24 11:14:30 by adriouic          #+#    #+#             */
/*   Updated: 2022/04/03 15:15:24 by adriouic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "includes/includes.h"

static int	ft_count_words(const char *str, char c)
{
	int	nb_wds;

	nb_wds = 0;
	while (*str)
	{
		while (*str && c == *str)
			str++;
		if (*str)
			nb_wds++;
		while (*str && *str != c)
			str++;
	}
	return (nb_wds);
}

static int	len_word(const char *str, char c)
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
		if (c == *str && !quote)
			break;
				str++;
		l++;
	}
	return (l);
}

static void	ft_free(char **ptr, int len)
{
	int	i;

	i = 0;
	while (i < len)
		free(ptr[i]);
	free(ptr);
	ptr = 0;
}

static int	ft_copy_word(const char *str, int size, char **result, int index)
{
	int		t;
	char	*word;

	t = 0;
	word = (char *)malloc(sizeof(char) * (size + 1));
	if (!word)
	{
		ft_free(result, index + 1);
		return (0);
	}
	while (*str && t < size)
	{
		word[t] = *str;
		str++;
		t++;
	}
	word[t] = '\0';
	result[index] = word;
	return (1);
}

char	**my_ft_split(const char *str, char c)
{
	char	**result;
	int		nb_words;
	int		i;

	if (!str)
		return (NULL);
	nb_words = ft_count_words(str, c);
	result = (char **)malloc(sizeof(char *) * (nb_words + 1));
	i = 0;
	if (!result)
		return (NULL);
	while (*str && i < nb_words)
	{
		while (*str && c == *str)
			str++;
		if (*str && ++i)
		{
			if (!ft_copy_word(str, len_word(str, c), result, i - 1))
				return (NULL);
		}
		str += len_word(str, c);
	}
	result[i] = 0;
	return (result);
}
