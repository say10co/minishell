#include "../../includes/includes.h"

void	print_env_g();

void	env(char **command)
{
	if (!*command)
		return ;
	if (command[1] != NULL)
		perror("env: too many arguments\n");
	print_env_g();
}
