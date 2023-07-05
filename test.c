#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#define BUFFER_SIZE 5

int	main(void)
{
	int	fd = open("empt.txt", O_RDONLY);

	printf("fd : %d\n", fd);
	char	*buffer;
	int		count;
	int		len;

	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	count = read(fd, buffer, BUFFER_SIZE);
	len = strlen(buffer);
	printf("len right after read : %d\n", len);
	buffer[BUFFER_SIZE] = '\0';
	printf("len after null : %d\n", len);
	printf("count : %d\n", count);
	printf("buffer : %s\n", buffer);
	printf("buffer : %p\n", buffer);
	free(buffer);
	buffer = NULL;
	printf("buffer after freeing : %p\n", buffer);
}