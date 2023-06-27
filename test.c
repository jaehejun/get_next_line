/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehejun <jaehejun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 13:47:20 by jaehejun          #+#    #+#             */
/*   Updated: 2023/06/27 17:06:36 by jaehejun         ###   ########.fr       */
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


abc \n de \n f	//8
\n ghijk \n l	//8
mn \n opqr		//7

<remain : NULL>
read 1 : buffer = abc \n de \n f
if (temp == NULL && remain == NULL)
	return (NULL);

if (strchr(remain, '\n') == NULL)
before(buffer) = abc \n -> line = abc \n
after(buffer) = de \n f -> remain = de \n f
return (line = abc \n)

<remain : de \n f>
if (temp == NULL && remain == NULL)
	return (NULL);
//if (strchr(remain, '\n') == NULL)
//read 2 : buffer = \n ghijk \n l
else if (strchr(remain, '\n') == TRUE)
before(remain) = de \n -> line = de \n
after(remain) = f -> remain = f
return (line = de \n)

<remain : f>
if (temp == NULL && remain == NULL)
	return (NULL);
if (strchr(remain, '\n') == NULL)
read 2 : buffer = \n ghijk \n l

before(buffer) = \n -> strjoin(remain, before(buffer)) = f \n -> line = f \n
after(buffer) = ghijk \n l -> remain = ghijk \n l
return (line = f \n)
//else if (strchr(remain, '\n') == TRUE)

<remain : ghijk \n l>
if (temp == NULL && remain == NULL)
	return (NULL);
if (strchr(remain, '\n') == NULL)
read 3 : buffer = mn \n opqr
else if (strchr(remain, '\n') == TRUE)
before(remain) = ghijk \n -> line = ghijk \n
after(remain) = l -> remain = l
return (line = ghijk \n)

<remain : l>
if (temp == NULL && remain == NULL)
	return (NULL);
if (strchr(remain, '\n') == NULL)
read 3 : buffer = mn \n opqr
//else if (strchr(remain, '\n') == TRUE)
before(buffer) = mn \n -> strjoin(remain, before(buffer)) = l mn \n -> line = l mn \n
after(buffer) = opqr -> remain = opqr
return (line = l mn \n)

<remain : opqr>
if (temp == NULL && remain == NULL)
	return (NULL);
if (strchr(remain, '\n') == NULL)
read 4 : buffer = \0

if (buffer == \0 && remain == \0)
return (NULL);

before(buffer) = opqr -> strjoin(remain, before(buffer)) = opqr -> line = opqr
after(buffer) = \0 -> remain = \0
return (line = opqr)
//else if (strchr(remain, '\n') == TRUE)

<remain : \0>
if (temp == NULL && remain == NULL)
	return (NULL);