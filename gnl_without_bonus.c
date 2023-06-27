#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#define BUFFER_SIZE 1
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

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*join;
	size_t	s1_len;
	size_t	s2_len;

	if (!s1 && !s2)
		return (NULL);
	else if (!s1)
		return (ft_strdup(s2));
	else if (!s2)
		return (ft_strdup(s1));
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	join = (char *)malloc(sizeof(char) * (s1_len + s2_len + 1));
	if (!join)
		return (NULL);
	ft_strlcpy(join, s1, s1_len + 1);
	ft_strlcpy(join + s1_len, s2, s2_len + 1);
	return (join);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	s_len;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (s_len < start)
		return (ft_strdup(""));
	if (s_len - start < len)
		len = s_len - start;
	substr = (char *)malloc(sizeof(char) * (len + 1));
	if (!substr)
		return (NULL);
	ft_strlcpy(substr, s + start, len + 1);
	return (substr);
}

char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*join;

	join = ft_strjoin(s1, s2);
	free(s1);
	free(s2);
	return (join);
}

int	get_next_line(int fd, char **line)
{
	static char	*save[OPEN_MAX];
	char		*buf;
	char		*temp;
	int			read_size;

	if (fd < 0 || fd >= OPEN_MAX || !line || BUFFER_SIZE <= 0)
		return (-1);
	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (-1);
	read_size = 1;
	while (!ft_strchr(save[fd], '\n') && read_size != 0)
	{
		read_size = read(fd, buf, BUFFER_SIZE);
		if (read_size == -1)
		{
			free(buf);
			return (-1);
		}
		buf[read_size] = '\0';
		temp = ft_strjoin_free(save[fd], buf);
		save[fd] = temp;
	}
	free(buf);
	*line = ft_substr(save[fd], 0, ft_strchr(save[fd], '\n') - save[fd]);
	temp = ft_strdup(save[fd] + (ft_strchr(save[fd], '\n') - save[fd]) + 1);
	free(save[fd]);
	save[fd] = temp;
	if (read_size == 0)
		return (0);
	return (1);
}

int	main(void)
{
	int		fd;
	char	*line;
	int		i;

	fd = open("test.txt", O_RDONLY);
	i = 1;
	while (get_next_line(fd, &line) > 0)
	{
		printf("%d: %s\n", i, line);
		free(line);
		i++;
	}
	printf("%d: %s\n", i, line);
	free(line);
	close(fd);
	return (0);
}

// Path: gnl_with_bonus.c