
#include "../includes/includes.h"


static void init_pipes(int *fd, int size)
{
  int i;
  int status;

  i = 0;
  while(i < size)
  {
    status = pipe(&fd[i * 2]);
    if(status == -1)
      exit(0); // handle error 
    i++;
  }
}

void exec_cmd(t_list *icmd)
{
  int *fd;
  //pid_t pid;
  t_cmd *cmd;
  int size;

  size = ft_lstsize(icmd);
  if(size > 1)
  {
    fd = (int *)malloc(sizeof(int) * (size * 2));
    init_pipes(fd, size);
  }
  while(icmd)
  {
    cmd = (t_cmd *)icmd->content;  
    printf("------------\n");
    printf("cmd => %s \n", cmd->command[1]);
    printf("fdi => %d \n", cmd->fd_in);
    printf("fdo => %d \n", cmd->fd_out);
    printf("------------\n");
    icmd = icmd->next;
  }
}
