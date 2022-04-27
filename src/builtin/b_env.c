#include "../../includes/includes.h"

void	print_env_g();

void	env(t_cmd *cmd)
{
  int tmpout;

  tmpout = -1;
	if (!cmd)
		return ;
	if (cmd->command[1] != NULL)
		perror("env: too many arguments\n");
	/*
  if(cmd->fd_out > 2)
  {
    tmpout = dup(1);
    dup2(cmd->fd_out, 1);
  }
  */
  print_env_g();
  /*
  if(cmd->fd_out > 2)
  {
    close(cmd->fd_out);
    dup2(tmpout, 1);
    close(tmpout);
  }
  */
}
