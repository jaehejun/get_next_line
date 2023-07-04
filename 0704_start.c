/*
read 할때 buffer프리해줘야함
remain에 strjoin(remain, buffer)할당된채로 다시read하다가 터지면
remain을 free시켜줘야 하는데 어쩌지;
*/

#include "get_next_line.h"

//void	free_memory(char *str)
//{
//	free(str);
//	str = NULL;
//}

char	*until_newline(char *str)
{
	char	*before;
	int		i;

	i = 0;
	if (str[i] == '\0')
		return (str);
	while (str[i] != '\0')
	{
		if (str[i] == '\n')
			break;
		i++;
	}
	str[i + 1] = '\0';
	before = ft_strdup(str);
	if (before == NULL)
		return (NULL);
	return (before);
}

char	*after_newline(char *str)
{
	char	*after;
	int		i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\n')
			break;
		i++;
	}
	after = ft_strdup(&str[i + 1]);
	if (after == NULL)
		return (NULL);
	return (after);
}

char	*read_line(int fd, char *remain)
{
	char	*temp;
	char	*buffer;
	int		count;
	
	count = 1;
	while (count != 0 && ft_strchr(remain, '\n') == NULL)
	{
		buffer = (char *)malloc(sizeof(char)* (BUFFER_SIZE + 1));
		if (buffer == NULL)	// buffer malloc error
			return (NULL);
		count = read(fd, buffer, BUFFER_SIZE);	//buffer에 BFSIZE만큼 read한 값 저장
		if (count == -1) // Error
		{
			free(buffer);
			buffer = NULL;
			free(remain);
			remain = NULL;
			return(NULL);
		}
		else if (count == 0)	// EOF or empty file
			break;
		else
		{
			buffer[count] = '\0';
			temp = remain;		// temp에 original remain 저장
			remain = ft_strjoin(remain, buffer);	//strjoin이 새로운 주소에 remain + buffer를 저장
			free(temp);
			temp = NULL;
			if (remain == NULL)	// remain malloc error
			{
				free(buffer);	// buffer free
				//buffer = NULL;	// buffer NULL 이 필요한가??
				return (NULL);
			}
			free(buffer);	// buffer free
			//buffer = NULL;	// 필요한가??
		}
	}
	free(buffer);
	buffer = NULL;
	return(remain);	// eof or empty file일때는 NULL이어야 함
}

char	*get_next_line(int fd)
{
	char		*line;
	char		*temp;
	static char	*remain;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (remain == NULL)
		remain = ft_strdup("");
	if (remain == NULL)
		return (NULL);
	temp = remain;	// temp에 original remain 저장
	remain = read_line(fd, remain);
	if (remain == NULL || remain[0] == '\0')	// read_line error or empty file
	{
		free(temp);
		temp = NULL;
		return (NULL);
	}
	
	
	free(remain);
	remain = NULL;
	remain = ft_strdup(temp);
	free(temp);
	temp = NULL;
	if (remain == NULL)
		return (NULL);
	temp = ft_strdup(remain);
	if (temp == NULL)
	{
		free(remain);
		remain = NULL;
		return (NULL);
	}
	line = until_newline(temp);
	if (line == NULL)
	{
		free(remain);
		remain = NULL;
		free(temp);
		temp = NULL;
		return (NULL);
	}
	free(temp);
	temp = NULL;
	temp = ft_strdup(remain);
	
	line = until_newline(temp);
	free (temp);
	temp = NULL;
	if (line == NULL)
	{
		free(remain);
		remain = NULL;
		return (NULL);
	}
	remain = after_newline(remain);
	if (remain == NULL)
		return (NULL);
	return (line);
}

//int	main(void)
//{
//	int		fd;
//	char	*line;
//	int	i = 1;
//	fd = open("test.txt", O_RDONLY);
//	printf("----------------------------------1st GNL-------------------------------------\n");
//	line = get_next_line(fd);
//	if (line == NULL)
//		printf("empty NULL\n");
//	else
//		printf("WRONG\n");
//	printf("%c\n", line[0]);
//	printf("%p\n", line);
//	printf("GNL%d : %s\n", i++, line);
//	printf("----------------------------------2nd GNL-------------------------------------\n");
//	line = get_next_line(fd);
//	printf("GNL%d : %s\n", i++, line);
//	printf("----------------------------------3rd GNL-------------------------------------\n");
//	line = get_next_line(fd);
//	printf("GNL%d : %s\n", i++, line);
//	printf("----------------------------------4th GNL-------------------------------------\n");
//	line = get_next_line(fd);
//	printf("GNL%d : %s\n", i++, line);
//	printf("----------------------------------5th GNL-------------------------------------\n");
//	line = get_next_line(fd);
//	printf("GNL%d : %s\n", i++, line);
//	printf("----------------------------------6th GNL-------------------------------------\n");
//	line = get_next_line(fd);
//	printf("GNL%d : %s\n", i++, line);
//	printf("----------------------------------7th GNL-------------------------------------\n");
//	return 0;
//}