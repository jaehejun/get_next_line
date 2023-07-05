/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehejun <jaehejun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 20:04:32 by jaehejun          #+#    #+#             */
/*   Updated: 2023/07/05 17:03:59 by jaehejun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	free_memory(char *allocated)
{
	free(allocated);
	allocated = NULL;
}

char	*make_line(char *line)
{
	char	*new_line;
	int		len;
	int		i;

	len = 0;
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
	count = 1;
	while (count != 0 && strchr(remain, '\n') == NULL)
	{
		count = read(fd, buffer, BUFFER_SIZE);
		if (count == -1)
		{
			free_memory(remain);
			return (NULL);
		}
		if (count == 0)
			break ;
		buffer[count] = '\0';
		temp_remain = remain;
		remain = ft_strjoin(remain, buffer);
		free_memory(temp_remain);
		if (remain == NULL)
			return (NULL);
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
	if (line == NULL || line[0] == '\0')
	{
		if (remain != NULL)
			free_memory(remain);
		return (NULL);
	}
	temp = line;
	line = make_line(line);
	if (line == NULL)
	{
		free(temp);
		return (NULL);
	}
	remain = make_remain(temp);
	if (remain == NULL)
	{
		free_memory(line);
		free_memory(temp);
		return (NULL);
	}
	free_memory(temp);
	return (line);
}
