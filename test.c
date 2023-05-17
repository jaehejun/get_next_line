/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehejun <jaehejun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 13:47:20 by jaehejun          #+#    #+#             */
/*   Updated: 2023/05/17 17:58:09 by jaehejun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

void	test()
{
	static int	counter;
	
	printf("counter: %d\n", counter);
	counter++;
	printf("counter value: %d\n", counter);
}

int	main(void)
{
	char	*string = "./a.txt";
	char	*path = "./a.txt";
	int	fd;
	char buf[100];
	printf("a : %p\n", path);
	printf("path : %p\n", string);
	printf("./a.txt\n");
	fd = open("./a.txt", O_RDONLY);
	if (fd == -1)
	{
		if (errno == ENOENT)
			printf("File does not exist\n");
		else
			perror("Failed to open the file\n");
	}
	else
	{
		read(fd, buf, 10);
		printf("%s\n", buf);
	}
//	int	fd1;
	//char	buf1[100];
	//fd1 = open("a.txt", O_RDONLY);
	//printf("%d\n", fd1);
	//read(fd1, buf1, 10);
	//printf("%s\n", buf1);
	return (0);
}
	