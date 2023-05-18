/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehejun <jaehejun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 20:04:32 by jaehejun          #+#    #+#             */
/*   Updated: 2023/05/18 22:53:26 by jaehejun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>
#include <string.h>

char	*get_next_line(int fd)
{
	char	*buffer;
	int		count;
	
	buffer = malloc(BUFFER_SIZE + 1);
	if (buffer == NULL)
		return (NULL);
	
	count = read(fd, buffer, BUFFER_SIZE);
	buffer[count] = '\0';
	if (count == -1 || count == 0)
		return (NULL);
	return (buffer);
}

int	main(void)
{
	int		fd;
	int		count;
	char	*line = "";
	
	fd = open("a.txt", O_RDONLY);
	while (line != NULL)
		printf("%s", line = get_next_line(fd));
}