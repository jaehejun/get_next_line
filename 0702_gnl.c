/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0702_gnl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehejun <jaehejun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 20:04:32 by jaehejun          #+#    #+#             */
/*   Updated: 2023/07/03 20:48:29 by jaehejun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*until_newline(char *str)
{
	char	*before;
	int		i;

	if (str == NULL)
		return (NULL);
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

	if (str == NULL)
		return (NULL);
	i = 0;
	while (str[i] != '\0')
	{
		i++;
		if (str[i] == '\n')
			break;
	}
	after = ft_strdup(&str[i + 1]);
	if (after == NULL)
		return (NULL);
	return (after);
}

char	*read_line(int fd, char *remain)
{
	char	*before_remain;
	char	*buffer;
	int		count;
	
	buffer = (char *)malloc(sizeof(char)* (BUFFER_SIZE + 1));
	if (buffer == NULL)
		return (NULL);
	count = 1;
	while (count != 0 && ft_strchr(remain, '\n') == NULL)
	{
		count = read(fd, buffer, BUFFER_SIZE);
		if (count == -1)
		{
			free(buffer);
			return(NULL);
		}
		buffer[count] = '\0';
		before_remain = remain;
		remain = ft_strjoin(before_remain, buffer);
		if (remain == NULL)
			return (NULL);
		free(before_remain);
		before_remain = NULL;
	}
	free(buffer);
	buffer = NULL;
	return(remain);
}

char	*get_next_line(int fd)
{
	char		*line;
	char		*temp;
	static char	*remain;

	if (fd < 0 || fd > 256)
		return (NULL);
	if (remain == NULL)
		remain = ft_strdup("");
	if (remain == NULL)
		return (NULL);
	remain = read_line(fd, remain);
	if (remain == NULL)
	{
		free(remain);
		return (NULL);
	}
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehejun <jaehejun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 20:04:35 by jaehejun          #+#    #+#             */
/*   Updated: 2023/07/02 19:29:40 by jaehejun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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
	int		i;

	i = 0;
	memsize = ft_strlen(s1);
	copy = (char *)malloc(sizeof(char) * (memsize + 1));
	if (copy == NULL)
		return (NULL);
	while (s1[i] != '\0')
	{
		copy[i] = s1[i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
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