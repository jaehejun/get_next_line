/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehejun <jaehejun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 20:04:32 by jaehejun          #+#    #+#             */
/*   Updated: 2023/06/18 21:58:05 by jaehejun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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
	printf("AFTER : %s\n", after);
	return (after);
}

char	*before(char *str)
{
	char	*before;
	int		i = 0;

	before = malloc(BUFFER_SIZE + 1);
	before[BUFFER_SIZE] = '\0';
	while (*str != '\0')
	{
		before[i++] = *str++;
		if (*str == '\n')
			break ;
	}
	before[i] = '\n';
	before[i+1] = '\0';
	printf("BEFORE : %s\n", before);
	return (before);
}


char	*get_next_line(int fd)
{
	char		*line;
	char		*temp;
	char		*buffer;
	int			count;
	static char	*remain;

	line = ft_strdup("");
	buffer = malloc(BUFFER_SIZE + 1);
	count = read(fd, buffer, BUFFER_SIZE);
	buffer[count] = '\0';
	printf("BUFFER : %s\n", buffer);
	line = ft_strjoin(line, buffer);
	printf("LINE : %s\n", line);
	temp = before(line);
	remain = after(line);
	if (ft_strchr(remain, '\n') != NULL)
	{
		temp = before(line);
		remain = after(line);
		free(line);
		line = remain;
		printf("TEMP : %s\n", temp);
		printf("REMAIN : %s\n", remain);
	}
	return (temp);
}

int	main(void)
{
	int		fd;
	char	*line;
	int	i = 1;
	
	fd = open("test.txt", O_RDONLY);
	line = get_next_line(fd);
	printf("%dgnl : %s\n", i++, line);
	//line = get_next_line(fd);
	//printf("%dgnl : %s\n", i++, line);
	//line = get_next_line(fd);
	//printf("%dgnl : %s\n", i++, line);
	return 0;
}