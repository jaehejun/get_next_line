#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#define BUFFER_SIZE 5

//void	read_line(fd)
//{
//	char	*buffer;
//	int		count;

//	count = 1;
//	while (count != 0)
//	{
//		buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
//		count = read(fd, buffer, BUFFER_SIZE);
//		printf("%s\n", buffer);
//		free(buffer);
//		buffer = NULL;
//	}
//}

//int	main(void)
//{
//	int	fd;

//	fd = open("test.txt", O_RDONLY);
//	read_line(fd);
//	system("leaks a.out");
//	return (0);
//}

//버퍼 쓸때마다 free(buffer)를 해줘야 하는데, 이걸 안해주면 메모리 누수가 발생한다.

char	*make_line(char *line)
{
	char	*new_line;
	int		len;
	int		i;

	len = 0;
	while (line[len] != '\0')
	{
		if (line[len] == '\n')
		{
			len++;
			break;
		}
		len++;
	}
	printf("%d\n", len);
	new_line = (char *)malloc(sizeof(char) * (len + 1));
	if (new_line == NULL)
		return (NULL);
	new_line[len] = '\0';
	i = 0;
	while (len-- > 0)
	{
		new_line[i] = line[i];
		printf("%c\n", new_line[i]);
		i++;
	}
	return (new_line);
}

int	main(void)
{
	char	*line;
	char	*temp;

	line = make_line("hello\nworld");
	printf("%s\n", line);
	temp = line;
	line = make_line("hellop");
	printf("%s\n", line);
	free(temp);
	printf("LINE : %s\n", line);
}