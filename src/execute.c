
#include "../includes/includes.h"

int *init_pipes(int size)
{
  int *fd;
  int i;
  int status;

  fd = (int *)malloc(sizeof(int) * (size - 1) * 2);
  if(!fd)
    perror("could't allocate memory !");
  i = 0;
  while(i < size - 1)
  {
    status = pipe(&fd[i * 2]);
    if(status < 0)
      perror("init pipes faild !");
    i++;
  }
  return (fd);
}

void close_pipes(int *fd, int size)
{
  int i;

  i = 0;
  while(i < (size - 1) * 2)
  {
    close(fd[i]);
    i++;
  }
}

void output_tofile(t_cmd *cmd)
{
  pid_t pid;
  int status;

  pid = fork();
  if(pid == 0)
  {
    status = dup2(cmd->fd_out, 1);
    if(status < 0)
      perror("dup2 faild");
    execve(cmd->command[0], cmd->command, NULL);
    perror("exec faild");
  }
  else if (pid > 0)
  {
    wait(&status);
    kill(pid, 9);
  }
}

void exec_cmd(t_list *icmd)
{
  t_cmd *cmd;
  pid_t pid;
  int *fd;
  int status;
  int size;
  int i;

  // init pipes with in memory file descriptors so we can share data betweem processes 
  size = ft_lstsize(icmd);
  fd = init_pipes(size);
  i = 0;
  while(i < size && icmd)
  {
    cmd = (t_cmd *)icmd->content;

    // TODO :
    // -> check why some commands hang after executing like grep 
    // -> handle out to file instead of stdout 

    pid = fork();
    if(pid == -1)
      perror("fork faild ");
    else if(pid == 0)
    {
      // child process 
      if(cmd->fd_in > 2)
        dup2(cmd->fd_in, 0);
      if(i != 0)
      {
        // this is not the first command ! 
        // child gets the previous process output by duplicating read fd to stdin  
        status = dup2(fd[(i - 1) * 2], 0);
        if(status < 0)
          perror("dup2 faild");
      }
      // check if file output to another fd beside stdout !
      // execute command in another proccess redirect result to the given fd if cmd size > 1
      // otherwise redirect command output to the given fd and display nada on stdout !
      if(cmd->fd_out > 2 && size > 1)
        output_tofile(cmd);
      else if (cmd->fd_out > 2 && size == 1)
        dup2(cmd->fd_out, 1);
      if(i < size - 1)
      {
        // this is not the last command !
        // child output to the next command bu dup write fd to std out
        status = dup2(fd[i * 2 + 1], 1);
        if(status < 0)
          perror("dup2 faild");
      }
      // close pipe's fd to have EOF so the next proccess can read from it 
      close_pipes(fd, size);
      execve(cmd->command[0], cmd->command, NULL);
      perror("exec faild");
    }
    i++;
    icmd = icmd->next;
  }
  close_pipes(fd, size);
  i = 0;
  while(i < size)
  {
    wait(NULL);
    i++;
  }
}

