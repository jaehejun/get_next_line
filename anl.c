#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <strings.h>
# define BUFFER_SIZE 1

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ft_strdup(const char *s1)
{
	char	*copy;
	size_t	memsize;

	memsize = ft_strlen(s1);
	copy = (char *)malloc(sizeof(char) * (memsize + 1));
	if (copy == 0)
		return (NULL);
	while (*s1 != '\0')
		*copy++ = *s1++;
	*copy = '\0';
	return (copy - memsize);
}

char	*ft_strchr(const char *s, char c)
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

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*join;
	size_t	len1;
	size_t	len2;
	int		i;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	join = (char *)malloc(sizeof(char) * (len1 + len2 + 1));
	if (join == 0)
		return (NULL);
	i = 0;
	while (len1-- > 0)
		join[i++] = *s1++;
	while (len2-- > 0)
		join[i++] = *s2++;
	join[i] = '\0';
	return (join);
}

char	*get_next_line(int fd)
{
	char		*buffer;
	char		*remain;
	char		*before_next;
	static char	*line;
	int			count;
	int			i;
	int			j;

	if (fd < 0 || BUFFER_SIZE <= 0)	// fd할당 잘못되었거나 버퍼사이즈가 0이하면 NULL
		return (NULL);
	if (line == 0)
		line = ft_strdup("");	// line을 사용하기 위해 빈문자열을 만들어 주소값을 할당해준다.
	if (line == NULL)
		return (NULL);
	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));	//버퍼사이즈+1(널자리)만큼 동적할당
	if (buffer == NULL)
		return (NULL);
	buffer[BUFFER_SIZE] = '\0';		// +1한 자리에 널문자 넣어서 문자열의 끝을 알린다.
	count = 1;						// read한 문자의 갯수를 파악하기 위해 1을 넣어둔다.
	while ((count = read(fd, buffer, BUFFER_SIZE)) != 0)	// read성공해서 1개라도 읽으면 0이 되지않는다.
	{
		printf("buffer : %s\n", buffer);
		printf("line : %s\n", line);
		buffer[count] = '\0';	// 버퍼사이즈보다 count가 작을수도 있어서 널문자로 문자열의 끝을 알린다.
		before_next = ft_strjoin(line, buffer);	// before_next에 line + buffer
		if (ft_strchr(line, '\n'))			// 라인에서 개행문자가 발견되면 반복문을 종료한다.
			break ;					
											// EOF를 만나거나 EOF만나기 전에 개행문자를 만나면 반복문 종료.
	}
	if (count == 0)		// EOF를 만났을 때 count가 0이 되므로 NULL반환하고 종료
		return (NULL);
	i = -1;
	before_next = (char *)malloc(sizeof(char) * count);	// 처음 만나는 개행까지를 저장한다(말록사이즈정해야함)
	if (before_next == NULL)
		return (NULL);
	while (line[++i] != '\n')
		before_next[i] = line[i];			// 처음만나는 개행까지 line에서 복사한다.
	before_next[i] = '\n';
	before_next[i + 1] = '\0';				// 개행과 널문자 넣는다.
	i += 1;
	j = 0;
	remain = (char *)malloc(sizeof(char) * count);	// line의 개행 뒷부분을 remain에 저장한다.
	if (remain == NULL)
		return (NULL);
	while (line[++i] != '\0')
		remain[j++] = line[i];
	remain[j] = '\0';
	return (before_next);		// 처음 만나는 개행까지(개행포함)반환한다.
}


// line1이 개행까지 끊어서 출력되는데 계속 line1을 가지고 있음
// line1을 초기화하고 다음 개행까지 before next라인에 넣는걸 반복문 안에 넣어서 돌려야 할 것 같다.
// 버퍼사이즈가 1일때도 계속 첫줄(개행전까지)만 가지고 있음

int	main(void)
{
	int		fd;
	char	*gnl;
	int		n;

	n = 1;
	fd = open("test.txt", O_RDONLY);
	if (fd == -1)
		printf("error\n");
	while (1)
	{
		gnl = get_next_line(fd);
		if (gnl == NULL)
			break ;
		printf("line%d: %s", n, gnl);
		printf("------------------------Cycle %d DONE------------------------\n", n++);
		free(gnl);
	}
	close(fd);
	return (0);
}