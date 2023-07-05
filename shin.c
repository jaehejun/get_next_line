#include "get_next_line.h"

static char *read_file(int fd, char **remain, char *buffer, int count_read)
{
    char    *temp_remain;
    while (count_read)
    {
        count_read = read(fd, buffer, BUFFER_SIZE);
        if (count_read == 0)
            break ;
        if (count_read == -1)
            return (NULL);
        buffer[count_read] = '\0';
        if (*remain == NULL)
            *remain = ft_strdup("");
        if (*remain == NULL)
            return (NULL);
        temp_remain = *remain;
        *remain = ft_strjoin(temp_remain, buffer);
        free(temp_remain);
        temp_remain = NULL;
        if (*remain == NULL)
            return (NULL);
        if (ft_strchr(*remain, '\n') != NULL)
            return (*remain);
    }
    return (*remain);
}

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

char	*read_line(int fd, char *buffer, char *remain)
{
	int	count;
	
	while (ft_strchr(remain, '\n') == NULL)
	{
		count = read(fd, buffer, BUFFER_SIZE);
		if (count == -1)
		{
			free(remain);
			remain = NULL;
			return (NULL);
		}
		if (count == 0)
			return (NULL);
		else
		{
			char *temp = remain;
			remain = ft_strjoin(remain, buffer);
			free (temp);
		}
	}
	return (remain);
}

char	*get_next_line(int fd)
{
	char		*buffer;
	char		*line;
	static char	*remain;

	if (fd < 0 || fd > 256)
		return (NULL);
	if (remain == NULL)
		remain = ft_strdup("");
	if (remain == NULL)
		return (NULL);
	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (buffer == NULL)
		return (NULL);
	remain = read_line(fd, buffer, remain);
	if (remain == NULL)
	{
		free(remain);
		return (NULL);
	}
	free(buffer);
	buffer = NULL;
	line = until_newline(remain);
	if (line == NULL)
	{
		free(remain);
		remain = NULL;
		return (NULL);
	}
	remain = after_newline(remain);
	if (remain == NULL)
	{
		free(line);
		return (NULL);
	}
	return (line);
}
