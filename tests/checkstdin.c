
#include <stdio.h>
#include <unistd.h>

int main()
{
  
  char buff[1024];

  int readed = read(0, &buff, 1024);
  buff[readed] = '\0';
  printf("readed: %d bytes \n", readed);
  printf("stdin : \n%s", buff);

  return(0);
}
