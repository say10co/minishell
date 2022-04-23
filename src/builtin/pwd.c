

#include "../../includes/includes.h"


void pwd()
{
  char *pwd;

  pwd = ft_getenv("PWD");
  printf("%s\n", pwd);
}
