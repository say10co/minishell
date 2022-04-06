# include <stdio.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft/libft.h"

#define R_ARROW 62
#define L_ARROW 60
#define DL_ARROW 124
#define DR_ARROW 120
#define DOLLAR	36
#define	D_QUOTE 34
#define S_QUOTE 27
#define SPACE 32

char *polish(char *s, char *charset)
{
	char *polished;

	polished = ft_strtrim(s, charset);
	if (polished[0] == '\0')
	{
		free(s);
		free(polished);
		return (NULL);
	}
	free(s);
	return (polished);
	
}
int	append_to_sting(char **str, const char c, int len_str)
{
	char *new_str;

	if (!(*str))
	{
		*str = malloc(sizeof(char) * 2);
		(*str)[0] = c;
		(*str)[1] = 0;
		return (1);
	}
	new_str = malloc(sizeof(char) * len_str + 2);
	if (!new_str)
		return (0);
	ft_memmove(new_str, *str, len_str);
	new_str[len_str] = c;
	new_str[len_str + 1] = 0;
	free(*str);
	*str = new_str;
	return (len_str + 1);
}

int	len_lst(char **lst)
{
	int	 len;

	len = 0;
	while (lst[len])
		len++;
	return (len);
}

char **merge_tow_lists(char **lst1, char **lst2)
{
	int total_len;
	char **new_lst;
	int		i1;
	int		i2;
	int		i;

	
	i1 = 0;
	i2 = 0;
	i = 0;
	total_len = len_lst(lst1) +  len_lst(lst2);
	new_lst = (char **)(malloc(sizeof(char *) * total_len + 1));
	while (i < total_len)
	{
		if (lst1[i1])
			new_lst[i++] = polish(lst1[i1++], " ");
		if (lst2[i2])
			new_lst[i++] = polish(lst2[i2++], " ");
	}
	new_lst[i] = 0;
	free(lst2);
	free(lst1);
	return (new_lst);
	
}

bool is_keyword(char c)
{
	if (c == '>')
		return (L_ARROW);
	if (c == '<')
		return (R_ARROW);
	if (c == '$')
		return (DOLLAR);
	if (c == '"')
		return (D_QUOTE);
	if (c == '\'')
		return (S_QUOTE);
	if (c == ' ')
		return (SPACE);
	if (c == '\0')
		return (1);
	return (0);
}

char    **ft_split_(char *str, char *charset, int s);

int main(int ac, char **agv)
{
	char	*line;
	char **tmp2;
	int		i;

	while (1){
	i = 0;
	line = readline("$ ");
	add_history(line);
	tmp2 = merge_tow_lists(ft_split_(line, "><", 1), ft_split_(line, "><", 0));
	while (tmp2[i])
	{
		printf("-/-: [%s]\n", tmp2[i]);
		i++;
	}}

}
