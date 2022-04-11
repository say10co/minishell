#include <unistd.h>
#include <fcntl.h>

int main()
{
	int fd = open("/tmp/minishell-dumy_file-0ew3d", O_CREAT | O_WRONLY, 0644);
	write(fd, "hello from test procces\n", 25);
	sleep(3);
	unlink("/tmp/minishell-dumy_file-0ew3d");
	return (0);
}
