#include "../includes/includes.h"

void	handler(int sig)
{
  char *heredoc;

	if (sig == SIGINT)
	{
    heredoc = ft_getenv("ISHEREDOC");
    write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}
