

#include "../../includes/includes.h"

void del(void *content)
{
  if(content)
    free(content);
}

void b_exit(void)
{
  ft_lstclear(&genv, del);
  exit(0);
}
