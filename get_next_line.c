/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehejun <jaehejun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 20:04:32 by jaehejun          #+#    #+#             */
/*   Updated: 2023/07/07 18:53:10 by jaehejun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*free_memory(char *allocated1, char *allocated2)
{
	if (allocated1 != NULL)
	{
		free(allocated1);
		allocated1 = NULL;
	}
	if (allocated2 != NULL)
	{
		free(allocated2);
		allocated2 = NULL;
	}
	return (NULL);
}

char	*make_line(char *temp_read)
{
	char	*new_line;
	int		len;
	int		i;

	len = 0;
	while (temp_read[len] != '\0')
	{
		if (temp_read[len] == '\n')
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
		new_line[i] = temp_read[i];
		i++;
	}
	return (new_line);
}

char	*make_remain(char *temp_read)
{
	char	*new_remain;
	int		i;

	i = 0;
	while (temp_read[i] != '\0')
	{
		if (temp_read[i] == '\n')
		{
			i++;
			break ;
		}
		i++;
	}
	new_remain = ft_strdup(&temp_read[i]);
	if (new_remain == NULL)
		return (NULL);
	return (new_remain);
}

char	*read_line(int fd, char *remain)
{
	char	*buffer;
	char	*temp_remain;
	int		count;

	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (buffer == NULL)
		return (NULL);
	while (1)
	{
		count = read(fd, buffer, BUFFER_SIZE);
		if (count == -1)
			return (free_memory(buffer, remain));
		if (count == 0)
			break ;
		buffer[count] = '\0';
		temp_remain = remain;
		remain = ft_strjoin(temp_remain, buffer);
		free_memory(temp_remain, NULL);
		if (remain == NULL)
			return (free_memory(buffer, remain));
		if (ft_strchr(remain, '\n'))
			break ;
	}
	free_memory(buffer, NULL);
	return (remain);
}

char	*get_next_line(int fd)
{
	static char	*remain;
	char		*line;
	char		*temp_read;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = read_line(fd, remain);
	if (line == NULL)
	{
		if (remain != NULL)
			remain = NULL;
		return (NULL);
	}
	remain = NULL;
	temp_read = line;
	if (temp_read[0] == '\0')
		return (free_memory(line, NULL));
	line = make_line(line);
	if (line == NULL)
		return (free_memory(temp_read, NULL));
	remain = make_remain(temp_read);
	if (remain == NULL)
		return (free_memory(temp_read, line));
	free_memory(temp_read, NULL);
	return (line);
}
