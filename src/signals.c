


#include "../includes/includes.h"


void handler(int sig)
{
  
  if(sig == SIGINT)
  {
    write(1, "\n", 1);
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
  }
  //else if(sig == SIGQUIT)
    
}
