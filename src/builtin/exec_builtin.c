#include "../../includes/includes.h"


void exec_builtin(int ncmd, t_cmd *cmd)
{
  if(ncmd == B_CD)
    cd(cmd->command);
  else if (ncmd == B_EXPORT)
	  export(cmd->command);
  else if (ncmd == B_PWD)
    pwd();
  else
    printf("STILL UNSUPORTED ?");
}
