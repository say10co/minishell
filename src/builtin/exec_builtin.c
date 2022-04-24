#include "../../includes/includes.h"


void exec_builtin(int ncmd, t_cmd *cmd)
{
  if(ncmd == B_CD)
	  cd(cmd->command);
  else if (ncmd == B_EXPORT)
	  export(cmd->command);
  else if (ncmd == B_ENV)
	  env(cmd->command);
  else if (ncmd == B_UNSET)
	  unset(cmd->command);
  else if (ncmd == B_PWD)
	  pwd();
  else if (ncmd == B_EXIT)
    b_exit();
  else
    printf("STILL UNSUPORTED ?\n");
}
