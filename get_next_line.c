/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehejun <jaehejun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 20:04:32 by jaehejun          #+#    #+#             */
/*   Updated: 2023/06/05 23:16:41 by jaehejun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>
#include <string.h>

//size_t	ft_strlen(const char *s)
//{
//	size_t	i;

//	i = 0;
//	while (s[i] != '\0')
//		i++;
//	return (i);
//}

//char	*ft_strchr(const char *s, int c)
//{
//	size_t	len;

//	len = ft_strlen(s) + 1;
//	while (len-- > 0)
//	{
//		if (*s == (char)c)
//			return ((char *)s);
//		s++;
//	}
//	return (NULL);
//}

//size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
//{
//	int		check_space;
//	size_t	src_len;

//	src_len = ft_strlen(src);
//	check_space = 0;
//	if (dstsize != 0)
//		check_space = 1;
//	while (*src != '\0' && dstsize-- > 1)
//		*dst++ = *src++;
//	if (check_space == 1)
//		*dst = '\0';
//	return (src_len);
//}

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
//	if (start >= ft_strlen(s1))
//		trimmed = (char *)malloc(sizeof(char) * 1);
//	else
//		trimmed = (char *)malloc(sizeof(char) * (end - start + 2));
//	if (trimmed == 0)
//		return (NULL);
//	ft_strlcpy(trimmed, s1 + start, end - start + 2);
//	return (trimmed);
//}


//char	*extract_line(char *buffer, size_t count)
//{
//	char		*line;
//	static char	*remain;
//	int			i;

//	line = malloc(count + 1);
//	if (line == NULL)
//		return (NULL);
//	line[count] = '\0';
//	while (*buffer != '\0')
//	{
//		*line++ = *buffer++;
//		if (*buffer == '\n')
//		{
//			*line = '\n';
//			*(line + 1) = '\0';
//			printf("%s", line);
//			break ;
//		}
//	}
//	printf("%s", line);
//	while (*buffer != '\0')
//		*remain++ = *buffer++;
//	*remain = '\0';
//	printf("%s\n", remain);
//	return (line);
//}

char	*get_next_line(int fd)
{
	char		*buffer;
	char		*line;
	//char		*new_line;
	static char	*remain;
	int			count;
	int			i;

	i = -1;
	buffer = malloc(BUFFER_SIZE + 1);
	if (buffer == NULL)
		return (NULL);
	count = read(fd, buffer, BUFFER_SIZE);
	if (count == -1 || count == 0)
		return (NULL);
	buffer[BUFFER_SIZE] = '\0';
	line = malloc(count + 1);
	if (line == NULL)
		return (NULL);
	line[count] = '\0';
	while (buffer[++i] != '\0')
	{
		line[i] = buffer[i];
		printf("%c", line[i]);
		printf("%c", buffer[i]);
		if (buffer[i] == '\n')
		{
			line[i] = buffer[i];
			break ;
		}
	}
	line[i + 1] = '\0';
	printf("%p", remain);
	//while (buffer[i] != '\0')
	//	*(remain++) = buffer[i++];
	//*remain = '\0';
	printf("%s", line);
	//printf("%s", remain);
	
	
	return (line);
}

int	main(void)
{
	int		fd;
	//int		count;
	//char	*line = "";
	
	fd = open("a.txt", O_RDONLY);
	//while (line != NULL) 
	//printf("%s", line = get_next_line(fd));
	get_next_line(fd);
}