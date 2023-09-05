#include <unistd.h>

int main(void)
{
	write(1, "HERE\n", 5);
	return (0);
}