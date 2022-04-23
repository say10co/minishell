
#include "libft.h"

char *ft_strreplace(char *container, char *target, char *replacement)
{
  char *res;
  char *occ;
  int size;
  int i;

  if(!target || !replacement || !container)
    return (NULL);
  occ = ft_strstr(container, target);
  if(!occ)
     return (NULL);
  size = (ft_strlen(container) - ft_strlen(target)) + ft_strlen(replacement) + 1;
  res = (char *)malloc(sizeof(char) * size);
  i = 0;
  
  // copy first haff
  while(*container && container != occ)
  {
    res[i] = *container;
    i++;
    container++;
  }
  // bypass the target
  while(*container && *target && *target == *container)
  {
    target++;
    container++;
  }
  while(*replacement)
  {
    res[i] = *replacement;
    replacement++;
    i++;
  }
  // copy rest of container
  while(*container)
  {
    res[i] = *container;
    i++;
    container++;
  }
  res[i] = '\0';
  return (res);
}
