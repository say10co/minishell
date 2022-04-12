#include <unistd.h>
#include <fcntl.h>

int main()
{
	char *lst[] = {"/bin/ls", "-l", "-a"};

	execv("/bin/non", lst);
	




	return (0);
}
