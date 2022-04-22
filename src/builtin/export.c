#include "../../includes/includes.h"

int	vector_length(char **vector)
{
	int	i;

	i = 0;
	if (!vector)
		return (0);
	while (vector[i])
		i++;
	return (i);
}

void append_to_list(char ***vector, char *str)
{
	char **new_vector;
	int	len_vector;

	len_varctor = vector_length(*envp);
	if (!*vector)
		new_vector = (char **)malloc(sizeof(char *) * len_varctor + 2)
	else
		new_vector = (char **)malloc(sizeof(char *) * len_varctor + 2)
	if (!new_vector)
		perror("Failed To allocate\n");
	ft_memmove(new_vector, *vector, len_varctor);
	new_vector[len_varctor] = ft_strdup(str);
	new_lst[len_varctor + 1] = NULL;
	free(*vector)
	*vector  = new_vector;
}

void change_value(char **old, char **new)
{
	*old = *new;
}

void	del_node(t_list **lst, int index)
{
	t_list *prev;
	t_list *next;
	int		i;
	

	i = 0;
	if (!index)
	{
		next = (*lst)->next;
		free((*lst)->content);
		if (next)
			*lst = next;
		else
			*lst = NULL;
		free(*lst);
		return ;
	}
	while (i < index - 1)
		lst = lst->next;
	next = lst->next;
	lst->next = next->next;
	free(next->data);
	free(next);
}

char *exporot_localenv(char *name, t_list **local_env)
{
	t_list *prev;
	t_list *curr;
	int		i;

	i = 0;
	curr = *local_env;
	while (curr)
	{
		prev = local_env;
		if (!ft_strncmp(name, (char *)curr->content), ft_strlen(name))
		{
			append_to_list((char *)curr->content);
			del_node(local_env, i);
			return ;
		}
		i++;
		curr = curr->next; 
	}
}

void	change_env(char ***envp, char *name, char *str, t_list *local_env)
{
	int		i;
	int		name_len;
	char	*lst;

	i = 0;
	name_len = ft_strlen(name);
	lst = *envp;
	while (lst[i])
	{
		if (!strncmp(name, lst[i], name_len))
		{
			change_value(&lst[i], str);
			return ;
		}
		i++;
	}
	append_to_list(envp, str);
}

void	export(char ***envp, char *command, t_list **local_env)
{
	char	**s;
	char	*name;
	int		i;

	i = 1;
	name = NULL;
	s = ft_split(command, ' ');
	if (!s)
		return (NULL);
	while (s[i])
	{
		if (is_assignment(s[i]), &name)
			change_env(envp, name, s[i], local_env);
		else
			exporot_localenv(s[i], local_env)
	}

}
