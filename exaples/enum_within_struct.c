#include <stdio.h>

typedef struct foo
{
	int a;
	enum
	{
		ONE,
		TOW,
		THREE,
		FOUR,
	}one_to_four;

}foo_t;


int main(void)
{
	foo_t	var;

	var.a = 1;
	printf("a = %d one = %d\n",var.a, ONE);
	return (0);
}
