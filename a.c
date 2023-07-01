#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int	main(void)
{
	int	fd1;
	int	fd2;

	fd1 = open("emp.txt", O_RDONLY);
	fd2 = open("empty.txt", O_RDONLY);
	printf("%d\n", fd1);
	printf("%d\n", fd2);
}