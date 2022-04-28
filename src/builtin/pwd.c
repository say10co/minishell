#include "../../includes/includes.h"

void	pwd(char **arg)
{
	char	*pwd;

	(void)arg;
	pwd = ft_getenv("PWD");
	printf("%s\n", pwd);
}
