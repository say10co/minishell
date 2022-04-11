#include "libft/libft.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

t_list *create_env(char **env)
{
	t_list	*head;
	t_list	*tmp;
	int		i;

	head = NULL;
	i = 0;
	while (env[i])
	{
		tmp = ft_lstnew(ft_strdup(env[i]));
		if (!tmp)
		{
			ft_lstclear(&head, free);
			return (NULL);
		}	
		ft_lstadd_front(&head, tmp);
		i++;
	}
	return (head);
}

char *get_value_of_key(char *key, t_list *env, int *len)
{
	t_list *iterator;
	char	*tmp;
	char 	*equale_index;

	tmp = NULL;
	iterator = env;
	while (iterator)
	{
		equale_index = ft_strchr((char *)iterator->content, '=');
		if (equale_index)
		{
			*equale_index = 0;
			if (!ft_strcmp(key, iterator->content))
			{
				*equale_index = '=';
				tmp = ft_strdup(++equale_index);
				break;
			}
			*equale_index = '=';
		}
		iterator = iterator->next;
	}
	if (!tmp)
		return (0);
	//return(ft_calloc(1, sizeof(char)));
	*len += ft_strlen(tmp);
	return (tmp);
}

void	get_expanded_values(char *token, t_list **str_lst, t_list *env,  int *length)
{
	int		i;
	int		j;
	int		len_token;
	char 	*buffer;

	i = 0;
	j = 0;
	*str_lst = NULL;
	len_token = ft_strlen(token);
	buffer = (char *) malloc(sizeof(char) * len_token);
	while (token[i])
	{
		if (token[i] == '$')
		{
			if (j)
			{
				buffer[j] = 0;
				ft_lstadd_back(str_lst, ft_lstnew(ft_strdup(buffer)));
				*length += j;
				j = 0;
			}
			i++;
			while (token[i]  && token[i]  != ' ' && token[i] != '$'
					&& token[i] != '\'' && token[i] != '\"')
				buffer[j++] = token[i++];
			buffer[j] = 0;
			ft_lstadd_back(str_lst, ft_lstnew(get_value_of_key(buffer, env, length)));
			j = 0;
		}
		else
			buffer[j++] = token[i++];
	}
	ft_lstadd_back(str_lst, ft_lstnew(ft_strdup(buffer)));
	*length += j;
	free(buffer);
	return ;


}
char	*wrappup_exapnded_token(t_list *str_lst, int total_length)
{
	t_list *curr;
	char	 *result;
	int		i;
	int		j;

	result = (char *)malloc(total_length * sizeof(char));
	if (!result)
	{
		printf("Allocation failed in 'wrappup_exapnded_token;'\n");
		return (NULL);
	}
	curr = str_lst;
	i = 0;
	while (curr)
	{
		j = 0;
		while (curr->content && ((char *)curr->content)[j])
			result[i++] = ((char *)curr->content)[j++];
		curr = curr->next;
	}
	return (result);
}

int main(int ac, char **av, char **enviorment)
{
	ac--;
	int	  len = 0;
	(void)av;
	t_list *lst;
	t_list *env;
	char *zitona;

	env = create_env(enviorment); 
	get_expanded_values(av[1], &lst, env, &len);
	zitona = wrappup_exapnded_token(lst, len);
	printf("%s\n", zitona);
	ft_lstclear(&lst, free);
	return (0);
}
