/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehejun <jaehejun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 20:04:32 by jaehejun          #+#    #+#             */
/*   Updated: 2023/06/27 21:10:42 by jaehejun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*before(char *str)
{
	char	*before;
	int		i = 0;

	before = malloc(BUFFER_SIZE + 1);
	before[BUFFER_SIZE] = '\0';
	while (*str != '\0' && *str != '\n')
	{
		before[i++] = *str++;
		if (*str == '\n')
			break ;
	}
	before[i] = '\n';
	before[i+1] = '\0';
	return (before);
}

char	*after(char *str)
{
	char	*after;
	int		i = 0;
	after = malloc(BUFFER_SIZE + 1);
	after[BUFFER_SIZE] = '\0';
	while (*str != '\0')
	{
		str++;
		if (*str == '\n')
			break ;
	}
	str++;
	while (*str != '\0')
		after[i++] = *str++;
	after[i] = '\0';
	return (after);
}

char	*read_line(int fd, char *remain)
{
	char	*buffer;
	int		count;
	
	if (remain != NULL)
	{
		buffer = (char *)malloc(sizeof(char)*BUFFER_SIZE + 1);
		if (buffer == NULL)
			return (NULL);
		count = read(fd, buffer, BUFFER_SIZE);
		if (count <= 0)
			return (NULL);
		buffer[count] = '\0';
	}
	//buffer = ft_strjoin(remain, buffer);
	return (buffer);
}

char	*get_next_line(int fd)
{
	static int	i = 1;
	char		*line;
	//char		*temp;
	static char	*remain;		// remain = 0x0

	line = ft_strdup("");		// line = ""
	if (remain == NULL)			// remain이 0x0일때만 실행해서 remain의 값을 유지한다.
		remain = ft_strdup("");		// remain = ""
	printf("81 REMAIN %d: %s\n", i++, remain);
	//temp = ft_strdup("");		// temp = ""
	//remain = read_line(fd, remain);	// remain = abc\nde\nf
	//printf("temp : %s\n", temp);
	while (ft_strchr(remain, '\n') == NULL && remain != NULL)
	{
		printf("NO\\n\n");
		line = ft_strjoin(line, remain);	// line = abc\nde\nf
		if (line == NULL)
			return (NULL);
		printf("89 line : %s\n", line);
		remain = read_line(fd, remain);	// remain = abc\nde\nf
		printf("91 remain : %s\n", remain);
	}
	if (ft_strchr(remain, '\n') != NULL || remain == NULL)		// remain = abc\nde\nf
	{
		printf("got\\n\n");
		//temp = before(remain);
		//printf("temp : %s\n", temp);
		line = ft_strjoin(line, before(remain));	// line = abc\n
		printf("99 line : %s\n", line);
		remain = after(remain);	// remain = de\nf
		printf("101 remain : %s\n", remain);
		//temp = remain;			// temp = de\nf
		return (line);			// line = abc\n, remain = de\nf
	}
	printf("remain before returning NULL : %s\n", remain);
	return (NULL);
}

int	main(void)
{
	int		fd;
	char	*line;
	int	i = 1;
	fd = open("test.txt", O_RDONLY);
	line = get_next_line(fd);
	printf("GNL%d : %s\n", i++, line);
	line = get_next_line(fd);
	printf("GNL%d : %s\n", i++, line);
	line = get_next_line(fd);
	printf("GNL%d : %s\n", i++, line);
	line = get_next_line(fd);
	printf("GNL%d : %s\n", i++, line);
	line = get_next_line(fd);
	printf("GNL%d : %s\n", i++, line);
	line = get_next_line(fd);
	printf("GNL%d : %s\n", i++, line);
	return 0;
}