#include "../../includes/includes.h"

void	env(t_cmd *cmd)
{
	int	tmpout;

	tmpout = -1;
	if (!cmd)
		return ;
	if (cmd->command[1] != NULL)
		perror("env: too many arguments\n");
	print_env_g("");
}
