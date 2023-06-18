/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehejun <jaehejun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 13:47:20 by jaehejun          #+#    #+#             */
/*   Updated: 2023/06/18 21:14:13 by jaehejun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#define BUFFER_SIZE 4


char	*test(char)
{
	while (*line != '\0')
	{
		line++;
		printf("str add : %p\n", line);
	}
	return (line);
}

char	*readline(int fd)
{
	static char	*line;
	char		*buffer;
	int			count;
	line = strdup("");
	buffer = malloc(BUFFER_SIZE + 1);
	count = read(fd, buffer, BUFFER_SIZE);
	buffer[count] = '\0';
	line = strcat(line, buffer);
	line++;
	printf("line : %s\n", line);
	printf("line add : %p\n", line);
	test(&line);
	printf("after line : %s\n", line);
	printf("after add : %p\n", line);
	return (line);
}

int	main(void)
{
	char	*str;
	int		fd;

	fd = open("test.txt", O_RDONLY);
	str = readline(fd);
	readline(fd);
	readline(fd);
	printf("AFTER STR : %s\n", str);
	printf("AFTER ADD : %p\n", str);
	close(fd);
	return 0;
}
