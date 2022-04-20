#include "../../includes/includes.h"


void exec_builtin(int ncmd, t_cmd *cmd)
{
  if(ncmd == B_CD)
    cd(cmd->command);
  else
    printf("STILL UNSUPORTED ?");
}
