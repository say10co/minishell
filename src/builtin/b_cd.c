

#include "../../includes/includes.h"


// TODO:
// -> change PWD and OLDPWD in env 
// -> print path when passing "-"
// -> handle cd with 2 args (replace the 1st arg with the second) ! 

static int arg_size(char **arg)
{
  int l;
  if(!arg)
    return (0);
  l = 0;
  while(arg[l])
    l++;
  return (l);
}

void cd(char **arg)
{
  int size;
  char path[4096];
  int status;
  char *oldpwd;

  size = arg_size(arg);
  getcwd(path, 4096);
  if(size > 3)
    printf("cd: too many arguments\n");
  else if(size == 2 && arg[1][0] != '-' && arg[1][0] != '~') 
  {
    status = chdir(arg[1]);
    if(status == -1)
      printf("cd: no such file or directory: %s\n", arg[1]);
  }
  else if(size == 2 && arg[1][0] == '-')
  {
    // print current directory !!!
    oldpwd = ft_getenv("OLDPWD");
    printf("%s\n", oldpwd);
    status = chdir(oldpwd); 
    if(status == -1)
      perror("cd faild");
  }
  else if((size == 2 && arg[1][0] == '~') || size == 1)
  {
    status = chdir(ft_getenv("HOME"));
    if(status == -1)
      perror("cd faild !");
  }
  else 
  {
    printf("Unsupported arguments !");
    return;
  }
  ft_updateenv("OLDPWD", path);
  getcwd(path, 4096);
  ft_updateenv("PWD", path);
  
}
