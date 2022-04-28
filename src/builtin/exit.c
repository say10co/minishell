#include "../../includes/includes.h"

void	del(void *content)
{
	if (content)
		free(content);
}

void	b_exit(void)
{
	ft_lstclear(&g_env, del);
	exit(0);
}
