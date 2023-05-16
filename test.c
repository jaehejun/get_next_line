/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehejun <jaehejun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 13:47:20 by jaehejun          #+#    #+#             */
/*   Updated: 2023/05/16 15:57:27 by jaehejun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

void	test()
{
	static int	counter;
	
	printf("counter: %d\n", counter);
	counter++;
	printf("counter value: %d\n", counter);
}

int	main(void)
{
	//int	fd1;
	//int	fd2;
	//char	buf1[100];
	//char	buf2[100];
	//fd1 = open("a.txt", O_RDONLY);
	//fd2 = open("b.txt", O_RDONLY);
	//printf("%d\n", fd1);
	//printf("%d\n", fd2);
	//read(fd1, buf1, 10);
	//read(fd2, buf2, 10);
	//printf("%s\n", buf1);
	//printf("%s\n", buf2);
	//close(fd1);
	//close(fd2);
	test();
	test();
	test();
	return (0);
}
	