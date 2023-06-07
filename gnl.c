#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#define BUFFER_SIZE 10
#define OPEN_MAX 256

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ft_strchr(const char *s, int c)
{
	size_t	len;

	len = ft_strlen(s) + 1;
	while (len-- > 0)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	return (NULL);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	int		check_space;
	size_t	src_len;

	src_len = ft_strlen(src);
	check_space = 0;
	if (dstsize != 0)
		check_space = 1;
	while (*src != '\0' && dstsize-- > 1)
		*dst++ = *src++;
	if (check_space == 1)
		*dst = '\0';
	return (src_len);
}

char	*ft_strdup(const char *s1)
{
	char	*dup;
	size_t	len;

	len = ft_strlen(s1);
	dup = (char *)malloc(sizeof(char) * (len + 1));
	if (!dup)
		return (NULL);
	ft_strlcpy(dup, s1, len + 1);
	return (dup);
}

//char	*ft_strtrim(char const *s1, char const *set)
//{
//	char	*trimmed;
//	size_t	start;
//	size_t	end;

//	start = 0;
//	end = ft_strlen(s1);
//	while (ft_strchr(set, s1[start]) != 0 && start < end)
//		start++;
//	while (ft_strchr(set, s1[end]) != 0 && end > 0)
//		end--;
//	if (start > end)
//		return (ft_strdup(""));
//	trimmed = (char *)malloc(sizeof(char) * (end - start + 2));
//	if (!trimmed)
//		return (NULL);
//	ft_strlcpy(trimmed, s1 + start, end - start + 2);
//	return (trimmed);
//}

 char	*ft_strjoin(char const *s1, char const *s2)
 {
 	char	*joined;
 	size_t	s1_len;
 	size_t	s2_len;

 	s1_len = ft_strlen(s1);
 	s2_len = ft_strlen(s2);
 	joined = (char *)malloc(sizeof(char) * (s1_len + s2_len + 1));
 	if (!joined)
 		return (NULL);
 	ft_strlcpy(joined, s1, s1_len + 1);
 	ft_strlcpy(joined + s1_len, s2, s2_len + 1);
 	return (joined);
 }

 char	*ft_substr(char const *s, unsigned int start, size_t len)
 {
 	char	*substr;
 	size_t	s_len;
 	size_t	sub_len;

 	s_len = ft_strlen(s);
 	if (s_len < start)
 		return (ft_strdup(""));
 	sub_len = s_len - start;
 	if (sub_len > len)
 		sub_len = len;
 	substr = (char *)malloc(sizeof(char) * (sub_len + 1));
 	if (!substr)
 		return (NULL);
 	ft_strlcpy(substr, s + start, sub_len + 1);
 	return (substr);
 }

void	clear_backup(char **backup)
{
	char	*temp;

	temp = ft_strdup("");
	free(*backup);
	*backup = temp;
}

char	*extract_line(char **backup, ssize_t read_size)
{
	char	*line;
	char	*temp;
	size_t	len;

	len = 0;
	while ((*backup)[len] != '\n' && (*backup)[len] != '\0')
		len++;
	if ((*backup)[len] == '\n')
	{
		line = ft_substr(*backup, 0, len + 1);
		temp = ft_strdup(*backup + len + 1);
		free(*backup);
		*backup = temp;
		if ((*backup)[0] == '\0')
			clear_backup(backup);
	}
	else
	{
		line = ft_strdup(*backup);
		clear_backup(backup);
		if (read_size == 0)
			return (NULL);
	}
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*backup[OPEN_MAX];
	char		*buffer;
	char		*temp;
	ssize_t		read_size;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	read_size = 1;
	while (read_size != 0 && ft_strchr(backup[fd], '\n') == 0)
	{
		read_size = read(fd, buffer, BUFFER_SIZE);
		if (read_size == -1)
		{
			free(buffer);
			return (NULL);
		}
		buffer[read_size] = '\0';
		temp = ft_strjoin(backup[fd], buffer);
		free(backup[fd]);
		backup[fd] = temp;
	}
	free(buffer);
	return (extract_line(&backup[fd], read_size));
}

 int	main(void)
 {
 	char	*line;
 	int		fd;

 	fd = open("test.txt", O_RDONLY);
	if (fd == -1)
		printf("error");
	else
		printf("%d\n", fd);
	printf("opened");
 	while (1)
 	{
 		line = get_next_line(fd);
 		if (!line)
 			break ;
 		printf("%s\n", line);
 		free(line);
 	}
 	close(fd);
 	return (0);
 }
