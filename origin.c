#include "get_next_line.h"

char	*until_newline(char *str)
{
	char	*before;
	int		i;
	int		len;

	len = 0;
	while (str[len] != '\0')
	{
		len++;
		if (str[len] == '\n')
			break;
	}
	before = (char *)malloc(sizeof(char) * (len + 2));
	if (before == NULL)
		return (NULL);
	before[len + 2] = '\0';
	i = 0;
	while (*str != '\0')
	{
		before[i++] = *str++;
		if (*(str - 1) == '\n')
			break ;
	}
	return (before);
}

char	*after_newline(char *str)
{
	char	*after;
	int		len;

	len = 0;
	while (str[len] != '\0')
	{
		len++;
		if (str[len] == '\n')
			break;
	}
	after = ft_strdup(&str[len + 1]);
	if (after == NULL)
		return (NULL);
	return (after);
}

char	*read_line(int fd)
{
	char	*buffer;
	int		count;
	
	buffer = (char *)malloc(sizeof(char)*BUFFER_SIZE + 1);
	if (buffer == NULL)
		return (NULL);
	count = read(fd, buffer, BUFFER_SIZE);
	if (count == -1)
		return("");
	if (count == 0)
		return (NULL);
	buffer[count] = '\0';
	return (buffer);
}

char	*get_next_line(int fd)
{
	char		*buffer;
	char		*line;
	static char	*remain;

	if (remain == NULL)
		remain = ft_strdup("");
	if (remain == NULL)
		return (NULL);
	while (ft_strchr(remain, '\n') == NULL)
	{
		buffer = read_line(fd);
		if (buffer == NULL)
			break;
		if (*buffer == '\0')
		{
			free(buffer);
			buffer = NULL;
			free(remain);
			remain = NULL;
			return (NULL);
		}
		remain = ft_strjoin(remain, buffer);
		free(buffer);
		buffer = NULL;
		if (remain == NULL)
			return (NULL);
	}
	line = until_newline(remain);
	if (line == NULL)
	{
		free(remain);
		remain = NULL;
		free(buffer);
		buffer = NULL;
		return (NULL);
	}
	remain = after_newline(remain);
	if (remain == NULL)
		return (NULL);
	return (line);
	return (NULL);
}

int	main(void)
{
	int		fd;
	char	*line;
	int	i = 1;
	fd = open("test.txt", O_RDONLY);
	printf("----------------------------------1st GNL-------------------------------------\n");
	line = get_next_line(fd);
	printf("GNL%d : %s\n", i++, line);
	printf("----------------------------------2nd GNL-------------------------------------\n");
	line = get_next_line(fd);
	printf("GNL%d : %s\n", i++, line);
	printf("----------------------------------3rd GNL-------------------------------------\n");
	line = get_next_line(fd);
	printf("GNL%d : %s\n", i++, line);
	printf("----------------------------------4th GNL-------------------------------------\n");
	line = get_next_line(fd);
	printf("GNL%d : %s\n", i++, line);
	printf("----------------------------------5th GNL-------------------------------------\n");
	line = get_next_line(fd);
	printf("GNL%d : %s\n", i++, line);
	printf("----------------------------------6th GNL-------------------------------------\n");
	line = get_next_line(fd);
	printf("GNL%d : %s\n", i++, line);
	printf("----------------------------------7th GNL-------------------------------------\n");
	return 0;
}