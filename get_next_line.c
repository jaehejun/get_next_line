/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehejun <jaehejun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 20:04:32 by jaehejun          #+#    #+#             */
/*   Updated: 2023/07/06 23:00:27 by jaehejun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include "get_next_line.h"

char	*free_memory(char *allocated)
{
	free(allocated);
	allocated = NULL; 
	return (allocated);
}

char	*make_line(char *line)
{
	char	*new_line;
	int		len;
	int		i;

	len = 0;
	if (line[0] == '\0')
		return (NULL);
	while (line[len] != '\0')
	{
		if (line[len] == '\n')
		{
			len++;
			break ;
		}
		len++;
	}
	new_line = (char *)malloc(sizeof(char) * (len + 1));
	if (new_line == NULL)
		return (NULL);
	new_line[len] = '\0';
	i = 0;
	while (len-- > 0)
	{
		new_line[i] = line[i];
		i++;
	}
	return (new_line);
}

char	*make_remain(char *temp)
{
	char	*new_remain;
	int		i;

	i = 0;
	while (temp[i] != '\0')
	{
		if (temp[i] == '\n')
		{
			i++;
			break ;
		}
		i++;
	}
	new_remain = ft_strdup(&temp[i]);
	if (new_remain == NULL)
		return (NULL);
	return (new_remain);
}

char	*read_line(int fd, char *buffer, char *remain)
{
	char	*temp_remain;
	int		count;

	if (remain == NULL)
		remain = ft_strdup("");
	if (remain == NULL)
		return (NULL);
	count = 0;
	while (1)
	{
		count = read(fd, buffer, BUFFER_SIZE);
		if (count == -1)
			return (free_memory(remain));
			// 여기서 remain = NULL해도 get_next_line의 remain은 NULL로 바뀌지 않음
		if (count == 0)
			break ;
		buffer[count] = '\0';
		temp_remain = remain;
		remain = ft_strjoin(temp_remain, buffer);
		free_memory(temp_remain);
		if (remain == NULL)
			return (NULL);
		if (ft_strchr(remain, '\n'))
			break ;
	}
	return (remain);
}

char	*get_next_line(int fd)
{
	static char	*remain;
	char		*line;
	char		*buffer;
	char		*temp;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (buffer == NULL)
		return (NULL);
	line = read_line(fd, buffer, remain);
	free_memory(buffer);
	if (line == NULL)
	{
		if (remain != NULL)
			remain = NULL; // read_line()에서 remain = NULL해도 get_next_line의 remain은 NULL로 바뀌지 않음
		return (NULL);
	}
	remain = NULL; // read_line()에서 remain = NULL해도 get_next_line의 remain은 NULL로 바뀌지 않음
	temp = line;
	line = make_line(line);
	if (line == NULL)
		return(free_memory(temp));
	remain = make_remain(temp);
	if (remain == NULL)
	{
		free_memory(line);
		free_memory(temp);
		return (NULL);
	}
	free_memory(temp);
	//system("leaks a.out");
	return (line);
}


//int	main(void)
//{
//	int		fd1;
//	int		fd2;
//	char	*line;
	
//	fd1 = open("test.txt", O_RDONLY);
	//fd2 = open("test2.txt", O_RDONLY);
	//while ((line = get_next_line(fd1)) != NULL)
	//{
	//	printf("%s", line);
	//}
	//printf("gnl returns NULL\n");
	
	//printf("%s", get_next_line(fd1));
	//close(fd1);
	//printf("%s", get_next_line(fd2));
	//close(fd2);
	//printf("%s", get_next_line(0));
	//printf("%s", NULL);
//	return (0);
//}

//int	main(void)
//{
//	int	fd = 0;
//	char	*line;
	
//	while ((line = get_next_line(fd)) != NULL)
//	{
//		printf("%s\n", line);
//	}
//	if (line == NULL)
//		printf("GNL returns NULL in STDIN\n");
//	close(fd);
//	return 0;
//}
