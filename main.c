/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehejun <jaehejun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 19:12:35 by jaehejun          #+#    #+#             */
/*   Updated: 2023/05/18 20:56:29 by jaehejun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#define BUFFER_SIZE 1

//int	main(void)
//{
//	char	buf[BUFFER_SIZE + 1];
//	char	*save = 0;
//	int		fd;
//	int		temp = 0;

//	fd = open("main.txt", O_RDONLY);
//	if (fd == -1)
//		printf("file open error");
//	else
//	{
//		while ((temp = read(fd, buf, BUFFER_SIZE) > 0))
//		{
//			buf[temp] = '\0';
//			if (save == NULL)
//			{
//				save = strdup(buf);
//				printf("%s\n", save);
//			}
//			else
//			{
//				strcat(save, buf);
//				printf("%s\n", save);
//			}
//		}
//		//printf("%s", save);
//		close(fd);
//	}
//	return (0);
//}

//array[2]
//(array + 2)